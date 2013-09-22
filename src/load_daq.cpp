/*
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License Version 2 as
** published by the Free Software Foundation.  You may not use, modify or
** distribute this program under any other version of the GNU General
** Public License.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
*/

#define IN_MEM_TEST

//#define __DEBUG__ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <time.h>
#include <pthread.h>
#include <stdarg.h>
#ifndef IN_MEM_TEST
#include "load_daq.h" 
#endif

#include <queue>

using namespace std;

#define IN_MEM_TEST 1 

// 10M
#define  BUF_SIZE  (1024 * 1024 * 10) 

#ifdef IN_MEM_TEST
#define DAQ_VERDICT_PASS 1
typedef struct _DAQ_PktHdr_t
{
    int caplen;
}DAQ_PktHdr_t;

typedef int DAQ_Verdict;
#define ANALYSIS_SIZE  (BUF_SIZE / 10 - 5)
#endif

const char * DAQ_LIB_PATH = "/usr/local/lib/daq/daq_dpdk.so";

const int SNAPLEN = 1514;

#define CONSUMER_THREAD_NUM 3 

static unsigned long long rev_bytes = 0;

typedef struct _buf{
    //volatile int len;
    //volatile void *addr;
    int len;
    void *addr;
}buf;

const int BUF_NUM = 4;

#define IDLE 0
#define NO_IDLE 1

#define RING_BUF_ENTRY_NUM 10
#define RING_BUF_ENTRY_SIZE BUF_SIZE 
#define MAX_ENRTY_NUM 50 
 
typedef enum _st{
	EMPTY,
	NOT_EMPTY,		
	FULL
}st;

#if 0
typedef struct _rev_ring_buf{
    int in_index;
    int out_index;
    int entry_num;
    st status;
    buf ring_buf_entry[RING_BUF_ENTRY_NUM];
}rev_ring_buf;

rev_ring_buf rrb;

typedef struct  _buf_info{
    
    buf buf_for_consumer[CONSUMER_THREAD_NUM];//producer write and consumer read
    volatile int consumer_idle[CONSUMER_THREAD_NUM]; //consumer write and producer read
    pthread_mutex_t mutex;
    pthread_cond_t cond_from_producer;
    pthread_cond_t cond_from_consumer;
    pthread_t pid[CONSUMER_THREAD_NUM];
    int thread_index[CONSUMER_THREAD_NUM];
}buf_info;

buf_info bi={.mutex = PTHREAD_MUTEX_INITIALIZER,
			 .cond_from_producer = PTHREAD_COND_INITIALIZER,
			 .cond_from_consumer = PTHREAD_COND_INITIALIZER};
#endif

typedef enum _thread_type{
    GPU,
    CPU
}thread_type;

typedef struct _thread_buf_fifo{
    pthread_mutex_t mutex;
    pthread_cond_t cond_from_producer;
    thread_type t_type;
    queue<buf> buf_fifo;
    pthread_t tid;
    int thread_index;
    int MAX_entry_num;
}thread_buf_fifo;

thread_buf_fifo tbfifo[CONSUMER_THREAD_NUM] = 
{
    {PTHREAD_MUTEX_INITIALIZER,PTHREAD_COND_INITIALIZER},
    {PTHREAD_MUTEX_INITIALIZER,PTHREAD_COND_INITIALIZER},
    {PTHREAD_MUTEX_INITIALIZER,PTHREAD_COND_INITIALIZER},
   // {PTHREAD_MUTEX_INITIALIZER,PTHREAD_COND_INITIALIZER},
};

pthread_cond_t cond_consumer_not_full = PTHREAD_COND_INITIALIZER; 

#define _ERR(STR)	do{\
	fprintf(stderr, "%s:%d ERROR INFO:" STR "\n", __FILE__, __LINE__);\
	exit(EXIT_FAILURE);\
	}while(0)


#ifdef __DEBUG__
    #define _D(STR, ARGS...)    do{\
	    printf("%s:%d INFO:" STR "\n", __FILE__, __LINE__, ##ARGS);\
    }while(0)

#else
    #define _D(STR, ARGS...)    do{\
        ;\
    }while(0)
#endif

void *fill_buf_p = NULL;
int fill_buf_size = 0;

unsigned long long timeNanos()
{
    struct timespec tp;
    clock_gettime(CLOCK_MONOTONIC, &tp);
    return (unsigned long long) tp.tv_sec * (1000ULL * 1000ULL * 1000ULL) + (unsigned long long) tp.tv_nsec;
}


#ifdef IN_MEM_TEST
DAQ_Verdict analysis_func(void *user, const DAQ_PktHdr_t *hdr, char *data)
#else
DAQ_Verdict analysis_func(void *user, const DAQ_PktHdr_t *hdr, const uint8_t *data)
#endif
{
	int i;
    static int arranged_thread = 0;
    buf buf_push;

#if 0	
	for (i=0; i < hdr->caplen; i++)
	{
		printf("%c", data[i]);
	}
	printf("\n");
#endif

    // TODO  check whether need to buffer the packet to so much size!!!
    // so here we can schedule according the thread
    //_D("In analysis_func");
    //_D("size:%d\n",hdr->caplen);
    rev_bytes += hdr->caplen; 
    // printf("rev_bytes:%lld\n",rev_bytes);	
    if (NULL == fill_buf_p)
    {
        fill_buf_p = (void*)malloc(BUF_SIZE);
        if (NULL == fill_buf_p)
        {
            _ERR("malloc");
        }
        _D("malloc address:%d", fill_buf_p);
    }
    
    if (fill_buf_size + hdr->caplen < BUF_SIZE)
    {
        memcpy(fill_buf_p + fill_buf_size , (void*)data, hdr->caplen);
        fill_buf_size += hdr->caplen;

       // _D("memcpy fill_buf_size:%d\n", fill_buf_size);
        
        return DAQ_VERDICT_PASS;
    }

find_idle_thread:

    // TODO robin way to arrange task
    for (i=0; i < CONSUMER_THREAD_NUM; i++)
    {

        arranged_thread++;
        arranged_thread %= CONSUMER_THREAD_NUM;

       // arranged_thread = 0;

        pthread_mutex_lock(&(tbfifo[arranged_thread].mutex));
        
        _D("thread[%d] buffer size %d",arranged_thread,
                    tbfifo[arranged_thread].buf_fifo.size()) ;
        
        if (tbfifo[arranged_thread].buf_fifo.size() < MAX_ENRTY_NUM)
        { 
            _D("thread[%d] buffer size %d,take the job",arranged_thread,
                    tbfifo[arranged_thread].buf_fifo.size()) ;

            buf_push.addr = fill_buf_p;
            buf_push.len  = fill_buf_size;
            
            // FIXME may alloc new memory ,not good!,DEAD LOCK??
            tbfifo[arranged_thread].buf_fifo.push(buf_push); 
            
            pthread_mutex_unlock(&(tbfifo[arranged_thread].mutex));
            
            _D("producer send signal to consumer");
            pthread_cond_broadcast(&(tbfifo[arranged_thread].cond_from_producer));
            
            
            fill_buf_size = 0;
            fill_buf_p    = NULL;
            
            return DAQ_VERDICT_PASS;
        }
        
        pthread_mutex_unlock(&(tbfifo[arranged_thread].mutex));
    }

    if (CONSUMER_THREAD_NUM == i)
    {
        _D("NO idle thread:Waiting signal from consumer!");
        _D("producer waiting consumer IN");
        
        pthread_cond_wait(&cond_consumer_not_full,
                &(tbfifo[arranged_thread].mutex));
        
        // XXX XXX XXX must unlock before goto find_idle_thread
        // in case of two times add lock!!!
         
        pthread_mutex_unlock(&(tbfifo[arranged_thread].mutex));
        
        _D("producer waiting consumer OUT");
        goto find_idle_thread;
    }
    
#if 0

    // now, need inform the consumer thread the buffer is ready
    // check which thread is idle
   
    pthread_mutex_lock(&(bi.mutex));

find_idle_thread:

    for (i=0; i < CONSUMER_THREAD_NUM; i++)
    {
        if (IDLE != bi.consumer_idle[i])
            continue;
        // find idle thread
        // XXX here or in thread function???
        
        _D("find thread [%d] idle\n", i);

        bi.consumer_idle[i] = NO_IDLE;
        bi.buf_for_consumer[i].addr = fill_buf_p;
        bi.buf_for_consumer[i].len  = fill_buf_size;
        fill_buf_size = 0;
        fill_buf_p    = NULL;
        break;
    }

    if (CONSUMER_THREAD_NUM == i)
    {
        _D("NO idle thread:Waiting signal from consumer!");
        _D("producer waiting consumer IN");
        pthread_cond_wait(&(bi.cond_from_consumer), &(bi.mutex));
        _D("producer waiting consumer OUT");
        goto find_idle_thread;
    }
    
	// XXX after unlock or before unlock
    //pthread_cond_broadcast(&(bi.cond_from_producer));
	
    pthread_mutex_unlock(&(bi.mutex));
    
    _D("produce broadcast signal to consumer");
    pthread_cond_broadcast(&(bi.cond_from_producer));

    return DAQ_VERDICT_PASS;
#endif
}

int handle_buf_sum(void* buf_addr, int buf_len)
{
    int i;
    int sum = 0;
    for (i=0; i < buf_len; i++)
    {
        sum += (int)(*(char*)(buf_addr));
    }
    return sum;
}

int handle_buf_nothing(void* buf_addr, int buf_len)
{
   return 1; 
}

void *consumer_thread(void *arg)
{
    buf buf_pop;

    int buf_len;
    void * buf_addr;

    int thread_index = *((int *)arg);
    int times = 0;
    
    int sum;

	while(1)
	{
		_D("++++++++++++++tid[%d]:%u(%d)times++++++++++++++\n", 
                thread_index, (unsigned int)pthread_self(), times++); 

        pthread_mutex_lock(&(tbfifo[thread_index].mutex));

        //  empty
        while (tbfifo[thread_index].buf_fifo.empty())
        {
            _D("consumer [%d] waiting producer IN", thread_index);
		    pthread_cond_wait(&(tbfifo[thread_index].cond_from_producer), 
                              &(tbfifo[thread_index].mutex));
            _D("consumer [%d] waiting producer OUT", thread_index);
        }
        
        // not empty

        buf_pop = tbfifo[thread_index].buf_fifo.front();
        tbfifo[thread_index].buf_fifo.pop();
        
        pthread_mutex_unlock(&(tbfifo[thread_index].mutex));
        
        _D("thread [%d] pop oldest buf to handle,queue size:%d\n",
                thread_index,
                tbfifo[thread_index].buf_fifo.size());
        
        pthread_cond_broadcast(&cond_consumer_not_full);
        _D("consumer broadcast signal to producer");

		sum = handle_buf_sum(buf_pop.addr, buf_pop.len);
        
        _D("thread[%d]===sum:%d\n", thread_index, sum);

        _D("free address:%d\n", buf_pop.addr);
		free(buf_pop.addr);

#if 0
		pthread_mutex_lock(&(bi.mutex));
		
		while(NULL == bi.buf_for_consumer[thread_index].addr)
		{
            _D("consumer waiting producer IN");
		    pthread_cond_wait(&(bi.cond_from_producer), &(bi.mutex));
            _D("consumer waiting producer OUT");
		}

		buf_len  = bi.buf_for_consumer[thread_index].len;
		buf_addr = bi.buf_for_consumer[thread_index].addr;
		
		bi.consumer_idle[thread_index] = IDLE;
		
		bi.buf_for_consumer[thread_index].addr = NULL;
		bi.buf_for_consumer[thread_index].len  = 0;
        
        pthread_mutex_unlock(&(bi.mutex));
	   
		sum = handle_buf_sum(buf_addr, buf_len);
		//sum = handle_buf_nothing(buf_addr, buf_len);
	    
        _D("thread[%d]===sum:%d\n", thread_index, sum);

        _D("free address:%x\n", (unsigned int)buf_addr);
		free(buf_addr);
	    
        //if pthread_cond_broadcast call before produce pthread_cond_wait 
        
		pthread_cond_broadcast(&(bi.cond_from_consumer));
        _D("consumer broadcast signal to producer");
#endif
    }

    return ((void*)0);
}

#if 0
void rrb_init()
{
	void *p;
    int i;

	rrb.entry_num = 0;
    rrb.in_index  = 0;
    rrb.out_index = 0;
	rrb.status    = EMPTY;

    for (i=0; i < RING_BUF_ENTRY_NUM; i++)
    {

		p = malloc(RING_BUF_ENTRY_SIZE);
		if (NULL == p)
		{
		     _ERR("malloc");
		}
		rrb.ring_buf_entry[i].addr = p;
        rrb.ring_buf_entry[i].len  = RING_BUF_ENTRY_SIZE;
    }
}

void bi_init()
{
    int i;
    for (i=0; i < CONSUMER_THREAD_NUM; i++)
    {
        bi.buf_for_consumer[i].len  = 0;
        bi.buf_for_consumer[i].addr = NULL;
        bi.consumer_idle[i]         = IDLE;
        bi.pid[i]                   = 0;
        bi.thread_index[i]          = i;
    }
}
#endif

void multi_thread_init()
{
    int ret,i;
    
    // create multi thread 
    for (i=0; i < CONSUMER_THREAD_NUM; i++)
    {
        tbfifo[i].thread_index = i;

        ret = pthread_create(&(tbfifo[i].tid), NULL, consumer_thread,
                             (void*)&tbfifo[i].thread_index);
        if (0 != ret)
        {
            _ERR("thread create");
        }
        else
        {
            _D("thread[%d]:%u create!", tbfifo[i].thread_index,tbfifo[i].tid);
        }
        pthread_detach(tbfifo[i].tid);
    }
}

void tbfifo_init()
{
    int i;

   // create multi thread 
    for (i=0; i < CONSUMER_THREAD_NUM; i++)
    {
        tbfifo[i].MAX_entry_num = MAX_ENRTY_NUM;
        tbfifo[i].t_type        = CPU;
    }

}

int main(int argc, char *argv[])
{
    void *handle_p;
    
    int i;

    char *err = NULL;

	int ret;

    float result;
	
    void * ctx_p;

#ifdef IN_MEM_TEST
    char* buf_for_analysis_p;
    DAQ_PktHdr_t hdr;
#else
    DAQ_Config_t  DAQ_config;

	DAQ_Module_t *DMD_p; //DAQ_MODULE_DATA

	DAQ_Analysis_Func_t analysis_func_p = analysis_func;
#endif

	char buf[256] = "";

    unsigned long long start,end,use;

//	rrb_init();
//	bi_init();
	multi_thread_init();
   // return 0;
    tbfifo_init();

#ifdef IN_MEM_TEST

    buf_for_analysis_p = (char*)malloc(ANALYSIS_SIZE);
    if (NULL == buf_for_analysis_p)
    {
         _ERR("malloc");
    }

    memset((void*)buf_for_analysis_p, 1, ANALYSIS_SIZE);
    hdr.caplen = ANALYSIS_SIZE;
    for (i=0; i < 100000; i++)
    //while(1)
    {
        _D("====================%d=======================\n",i);
        analysis_func(NULL, &hdr, buf_for_analysis_p);
    }

    free(buf_for_analysis_p);
    _D("main thread finish,input anything to exit!\n");
    
    getchar();

#else
//#ifndef IN_MEM_TEST 
    handle_p = dlopen(DAQ_LIB_PATH, RTLD_LAZY);

    if (NULL == handle_p)
    {
	    fprintf(stderr, "%s:%d ERROR INFO: %s\n", __FILE__, __LINE__, dlerror());
	    exit(EXIT_FAILURE);
    }

	dlerror();
	
	DMD_p = (DAQ_Module_t*)dlsym(handle_p, "DAQ_MODULE_DATA");

	if (dlerror() != NULL)
	{
	    fprintf(stderr, "%s:%d ERROR INFO: %s\n", __FILE__, __LINE__, dlerror());
	    exit(EXIT_FAILURE);
    }

	DAQ_config.snaplen = SNAPLEN;
	DAQ_config.flags = DAQ_CFG_PROMISC;
	DAQ_config.timeout = 0;
	DAQ_config.mode = MAX_DAQ_MODE; // no meaning

 	ret = DMD_p->initialize(&DAQ_config, &ctx_p, buf, sizeof(buf));

	if (DAQ_SUCCESS != ret)
	{
		_ERR("dpdk_daq_initialize");
	}else
	{
		printf("dpdk_daq_initialize successful!\n");
	}

	ret = DMD_p->start(ctx_p);

	if (DAQ_SUCCESS != ret)
	{
		_ERR("dpdk_daq_start");
	}else
	{
		printf("dpdk_daq_start successful!\n");
	}

    start = timeNanos();

#define PKT_NUM 1000*1000*1000 
    
    for (i = 0; i < PKT_NUM; i++)
    {    //sleep(1);
        ret = DMD_p->acquire(ctx_p, 1, analysis_func, NULL, NULL);
        
        if (DAQ_SUCCESS != ret)
        {
            _ERR("dpdp_daq_acquire");
        }
    }

    end = timeNanos();
    
    use = end - start;
    
    printf("rev_bytes:%lld\n",rev_bytes);

    printf("time:%f s\n", use / 1000000000.0f);

    result =  (rev_bytes/(1024.0f*1024*1024))/(use / 1000000000.0f);

    printf("speed:%f GB/s\n",result);	

    dlclose(handle_p);
    free(ctx_p);
    
    _D("main thread finish,input anything to exit!\n");
    getchar();
#endif
	exit(EXIT_SUCCESS);
}


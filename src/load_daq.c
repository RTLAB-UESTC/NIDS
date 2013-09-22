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

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <time.h>
#include <pthread.h>
#include <stdarg.h>

//#define IN_MEM_TEST 1 

// 10M
#define  BUF_SIZE  (1024 * 1024 * 10) 

#ifndef IN_MEM_TEST
#include "load_daq.h" 
#endif

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

#define CONSUMER_THREAD_NUM 4 

static unsigned long long rev_bytes = 0;

typedef struct _buf{
    volatile int len;
    volatile void *addr;
}buf;

const int BUF_NUM = 4;

#define IDLE 0
#define NO_IDLE 1

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

#define _ERR(STR)	do{\
	fprintf(stderr, "%s:%d ERROR INFO:" STR "\n", __FILE__, __LINE__);\
	exit(EXIT_FAILURE);\
	}while(0)

//#define __DEBUG__ 

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
#if 0	
	for (i=0; i < hdr->caplen; i++)
	{
		printf("%c", data[i]);
	}
	printf("\n");
#endif

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
        _D("malloc address:%x", (unsigned int)fill_buf_p);
    }
    if (fill_buf_size + hdr->caplen < BUF_SIZE)
    {
        memcpy(fill_buf_p + fill_buf_size , (void*)data, hdr->caplen);
        fill_buf_size += hdr->caplen;
        
       // _D("memcpy fill_buf_size:%d\n", fill_buf_size);
        
        return DAQ_VERDICT_PASS;
    }
    
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
    int buf_len;
    void * buf_addr;

    int thread_index = *((int *)arg);
    int times = 0;

    int sum;

	while(1)
	{
		_D("++++++++++++++tid[%d]:%u(%d)times++++++++++++++\n", 
                thread_index, (unsigned int)pthread_self(), times++); 
		
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
    }

    return ((void*)0);
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
    unsigned char* buf_for_analysis_p;
    DAQ_PktHdr_t hdr;
#else
    DAQ_Config_t  DAQ_config;

	DAQ_Module_t *DMD_p; //DAQ_MODULE_DATA

	DAQ_Analysis_Func_t analysis_func_p = analysis_func;
#endif

	char buf[256] = "";

    unsigned long long start,end,use;

    for (i=0; i < CONSUMER_THREAD_NUM; i++)
    {
        bi.buf_for_consumer[i].len  = 0;
        bi.buf_for_consumer[i].addr = NULL;
        bi.consumer_idle[i]         = IDLE;
        bi.pid[i]                   = 0;
        bi.thread_index[i]          = i;
    }

    // create multi thread 
    for (i=0; i < CONSUMER_THREAD_NUM; i++)
    {
        ret = pthread_create(&(bi.pid[i]), NULL, consumer_thread, (void*)&bi.thread_index[i]);
        if (0 != ret)
        {
            _ERR("thread create");
        }
        pthread_detach(bi.pid[i]);
    }

#ifdef IN_MEM_TEST

    buf_for_analysis_p = (unsigned char*)malloc(ANALYSIS_SIZE);
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
	
	DMD_p = dlsym(handle_p, "DAQ_MODULE_DATA");

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







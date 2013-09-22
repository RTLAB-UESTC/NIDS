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

#include <sfbpf.h>
#include <daq_api.h>
#include <sfbpf_dlt.h>

#define RTE_MAX_LCORE 32
#define DAQ_DPDK_VERSION 1
#define DPDK_MAX_PORTS 32
#define MBUF_SIZE (2048 + sizeof(struct rte_mbuf) + RTE_PKTMBUF_HEADROOM)
#define NB_MBUF 8192

#define ENABLED_PORT_MASK 0xFFFF
#define RX_QUEUE_PER_LCORE 8


/*
 *  * RX and TX Prefetch, Host, and Write-back threshold values should be
 *   * carefully set for optimal performance. Consult the network
 *    * controller's datasheet and supporting DPDK documentation for guidance
 *     * on how these parameters should be set.
 *      */
#define RX_PTHRESH 8 /**< Default values of RX prefetch threshold reg. */
#define RX_HTHRESH 8 /**< Default values of RX host threshold reg. */
#define RX_WTHRESH 4 /**< Default values of RX write-back threshold reg. */

/*
 *  * These default values are optimized for use with the Intel(R) 82599 10 GbE
 *   * Controller and the DPDK ixgbe PMD. Consider using other values for other
 *    * network controllers and/or network drivers.
 *     */
#define TX_PTHRESH 36 /**< Default values of TX prefetch threshold reg. */
#define TX_HTHRESH 0  /**< Default values of TX host threshold reg. */
#define TX_WTHRESH 0  /**< Default values of TX write-back threshold reg. */

#define MAX_PKT_BURST 32
#define BURST_TX_DRAIN 200000ULL /* around 100us at 2 Ghz */

#define SOCKET0 0

/*
 *  * Configurable number of RX/TX ring descriptors
 *   */
#define RTE_TEST_RX_DESC_DEFAULT 128
#define RTE_TEST_TX_DESC_DEFAULT 512
//static uint16_t nb_rxd = RTE_TEST_RX_DESC_DEFAULT;
//static uint16_t nb_txd = RTE_TEST_TX_DESC_DEFAULT;

/* ethernet addresses of ports */
//static struct ether_addr l2fwd_ports_eth_addr[DPDK_MAX_PORTS];

/* mask of enabled ports */
//static uint32_t l2fwd_enabled_port_mask = 0;

/* list of enabled ports */
//static uint32_t l2fwd_dst_ports[DPDK_MAX_PORTS];

//static unsigned int l2fwd_rx_queue_per_lcore = 1;

#define MAX_PKT_BURST 32
struct mbuf_table {
    unsigned len;
    struct rte_mbuf *m_table[MAX_PKT_BURST];
};

#define MAX_RX_QUEUE_PER_LCORE 16
#define MAX_TX_QUEUE_PER_PORT 16
struct lcore_queue_conf {
     
    unsigned n_rx_queue;
    unsigned rx_queue_list[MAX_RX_QUEUE_PER_LCORE];
    unsigned tx_queue_id;
    struct mbuf_table tx_mbufs[DPDK_MAX_PORTS];

} __rte_cache_aligned;
//struct lcore_queue_conf lcore_queue_conf[RTE_MAX_LCORE];

/* Per-port statistics struct */
typedef struct dpdk_stat {
    uint64_t recv;
    uint64_t drop;
}dpdk_stat;
//struct l2fwd_port_statistics port_statistics[DPDK_MAX_PORTS];

/* A tsc-based timer responsible for triggering statistics printout */
//#define TIMER_MILLISECOND 2000000ULL /* around 1ms at 2 Ghz */
//#define MAX_TIMER_PERIOD 86400 /* 1 day max */
//static int64_t timer_period = 10 * TIMER_MILLISECOND * 1000; 

#define DPDK_ERRBUF_SIZE 256

typedef struct _dpdk_context
{
    char *file;
    DAQ_Mode mode; 
    int snaplen;
    int promisc_flag;
    int timeout;
    int delayed_open;
    u_int breakloop;
    struct rte_mempool *pktmbuf_pool;
    //struct ether_addr ports_eth_addr[DPDK_MAX_PORTS];
    //uint32_t dst_ports[DPDK_MAX_PORTS];
    
    struct lcore_queue_conf lcore_queue_conf[RTE_MAX_LCORE];

    char errbuf[DPDK_ERRBUF_SIZE]; 

    DAQ_Analysis_Func_t analysis_func;
    DAQ_Stats_t stats;
    DAQ_State state;

    struct lcore_queue_conf *qconf;
    uint32_t base_recv[MAX_RX_QUEUE_PER_LCORE];
    uint32_t base_drop[MAX_RX_QUEUE_PER_LCORE];
}Dpdk_Context_t;

typedef DAQ_Verdict (*DAQ_Analysis_Func_t)(void *user, const DAQ_PktHdr_t *hdr, const uint8_t *data);



typedef struct _daq_module DAQ_Module_t;



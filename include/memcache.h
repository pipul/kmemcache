#ifndef __MEMCACHE_H
#define __MEMCACHE_H

#include <linux/types.h>

/* time relative to server start. */
typedef unsigned int rel_time_t;

typedef enum {
	local_transport,
	tcp_transport,
	udp_transport
} net_transport_t;

#define IS_UDP(x) (x == udp_transport)

typedef enum {
	ascii_prot,
	binary_prot,
	negotiating_prot
} protocol_t;

typedef enum {
	T_MEMD_INITIAL_MALLOC,
	T_MEMD_SLABS_LIMIT,
} env_t;

typedef env_t	ask_env_t;

typedef struct {
	env_t	env;
	char	data[0];
} ack_env_t;

#define MAX_VERBOSITY_LEVEL 2
#define DEFAULT_HASH_BULK_MOVE	1
#define DEFAULT_SLAB_BULK_CHECK	1

typedef struct {
	net_transport_t trans;

	__s32 family;
	__s32 type;
	__s32 protocol;

	__s32 addrlen;
	__u8  addr[0];
} sock_entry_t __attribute__((aligned(sizeof(int))));

typedef struct {
	__s32 port;
	__s32 udpport;
	__s32 access;
	__s32 backlog;

	__s32 verbose;
	__u64 maxbytes;
	__s32 maxconns;
	__s32 num_threads_per_udp;
	__s32 reqs_per_event;
	__s32 evict_to_free;

	__s32 chunk_size;
	__s32 item_size_max;
	__s32 slab_automove;
	__s32 hashpower_init;
	__s32 hash_bulk_move;
	__s32 slab_bulk_check;
	rel_time_t oldest_live;
	protocol_t binding_protocol;
	__s32 factor_numerator;
	__s32 factor_denominator;

	__u8  use_cas;
	__u8  sasl;
	__u8  maxconns_fast;
	__u8  slab_reassign;
	__s8  prefix_delimiter;
	__u8  detail_enabled;
	__u8  shutdown_command;
	__u8  preallocate;

	/*
	 * flags --- describe the data's value
	 *
	 * UNIX_SOCK: data ---> unix domain's absolute path
	 * PORT_FILE: data ---> n * sock_entry_t + port_file_path
	 */
#define UNIX_SOCK (0x1 << 1) 
#define PORT_FILE (0x1 << 2)
	__s8  flags;
	__u16 len;
	__s8  data[0];
} settings_init_t __attribute__((aligned(sizeof(int))));

#define KMC_V_MSG	(sizeof(struct cn_msg))
#define KMC_V_ASK_ENV	(KMC_V_MSG + sizeof(ask_env_t))
#define KMC_V_ACK_ENV	(KMC_V_MSG + sizeof(ack_env_t))
#define KMC_V_BH_STATUS	(KMC_V_MSG + sizeof(__s32))

#ifdef __KERNEL__

struct settings {
	__s32 port;
	__s32 udpport;
	__s32 access;
	__s32 backlog;

	__s32 verbose;
	__u64 maxbytes;
	__s32 maxconns;
	__s32 num_threads_per_udp;
	__s32 reqs_per_event;
	__s32 evict_to_free;

	__s32 chunk_size;
	__s32 item_size_max;
	__s32 slab_automove;
	__s32 hashpower_init;
	__s32 hash_bulk_move;
	__s32 slab_bulk_check;
	rel_time_t oldest_live;
	protocol_t binding_protocol;
	__s32 factor_numerator;
	__s32 factor_denominator;

	__u8  use_cas;
	__u8  sasl;
	__u8  maxconns_fast;
	__u8  slab_reassign;
	__s8  prefix_delimiter;
	__u8  detail_enabled;
	__u8  shutdown_command;
	__u8  preallocate;
	__s8  flags;	/* UNIX SOCK? */
} __attribute__((aligned(sizeof(int))));

extern struct settings settings;

#endif /* __KERNEL__ */
#endif /* __MEMCACHE_H */

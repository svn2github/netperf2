/*
        Copyright (C) 1993, Hewlett-Packard Company
*/

 /* This file contains the test-specific definitions for netperf's BSD */
 /* sockets tests */

#define PAD_TIME 2

struct	tcp_stream_request_struct {
  int	send_buf_size;
  int	recv_buf_size;	/* how big does the client want it - the */
			/* receive socket buffer that is */ 
  int	receive_size;   /* how many bytes do we want to receive at one */
			/* time? */ 
  int	recv_alignment; /* what is the alignment of the receive */
			/* buffer? */ 
  int	recv_offset;    /* and at what offset from that alignment? */ 
  int	no_delay;       /* do we disable the nagle algorithm for send */
			/* coalescing? */ 
  int	measure_cpu;	/* does the client want server cpu utilization */
			/* measured? */ 
  float	cpu_rate;	/* do we know how fast the cpu is already? */ 
  int	test_length;	/* how long is the test?		*/
  int	so_rcvavoid;    /* do we want the remote to avoid copies on */
			/* receives? */ 
  int	so_sndavoid;    /* do we want the remote to avoid send copies? */
  int   dirty_count;    /* how many integers in the receive buffer */
			/* should be made dirty before calling recv? */  
  int   clean_count;    /* how many integers should be read from the */
			/* recv buffer before calling recv? */ 
};

struct	tcp_stream_response_struct {
  int	recv_buf_size;	/* how big does the client want it	*/
  int	receive_size;
  int	no_delay;
  int	measure_cpu;	/* does the client want server cpu	*/
  int	test_length;	/* how long is the test?		*/
  int	send_buf_size;
  int	data_port_number;	/* connect to me here	*/
  float	cpu_rate;		/* could we measure	*/
  int	so_rcvavoid;	/* could the remote avoid receive copies? */ 
  int	so_sndavoid;	/* could the remote avoid send copies? */
};

struct tcp_stream_results_struct {
  double         bytes_received;
  unsigned int	 recv_calls;	
  float	         elapsed_time;	/* how long the test ran */
  float	         cpu_util;	/* -1 if not measured */
  float	         serv_dem;	/* -1 if not measured */
  int            cpu_method;    /* how was cpu util measured? */
};

struct	tcp_rr_request_struct {
  int	recv_buf_size;	/* how big does the client want it	*/
  int	send_buf_size;
  int	recv_alignment;
  int	recv_offset;
  int	send_alignment;
  int	send_offset;
  int	request_size;
  int	response_size;
  int	no_delay;
  int	measure_cpu;	/* does the client want server cpu	*/
  float	cpu_rate;	/* do we know how fast the cpu is?	*/
  int	test_length;	/* how long is the test?		*/
  int	so_rcvavoid;    /* do we want the remote to avoid receive */
			/* copies? */ 
  int	so_sndavoid;    /* do we want the remote to avoid send copies? */
};

struct	tcp_rr_response_struct {
  int	recv_buf_size;	/* how big does the client want it	*/
  int	no_delay;
  int	measure_cpu;	/* does the client want server cpu	*/
  int	test_length;	/* how long is the test?		*/
  int	send_buf_size;
  int	data_port_number;	/* connect to me here	*/
  float	cpu_rate;		/* could we measure	*/
  int	so_rcvavoid;	/* could the remote avoid receive copies? */
  int	so_sndavoid;	/* could the remote avoid send copies? */
};

struct tcp_rr_results_struct {
  unsigned int  bytes_received;	/* ignored initially */
  unsigned int	recv_calls;	/* ignored initially */
  unsigned int	trans_received;	/* not ignored  */
  float	        elapsed_time;	/* how long the test ran */
  float	        cpu_util;	/* -1 if not measured */
  float	        serv_dem;	/* -1 if not measured */
  int           cpu_method;    /* how was cpu util measured? */
};

struct	tcp_conn_rr_request_struct {
  int	recv_buf_size;	/* how big does the client want it	*/
  int	send_buf_size;
  int	recv_alignment;
  int	recv_offset;
  int	send_alignment;
  int	send_offset;
  int	request_size;
  int	response_size;
  int	no_delay;
  int	measure_cpu;	/* does the client want server cpu	*/
  float	cpu_rate;	/* do we know how fast the cpu is?	*/
  int	test_length;	/* how long is the test?		*/
  int	so_rcvavoid;    /* do we want the remote to avoid receive */
			/* copies? */ 
  int	so_sndavoid;    /* do we want the remote to avoid send copies? */
};


struct	tcp_conn_rr_response_struct {
  int	recv_buf_size;	/* how big does the client want it	*/
  int	no_delay;
  int	measure_cpu;	/* does the client want server cpu	*/
  int	test_length;	/* how long is the test?		*/
  int	send_buf_size;
  int	data_port_number;	/* connect to me here	*/
  float	cpu_rate;		/* could we measure	*/
  int	so_rcvavoid;	/* could the remote avoid receive copies? */
  int	so_sndavoid;	/* could the remote avoid send copies? */
};

struct tcp_conn_rr_results_struct {
  unsigned int	bytes_received;	/* ignored initially */
  unsigned int	recv_calls;	/* ignored initially */
  unsigned int	trans_received;	/* not ignored  */
  float	elapsed_time;	/* how long the test ran */
  float	cpu_util;	/* -1 if not measured */
  float	serv_dem;	/* -1 if not measured */
  int   cpu_method;    /* how was cpu util measured? */
};

struct	udp_stream_request_struct {
  int	recv_buf_size;
  int	message_size;
  int	recv_alignment;
  int	recv_offset;
  int	checksum_off;
  int	measure_cpu;
  float	cpu_rate;
  int	test_length;
  int	so_rcvavoid;    /* do we want the remote to avoid receive */
			/* copies? */ 
  int	so_sndavoid;    /* do we want the remote to avoid send copies? */
};

struct	udp_stream_response_struct {
  int	recv_buf_size;
  int	send_buf_size;
  int	measure_cpu;
  int	test_length;
  int	data_port_number;
  float	cpu_rate;
  int	so_rcvavoid;	/* could the remote avoid receive copies? */
  int	so_sndavoid;	/* could the remote avoid send copies? */
};

struct	udp_stream_results_struct {
  unsigned int	messages_recvd;
  unsigned int	bytes_received;
  float	        elapsed_time;
  float	        cpu_util;
  int           cpu_method;    /* how was cpu util measured? */
};


struct	udp_rr_request_struct {
  int	recv_buf_size;	/* how big does the client want it	*/
  int	send_buf_size;
  int	recv_alignment;
  int	recv_offset;
  int	send_alignment;
  int	send_offset;
  int	request_size;
  int	response_size;
  int	no_delay;
  int	measure_cpu;	/* does the client want server cpu	*/
  float	cpu_rate;	/* do we know how fast the cpu is?	*/
  int	test_length;	/* how long is the test?		*/
  int	so_rcvavoid;    /* do we want the remote to avoid receive */
			/* copies? */ 
  int	so_sndavoid;    /* do we want the remote to avoid send copies? */
};

struct	udp_rr_response_struct {
  int	recv_buf_size;	/* how big does the client want it	*/
  int	no_delay;
  int	measure_cpu;	/* does the client want server cpu	*/
  int	test_length;	/* how long is the test?		*/
  int	send_buf_size;
  int	data_port_number;	/* connect to me here	*/
  float	cpu_rate;		/* could we measure	*/
  int	so_rcvavoid;	/* could the remote avoid receive copies? */
  int	so_sndavoid;	/* could the remote avoid send copies? */
};

struct udp_rr_results_struct {
  unsigned int	bytes_received;	/* ignored initially */
  unsigned int	recv_calls;	/* ignored initially */
  unsigned int	trans_received;	/* not ignored  */
  float	        elapsed_time;	/* how long the test ran */
  float	        cpu_util;	/* -1 if not measured */
  float	        serv_dem;	/* -1 if not measured */
  int           cpu_method;    /* how was cpu util measured? */
};



/*
 
              Copyright (C) 1993 Hewlett-Packard Company
                         ALL RIGHTS RESERVED.
 
  The enclosed software and documention includes copyrighted works of
  Hewlett-Packard Co. For as long as you comply with the following
  limitations, you are hereby authorized to (i) use, reproduce, and
  modify the software and documentation, and to (ii) distribute the
  software and documentation, including modifications, for
  non-commercial purposes only.
      
  1.  The enclosed software and documentation is made available at no
      charge in order to advance the general development of
      high-performance networking products.
 
  2.  You may not delete any copyright notices contained in the
      software or documentation. All hard copies, and copies in
      source code or object code form, of the software or
      documentation (including modifications) must contain at least
      one of the copyright notices.
 
  3.  The enclosed software and documentation has not been subjected
      to testing and quality control and is not a Hewlett-Packard Co.
      product. At a future time, Hewlett-Packard Co. may or may not
      offer a version of the software and documentation as a product.
  
  4.  THE SOFTWARE AND DOCUMENTATION IS PROVIDED "AS IS".
      HEWLETT-PACKARD COMPANY DOES NOT WARRANT THAT THE USE,
      REPRODUCTION, MODIFICATION OR DISTRIBUTION OF THE SOFTWARE OR
      DOCUMENTATION WILL NOT INFRINGE A THIRD PARTY'S INTELLECTUAL
      PROPERTY RIGHTS. HP DOES NOT WARRANT THAT THE SOFTWARE OR
      DOCUMENTATION IS ERROR FREE. HP DISCLAIMS ALL WARRANTIES,
      EXPRESS AND IMPLIED, WITH REGARD TO THE SOFTWARE AND THE
      DOCUMENTATION. HP SPECIFICALLY DISCLAIMS ALL WARRANTIES OF
      MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
  
  5.  HEWLETT-PACKARD COMPANY WILL NOT IN ANY EVENT BE LIABLE FOR ANY
      DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES
      (INCLUDING LOST PROFITS) RELATED TO ANY USE, REPRODUCTION,
      MODIFICATION, OR DISTRIBUTION OF THE SOFTWARE OR DOCUMENTATION.
 
*/
char	netserver_id[]="@(#)netserver.c (c) Copyright 1993, \
Hewlett-Packard Company. Version 1.9alphaPL4";

 /***********************************************************************/
 /*									*/
 /*	netserver.c							*/
 /*									*/
 /*	This is the server side code for the netperf test package. It	*/
 /* will operate either stand-alone, or as a child of inetd. In this	*/
 /* way, we insure that it can be installed on systems with or without	*/
 /* root permissions (editing inetd.conf). Essentially, this code is	*/
 /* the analog to the netsh.c code.					*/
 /*									*/
 /***********************************************************************/


/************************************************************************/
/*									*/
/*	Global include files						*/
/*									*/
/************************************************************************/
#include <sys/types.h>
#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <sys/ipc.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>

#include "netlib.h"
#include "nettest_bsd.h"
#include "nettest_dlpi.h"
#include "netsh.h"

 /* some global variables */

FILE	*afp;
short	listen_port_num;
extern	char	*optarg;
extern	int	optind, opterr;

#define SERVER_ARGS "dp:"

 /* This routine implements the "main event loop" of the netperf	*/
 /* server code. Code above it will have set-up the control connection	*/
 /* so it can just merrily go about its business, which is to		*/
 /* "schedule" performance tests on the server.				*/

void 
process_requests()
{
  
  float	temp_rate;
  
  
  while (1) {
    recv_request();
    if (debug)
      dump_request();
    
    switch (netperf_request->request_type) {
      
    case DEBUG_ON:
      netperf_response->response_type = DEBUG_OK;
      if (!debug)
	debug++;
      dump_request();
      send_response();
      break;
      
    case DEBUG_OFF:
      if (debug)
	debug--;
      netperf_response->response_type = DEBUG_OK;
      fclose(where);
      send_response();
      break;
      
    case CPU_CALIBRATE:
      netperf_response->response_type = CPU_CALIBRATE;
      temp_rate = calibrate_local_cpu(0.0);
      bcopy((char *)&temp_rate,
	    (char *)netperf_response->test_specific_data,
	    sizeof(temp_rate));
      send_response();
      break;
      
    case DO_TCP_STREAM:
      recv_tcp_stream();
      break;
      
    case DO_TCP_RR:
      recv_tcp_rr();
      break;
      
    case DO_TCP_CRR:
      recv_tcp_conn_rr();
      break;
      
    case DO_UDP_STREAM:
      recv_udp_stream();
      break;
      
    case DO_UDP_RR:
      recv_udp_rr();
      break;
      
#ifdef DO_DLPI

    case DO_DLPI_CO_RR:
      recv_dlpi_co_rr();
      break;
      
    case DO_DLPI_CL_RR:
      recv_dlpi_cl_rr();
      break;

    case DO_DLPI_CO_STREAM:
      recv_dlpi_co_stream();
      break;

    case DO_DLPI_CL_STREAM:
      recv_dlpi_cl_stream();
      break;

#endif /* DO_DLPI */

#ifdef DO_UNIX

    case DO_STREAM_STREAM:
      recv_stream_stream();
      break;
      
    case DO_STREAM_RR:
      recv_stream_rr();
      break;
      
    case DO_DG_STREAM:
      recv_dg_stream();
      break;
      
    case DO_DG_RR:
      recv_dg_rr();
      break;
      
#endif /* DO_UNIX */

#ifdef DO_FORE

    case DO_FORE_STREAM:
      recv_fore_stream();
      break;
      
    case DO_FORE_RR:
      recv_fore_rr();
      break;
      
#endif /* DO_FORE */

    default:
      fprintf(where,"unknown test\n");
      fflush(where);
      netperf_response->serv_errno=998;
      send_response();
      break;
      
    }
  }
}

/*********************************************************************/
/*				       		                     */
/*	set_up_server()						     */
/*								     */
/* set-up the server listen socket. we only call this routine if the */
/* user has specified a port number on the command line.             */
/*								     */
/*********************************************************************/
/*KC*/

void set_up_server()
{ 
  struct  servent         *sp;            /* server entity           */
  struct sockaddr_in 	server;
  struct sockaddr_in 	peeraddr;

  int server_control;
  int peeraddr_len;
  int ppid,pid;
  
  server.sin_port = htons(listen_port_num);
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_family = AF_INET;
  
  server_control = socket (AF_INET,SOCK_STREAM,0);
  if (server_control < 0)
    {
      perror("server_set_up: creating the socket");
      exit(1);
    }
  if (bind (server_control,
	    (struct sockaddr *)&server, 
	    sizeof(struct sockaddr_in)) == -1)
    {
      perror("server_set_up: binding the socket");
      exit (1);
    }
  if (listen (server_control,5) == -1)
    {
      perror("server_set_up: listening");
      exit(1);
    }
  
  /*
    setpgrp();
    */

  switch (fork())
    {
    case -1:  	
      perror("netperf server error");
      exit(1);
      
    case 0:	
      close(stdin);
      close(stderr);
      setpgrp();
      signal(SIGCLD, SIG_IGN);
      
      for (;;)
	{
	  peeraddr_len = sizeof(peeraddr);
	  if ((server_sock=accept(server_control,
				  (struct sockaddr *)&peeraddr,
				  &peeraddr_len)) == -1)
	    {
	      printf("server_control: accept failed\n");
	      exit(1);
	    }
	  signal(SIGCLD, SIG_IGN);
	  
	  switch (fork())
	    {
	    case -1:
	      exit(1);
	    case 0:
	      close(server_control);
	      process_requests();
	      exit(0);
	      break;
	    default:
	      close(server_sock);
	      break;
	    }
	} /*for*/
      break; /*case 0*/
      
    default: 
      exit (0);
      
    }
  
}


main(argc, argv)
int argc;
char *argv[];
{
  struct protoent *pp;
  char	*debug_file;
  int	c;

  int spin = 1;
  
  netlib_init();
  
  /* Scan the command line to see if we are supposed to set-up our own */
  /* listen socket instead of relying on inetd. */
  
  while ((c = getopt(argc, argv, SERVER_ARGS)) != EOF) {
    switch (c) {
    case '?':
    case 'h':
      print_netserver_usage();
      exit(1);
    case 'd':
      /* we want to set the debug file name sometime */
      debug++;
      break;
    case 'p':
      /* we want to open a listen socket at a */
      /* specified port number */
      listen_port_num = atoi(optarg);
      printf("Starting netserver at port %d\n",listen_port_num);
      break;
    }
  }
  
  if ((where = fopen("/tmp/netperf.debug", "w")) == NULL) {
    if (listen_port_num) {
      perror("netserver: debug file");
    }
    exit(1);
  }
  
  chmod("/tmp/netperf.debug",0777);
  
  /* if we were given a port number, then we should open a */
  /* socket and hang listens off of it. otherwise, we should go */
  /* straight into processing requests. the do_listen() routine */
  /* will sit in an infinite loop accepting connections and */
  /* forking child processes. the child processes will call */
  /* process_requests */
  
  if (listen_port_num) {
    set_up_server();
  }
  else {
    process_requests();
  };
}

#
# @(#)Makefile	2.0PL3	07/26/95
#
# Makefile to build netperf benchmark tool
#
# for those folks running csh, this may help with makes
#SHELL="/bin/sh"

#
# This tells the script where the executables and scripts are supposed
# to go. Some people might be used to "/usr/etc/net_perf", but
# for the rest of the world, it is probably better to put the binaries
# in /usr/local/netperf or /opt/netperf
#
#NETPERF_HOME = /usr/local/netperf
NETPERF_HOME = /opt/netperf

# The compiler on your system might be somewhere else, and/or have
# a different name.
#
# /bin/cc              - the location on HP-UX 9.X and previous
# /usr/bin/cc          - the location on HP-UX 10.0 and some other
#                        platforms (IRIX, OSF/1)
# /opt/SUNWspro/bin/cc - the unbundled C compiler under Solaris
# cc                   - if your paths are set, this may be all you 
#                        need
# 
# one most systems, netperf spends very little time in user code, and
# most of its time in the kernel, so I *suspect* that different
# optimization levels won't make very much of a difference. however,
# might as well compile -O... If you are using the HP-UX unbundled
# compiler, this will generate a warning about an unsupported option.
# You may safely ignore that warning.
#

CC = cc -O

# Adding flags to CFLAGS enables some non-mainline features. For
# more information, please consult the source code.
# -Ae         - enable ANSI C on HP-UX with namespace extensions. ANSI
#               compilation is required for -DHISTOGRAM
# -DDIRTY     - include code to dirty buffers before calls to send
# -DHISTOGRAM - include code to keep a histogram of r/r times or
#               time spent in send()
# -DINTERVALS - include code to allow pacing of sends in a UDP or TCP 
#               test. this may have unexpected results on non-HP-UX
#               systems as I have not learned how to emulated the
#               functionality found within the __hpux defines in
#               the catcher() routine of netlib.c
# -DDO_DLPI   - include code to test the DLPI interface (may also 
#               require changes to LIBS. see below)
# -DDO_UNIX   - include code to test Unix Domain sockets
# -DDO_FORE   - include code to test the Fore ATM API (requires 
#               -DFORE_KLUDGE and -I/usr/fore/include)
# -DDO_HIPPI  - include code to test the HP HiPPI LLA interface. if 
#               you just want vanilla HP LLA, then also add
#               -DBUTNOTHIPPI
# -D$(LOG_FILE) Specifies where netserver should put its debug output 
#               when debug is enabled
# -DUSE_LOOPER- use looper or soaker processes to measure CPU
#               utilization. these will be forked-off at the
#               beginning. if you are running this way, it is
#               important to see how much impact these have on the
#               measurement. A loopback test on uniprocessor should be
#               able to consume ~100% of the CPU, and the difference
#               between throughput with USE_LOOPER CPU and without
#               should be small for a real network. if it is not, then
#               some work proably needs to be done on reducing the
#               priority of the looper processes.
# -DUSE_PSTAT - If used on HP-UX 10.0 and later, this will make CPU
#               utilization measurements with some information
#               returned byt he 10.X pstat() call. This is very
#               accurate, and should have no impact on the
#               measurement. Astute observers will notice that the
#               LOC_CPU and REM_CPU rates with this method look
#               remarkably close to the clockrate of the machine :)
# -DDO_IPV6   - Include tests which use a sockets interface to IPV6.
#               The control connection remains IPV4

LOG_FILE=DEBUG_LOG_FILE="\"/tmp/netperf.debug\""
CFLAGS = -D$(LOG_FILE) -DUSE_LOOPER

# Some platforms, and some options, require additional libraries.
# you can add to the "LIBS =" line to accomplish this. if you find
# that additional libs are required for your platform, please let
# me know. rick jones <raj@cup.hp.com>
# -lstr                 - required for -DDO_DLPI on HP-UX 9.X
# -lsocket -lnsl -lelf  - required for Solaris 2.3 (2.4?)
# -L/usr/fore/lib -latm - required on all platforms for the Fore
#                         ATM API tests
# -lelf                 - on IRIX 5.2 to resolve nlist. with 2.0PL1
#                         and later, this should not be needed since
#                         netperf no longer uses nlist()
# -lsys5                - on Digital Unix (OSF) this helps insure that
#                         netserver processes are reaped?
# -lm                   - required for ALL platforms
# -lxti                 - required for -DDO_XTI on HP_UX 10.X

LIBS= -lm

# ---------------------------------------------------------------
# it should not be the case that anything below this line needs to
# be changed. if it does, please let me know.
# rick jones <raj@cup.hp.com>


SHAR_SOURCE_FILES = netlib.c netlib.h netperf.c netserver.c \
		    netsh.c netsh.h \
		    nettest_bsd.c nettest_bsd.h \
		    nettest_dlpi.c nettest_dlpi.h \
		    nettest_unix.c nettest_unix.h \
		    nettest_fore.c nettest_fore.h \
		    nettest_hippi.c nettest_hippi.h \
                    nettest_xti.c nettest_xti.h \
                    nettest_ipv6.c nettest_ipv6.h \
                    hist.h \
		    makefile makefile.win32

ZIP_SOURCE_FILES  = netlib.c netlib.h netperf.c netserver.c \
		    netsh.c netsh.h \
		    nettest_bsd.c nettest_bsd.h \
                    hist.h \
		    makefile.win32

SHAR_EXE_FILES    = ACKNWLDGMNTS COPYRIGHT README Release_Notes \
                    netperf.ps \
		    netperf.man netserver.man

SHAR_SCRIPT_FILES = tcp_stream_script udp_stream_script \
                    tcp_rr_script udp_rr_script tcp_range_script \
                    snapshot_script arr_script

NETSERVER_OBJS	  = netserver.o nettest_bsd.o nettest_dlpi.o \
                    nettest_unix.o netlib.o netsh.o nettest_fore.o \
		    nettest_hippi.o nettest_xti.o nettest_ipv6.o

NETPERF_OBJS	  = netperf.o netsh.o netlib.o nettest_bsd.o \
                    nettest_dlpi.o nettest_unix.o nettest_fore.o \
		    nettest_hippi.o nettest_xti.o nettest_ipv6.o

NETPERF_SCRIPTS   = tcp_range_script tcp_stream_script tcp_rr_script \
                    udp_stream_script udp_rr_script \
                    snapshot_script

SCAF_FILES	  = spiff spiff.1 scaf_script scafsnapshot_script \
		    baselines/*

all: netperf netserver

netperf:	$(NETPERF_OBJS)
		$(CC) -o $@ $(NETPERF_OBJS) $(LIBS)

netserver:	$(NETSERVER_OBJS)
		$(CC) -o $@ $(NETSERVER_OBJS) $(LIBS)

netperf.o:	netperf.c netsh.h makefile

netsh.o:	netsh.c netsh.h nettest_bsd.h netlib.h makefile

netlib.o:	netlib.c netlib.h netsh.h makefile

nettest_bsd.o:	nettest_bsd.c nettest_bsd.h netlib.h netsh.h makefile

nettest_dlpi.o:	nettest_dlpi.c nettest_dlpi.h netlib.h netsh.h makefile

nettest_unix.o:	nettest_unix.c nettest_unix.h netlib.h netsh.h makefile

nettest_fore.o: nettest_fore.c nettest_fore.h netlib.h netsh.h makefile

nettest_hippi.o: nettest_hippi.c nettest_hippi.h netlib.h netsh.h makefile

nettest_xti.o:   nettest_xti.c nettest_xti.h netlib.h netsh.h makefile

nettest_ipv6.o:  nettest_ipv6.c nettest_ipv6.h netlib.h netsh.h makefile

netserver.o:	netserver.c nettest_bsd.h netlib.h makefile

install:	netperf netserver
		chmod -w *.[ch]
		chmod +x $(NETPERF_SCRIPTS)
		cp netperf $(NETPERF_HOME)
		cp netserver $(NETPERF_HOME)
		cp $(NETPERF_SCRIPTS) $(NETPERF_HOME)
clean:
	rm -f *.o netperf netserver core

extraclean:
	rm -f *.o netperf netserver core netperf.tar.gz netperf.shar \
	netperf_src.shar

deinstall:
	echo do this to deinstall rm -rf $(NETPERF_HOME)/*

netperf_src.shar: $(SHAR_SOURCE_FILES)
	shar -bcCsZ $(SHAR_SOURCE_FILES) > netperf_src.shar

netperf.shar:	$(SHAR_SOURCE_FILES) $(SHAR_EXE_FILES) $(SHAR_SCRIPT_FILES)
	shar -bcCsZ $(SHAR_SOURCE_FILES) $(SHAR_EXE_FILES) \
		$(SHAR_SCRIPT_FILES) > netperf.shar

netperf.zip:    $(ZIP_SOURCE_FILES) $(SHAR_EXE_FILES)
	zip netperf.zip $(ZIP_SOURCE_FILES) $(SHAR_EXE_FILES)

netperf.tar:	$(SHAR_EXE_FILES) \
		$(SHAR_SCRIPT_FILES) $(SHAR_SOURCE_FILES)
	tar -cf netperf.tar $(SHAR_EXE_FILES) \
		$(SHAR_SCRIPT_FILES) $(SHAR_SOURCE_FILES)
	gzip netperf.tar

netperf-scaf.tar:	$(SHAR_EXE_FILES) \
			$(SHAR_SCRIPT_FILES) \
			$(SCAF_FILES)
	tar -cf netperf-scaf.tar \
		$(SHAR_EXE_FILES) \
		$(SHAR_SCRIPT_FILES) $(SCAF_FILES)
	compress netperf-scaf.tar
	
netperf-scaf.shar:	$(SHAR_EXE_FILES) \
			$(SHAR_SCRIPT_FILES) \
			$(SCAF_FILES)
	shar -bcCsZ $(SHAR_EXE_FILES) \
		$(SHAR_SCRIPT_FILES) $(SCAF_FILES) > netperf-scaf.shar

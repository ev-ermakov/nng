#
# Copyright 2021 Staysail Systems, Inc. <info@staysail.tech>
#
# This software is supplied under the terms of the MIT License, a
# copy of which should be located in the distribution where this
# file was obtained (LICENSE.txt).  A copy of the license may also be
# found online at https://opensource.org/licenses/MIT.
#

#  POSIX

if nng_platform_posix
  nng_lib_defs += [
    '_GNU_SOURCE',
  ]

  if host_system == 'sunos'
    nng_lib_defs += '_POSIX_PTHREAD_SEMANTICS'
  endif

  nng_check_func += [
    ['lockf', 'unistd.h', 'NNG_HAVE_LOCKF'],
    ['flock', 'sys/file.h', 'NNG_HAVE_FLOCK'],
    ['getrandom', 'sys/random.h', 'NNG_HAVE_GETRANDOM'],
    ['arc4random_buf', 'stdlib.h', 'NNG_HAVE_ARC4RANDOM'],

    # ['clock_gettime', 'time.h', 'NNG_HAVE_CLOCK_GETTIME'],
    # ['sem_wait', 'semaphore.h', 'NNG_HAVE_SEMAPHORE_PTHREAD'],
    # ['pthread_atfork', 'pthread.h', 'NNG_HAVE_PTHREAD_ATFORK_PTHREAD'],
    # ['pthread_set_name_np', 'pthread.h', 'NNG_HAVE_PTHREAD_SET_NAME_NP'],
    # ['pthread_setname_np', 'pthread.h', 'NNG_HAVE_PTHREAD_SETNAME_NP'],
    # ['gethostbyname', 'sys/socket.h', 'NNG_HAVE_LIBNSL'],
    # ['socket', 'sys/socket.h', 'NNG_HAVE_LIBSOCKET'],

    ['backtrace_symbols_fd', 'execinfo.h', 'NNG_HAVE_BACKTRACE'],
    ['eventfd', 'sys/eventfd.h', 'NNG_HAVE_EVENTFD'],
    ['kqueue', 'sys/event.h', 'NNG_HAVE_KQUEUE'],
    ['port_create', 'port.h', 'NNG_HAVE_PORT_CREATE'],
    ['epoll_create', 'sys/epoll.h', 'NNG_HAVE_EPOLL'],
    ['epoll_create1', 'sys/epoll.h', 'NNG_HAVE_EPOLL_CREATE1']
  ]

  nng_platform_srcs += files(
    'posix_alloc.c',
    'posix_atomic.c',
    'posix_clock.c',
    'posix_debug.c',
    'posix_file.c',
    'posix_ipcconn.c',
    'posix_ipcdial.c',
    'posix_ipclisten.c',
    'posix_pipe.c',
    'posix_resolv_gai.c',
    'posix_sockaddr.c',
    'posix_tcpconn.c',
    'posix_tcpdial.c',
    'posix_tcplisten.c',
    'posix_thread.c',
    'posix_udp.c'
  )

  if cc.has_function('port_create', prefix: '#include <port.h>')
    nng_platform_srcs += files('posix_pollq_port.c')
  elif cc.has_function('kqueue', prefix: '#include <sys/event.h>')
    nng_platform_srcs += files('posix_pollq_kqueue.c')
  elif cc.has_function('epoll_create', prefix: '#include <sys/epoll.h>') and \
       cc.has_function('eventfd', prefix: '#include <sys/eventfd.h>')
    nng_platform_srcs += files('posix_pollq_epoll.c')
  else
    nng_platform_srcs += files('posix_pollq_poll.c')
  endif

  if cc.has_function('arc4random_buf', prefix: '#include <stdlib.h>')
    nng_platform_srcs += files('posix_rand_arc4random.c')
  elif cc.has_function('getrandom', prefix: '#include <sys/random.h>')
    nng_platform_srcs += files('posix_rand_getrandom.c')
  else
    nng_platform_srcs += files('posix_rand_urandom.c')
  endif

  nng_deps += dependency('threads', required: true)
endif

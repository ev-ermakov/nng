#
# Copyright 2021 Staysail Systems, Inc. <info@staysail.tech>
#
# This software is supplied under the terms of the MIT License, a
# copy of which should be located in the distribution where this
# file was obtained (LICENSE.txt).  A copy of the license may also be
# found online at https://opensource.org/licenses/MIT.
#

#  Windows

if nng_platform_windows
  error('TODO')

  if not cc.has_function('snprintf', prefix: '#include <stdio.h>') and
         cc.has_function('InitializeConditionVariable', prefix: '#include <windows.h')
     error('''
       Modern Windows API support is missing.
       Versions of Windows prior to Vista are not supported.
       Further, the 32-bit MinGW environment is not supported.
       Ensure you have at least Windows Vista or newer, and are
       using either Visual Studio 2013 or newer or MinGW-W64.''')
  endif

  nng_platform_srcs += files(
    'win_clock.c',
    'win_debug.c',
    'win_file.c',
    'win_io.c',
    'win_ipcconn.c',
    'win_ipcdial.c',
    'win_ipclisten.c',
    'win_pipe.c',
    'win_rand.c',
    'win_resolv.c',
    'win_sockaddr.c',
    'win_tcp.c',
    'win_tcpconn.c',
    'win_tcpdial.c',
    'win_tcplisten.c',
    'win_thread.c',
    'win_udp.c'
  )

  nng_deps += [
    cc.find_library('ws2_32'),
    cc.find_library('mswsock'),
    cc.find_library('advapi32')
  ]
endif

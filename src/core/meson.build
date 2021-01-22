#
# Copyright 2021 Staysail Systems, Inc. <info@staysail.tech>
#
# This software is supplied under the terms of the MIT License, a
# copy of which should be located in the distribution where this
# file was obtained (LICENSE.txt).  A copy of the license may also be
# found online at https://opensource.org/licenses/MIT.
#

#  Core

if get_option('nng_stats')
  nng_lib_defs += 'NNG_ENABLE_STATS'
endif

nng_core_srcs += files(
  'aio.c',
  'clock.c',
  'device.c',
  'dialer.c',
  'file.c',
  'idhash.c',
  'init.c',
  'list.c',
  'listener.c',
  'lmq.c',
  'message.c',
  'msgqueue.c',
  'options.c',
  'pollable.c',
  'panic.c',
  'pipe.c',
  'protocol.c',
  'reap.c',
  'socket.c',
  'stats.c',
  'stream.c',
  'strs.c',
  'taskq.c',
  'tcp.c',
  'thread.c',
  'timer.c',
  'transport.c',
  'url.c'
)

nng_tests += {
  'source': meson.current_source_dir(),
  'suite': ['aio', 'buf_size', 'errors', 'id', 'list', 'reconnect', 'sock', 'url']
}

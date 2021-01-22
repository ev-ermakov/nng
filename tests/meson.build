#
# Copyright 2021 Staysail Systems, Inc. <info@staysail.tech>
#
# This software is supplied under the terms of the MIT License, a
# copy of which should be located in the distribution where this
# file was obtained (LICENSE.txt).  A copy of the license may also be
# found online at https://opensource.org/licenses/MIT.
#

#  Declare unit tests.

# Note that tests which depend on internal (not public) APIs are not
# enabled unless a static library is built.  This is because on some
# systems (e.g. Windows) we do not expose symbols that are not in the
# public API.

reqrep0 = 'req0' in nng_proto and 'rep0' in nng_proto
pushpull0 = 'push0' in nng_proto and 'pull0' in nng_proto

tests = {
  'additional_sources': files('convey.c'),
  'tests': [
    ['device', 5],
    ['files', 5],
    ['httpclient', 60, nng_supp_http],
    ['httpserver', 30, nng_supp_http],
    ['inproc', 5, 'inproc' in nng_transport],
    ['ipc', 5, reqrep0],
    ['ipcsupp', 10],
    ['ipcwinsec', 5, 'rep0' in nng_proto],
    ['message', 5],
    ['multistress', 60, reqrep0 and
       'bus0' in nng_proto and
       'pub0' in nng_proto and
       'push0' in nng_proto],
    ['nonblock', 60, reqrep0],
    ['options', 5],
    ['pipe', 5, pushpull0],
    ['pollfd', 5, pushpull0],
    ['scalability', 20, reqrep0],
    ['stats', 5, get_option('nng_stats')],
    ['synch', 5],
    ['tls', 60, reqrep0],
    ['tcpsupp', 10],
    ['tcp', 180, reqrep0],
    ['tcp6', 60, reqrep0],
    ['transport', 5],
    ['udp', 5, reqrep0],
    ['ws', 30, reqrep0],
    ['wss', 30, reqrep0],
    ['zt', 60, 'zerotier' in nng_transport],

    ['bus', 5, 'bus0' in nng_proto],
    ['reqctx', 5, reqrep0],
    ['reqstress', 60, reqrep0]
  ]
}

# compatibility tests
# We only support these if ALL the legacy protocols are supported.  This
# is because we don't want to make modifications to partially enable some
# of these tests.  Folks minimizing the library probably don't care too
# much about these anyway.

compat_tests = {
  'enable': get_option('nng_compat'),
  'additional_sources': files('compat_testutil.c'),
  'tests': [
    ['compat_block', 10],
    ['compat_bug777', 10],
    ['compat_bus', 10],
    ['compat_cmsg', 10],
    ['compat_msg', 10],
    ['compat_iovec', 10],
    ['compat_device', 10],
    ['compat_pair', 10],
    ['compat_pipeline', 10],
    ['compat_poll', 10],
    ['compat_reqrep', 10],
    ['compat_survey', 10],
    ['compat_reqttl', 10],
    ['compat_shutdown', 10],
    ['compat_surveyttl', 10],
  ]
}

# These are special tests for compat mode, not inherited from the
# legacy libnanomsg suite.
compat_special_tests = {
  'enable': get_option('nng_compat'),
  'additional_sources': files('convey.c'),
  'tests': [
    ['compat_options', 5]
  ]
}

nng_tests += {
  'source': meson.current_source_dir(),
  'suffix': false,
  'single_suite': false,
  'suites': [tests, compat_tests, compat_special_tests]
}

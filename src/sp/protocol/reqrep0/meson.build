#
# Copyright 2021 Staysail Systems, Inc. <info@staysail.tech>
#
# This software is supplied under the terms of the MIT License, a
# copy of which should be located in the distribution where this
# file was obtained (LICENSE.txt).  A copy of the license may also be
# found online at https://opensource.org/licenses/MIT.
#

#  Req/Rep protocol

if 'rep0' in nng_proto
  nng_proto_srcs += files('rep.c', 'xrep.c')
  nng_tests += {
    'source': meson.current_source_dir(),
    'suite': ['rep', 'xrep']
  }
endif

if 'req0' in nng_proto
  nng_proto_srcs += files('req.c', 'xreq.c')
  nng_tests += {
    'source': meson.current_source_dir(),
    'suite': ['req', 'xreq']
  }
endif

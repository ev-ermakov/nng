#
# Copyright 2021 Staysail Systems, Inc. <info@staysail.tech>
#
# This software is supplied under the terms of the MIT License, a
# copy of which should be located in the distribution where this
# file was obtained (LICENSE.txt).  A copy of the license may also be
# found online at https://opensource.org/licenses/MIT.
#

#  Pipeline protocol

if 'pull0' in nng_proto
  nng_proto_srcs += files('pull.c')
  nng_tests += {
    'source': meson.current_source_dir(),
    'suite': ['pull']
  }
endif

if 'push0' in nng_proto
  nng_proto_srcs += files('push.c')
  nng_tests += {
    'source': meson.current_source_dir(),
    'suite': ['push']
  }
endif

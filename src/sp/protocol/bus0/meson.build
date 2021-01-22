#
# Copyright 2021 Staysail Systems, Inc. <info@staysail.tech>
#
# This software is supplied under the terms of the MIT License, a
# copy of which should be located in the distribution where this
# file was obtained (LICENSE.txt).  A copy of the license may also be
# found online at https://opensource.org/licenses/MIT.
#

#  Bus protocol

if 'bus0' in nng_proto
  nng_proto_srcs += files('bus.c')
  nng_tests += {
    'source': meson.current_source_dir(),
    'suite': ['bug1247']
  }
endif

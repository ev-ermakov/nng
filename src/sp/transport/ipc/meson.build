#
# Copyright 2021 Staysail Systems, Inc. <info@staysail.tech>
#
# This software is supplied under the terms of the MIT License, a
# copy of which should be located in the distribution where this
# file was obtained (LICENSE.txt).  A copy of the license may also be
# found online at https://opensource.org/licenses/MIT.
#

#  ipc protocol

if 'ipc' in nng_transport
  nng_transport_srcs += files('ipc.c')
  nng_tests += {
    'source': meson.current_source_dir(),
    'suite': ['ipc']
  }
endif

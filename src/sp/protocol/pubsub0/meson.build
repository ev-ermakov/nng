#
# Copyright 2021 Staysail Systems, Inc. <info@staysail.tech>
#
# This software is supplied under the terms of the MIT License, a
# copy of which should be located in the distribution where this
# file was obtained (LICENSE.txt).  A copy of the license may also be
# found online at https://opensource.org/licenses/MIT.
#

#  Pub/Sub protocol

if 'pub0' in nng_proto
  nng_proto_srcs += files('pub.c')
  nng_tests += {
    'source': meson.current_source_dir(),
    'suite': ['pub']
  }
endif

if 'sub0' in nng_proto
  nng_proto_srcs += files('sub.c', 'xsub.c')
  nng_tests += {
    'source': meson.current_source_dir(),
    'suite': ['sub', 'xsub']
  }
endif

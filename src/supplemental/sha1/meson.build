#
# Copyright 2021 Staysail Systems, Inc. <info@staysail.tech>
#
# This software is supplied under the terms of the MIT License, a
# copy of which should be located in the distribution where this
# file was obtained (LICENSE.txt).  A copy of the license may also be
# found online at https://opensource.org/licenses/MIT.
#

if nng_supp_sha1
  nng_supp_srcs += files('sha1.c')
  nng_tests += {
    'source': meson.current_source_dir(),
    'suite': ['sha1']
  }
endif

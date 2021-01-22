#
# Copyright 2021 Staysail Systems, Inc. <info@staysail.tech>
#
# This software is supplied under the terms of the MIT License, a
# copy of which should be located in the distribution where this
# file was obtained (LICENSE.txt).  A copy of the license may also be
# found online at https://opensource.org/licenses/MIT.
#

nng_supp_srcs += files('tls_common.c')

if nng_supp_tls
  nng_lib_defs += [
    'NNG_SUPP_TLS',
    'NNG_TLS_ENGINE_INIT=nng_tls_engine_init_' + nng_tls_engine,
    'NNG_TLS_ENGINE_FINI=nng_tls_engine_fini_' + nng_tls_engine
  ]

  nng_tests += {
    'source': meson.current_source_dir(),
    'suite': ['tls']
  }

  subdir('mbedtls')
  subdir('wolfssl')
endif

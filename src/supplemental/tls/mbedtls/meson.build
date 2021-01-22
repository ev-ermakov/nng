#
# Copyright 2021 Staysail Systems, Inc. <info@staysail.tech>
#
# This software is supplied under the terms of the MIT License, a
# copy of which should be located in the distribution where this
# file was obtained (LICENSE.txt).  A copy of the license may also be
# found online at https://opensource.org/licenses/MIT.
#

if nng_tls_engine == 'mbed'
  warning('************************************************************')
  warning('Linking against Mbed TLS changes license terms (Apache 2.0).')
  warning('Consult a lawyer and the license files for details.         ')
  warning('************************************************************')

  nng_deps += [
    cc.find_library('mbedtls'),
    cc.find_library('mbedcrypto'),
    cc.find_library('mbedx509')
  ]

  nng_supp_srcs += files('tls.c')
endif

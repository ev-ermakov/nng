#
# Copyright 2021 Staysail Systems, Inc. <info@staysail.tech>
#
# This software is supplied under the terms of the MIT License, a
# copy of which should be located in the distribution where this
# file was obtained (LICENSE.txt).  A copy of the license may also be
# found online at https://opensource.org/licenses/MIT.
#

#  ZeroTier protocol

if 'zerotier' in nng_transport
  error('TODO')

  # NB: As we wind up linking libzerotiercore.a into the application,
  # this means that your application will *also* need to either be licensed
  # under the GPLv3, or you will need to have a commercial license from
  # ZeroTier permitting its use elsewhere.
  warning('************************************************************')
  warning('Linking against zerotiercore changes license terms.         ')
  warning('Consult a lawyer and the license files for details.         ')
  warning('************************************************************')

  nng_transport_srcs += files('zerotier.c')
endif

#
# Copyright 2021 Staysail Systems, Inc. <info@staysail.tech>
#
# This software is supplied under the terms of the MIT License, a
# copy of which should be located in the distribution where this
# file was obtained (LICENSE.txt).  A copy of the license may also be
# found online at https://opensource.org/licenses/MIT.
#

#  Surveyor/Respondent protocol

if 'surveyor0' in nng_proto
  nng_proto_srcs += files('survey.c', 'xsurvey.c')
  nng_tests += {
    'source': meson.current_source_dir(),
    'suite': ['survey', 'xsurvey']
  }
endif

if 'respondent0' in nng_proto
  nng_proto_srcs += files('respond.c', 'xrespond.c')
  nng_tests += {
    'source': meson.current_source_dir(),
    'suite': ['respond', 'xrespond']
  }
endif

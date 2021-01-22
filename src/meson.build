#
# Copyright 2021 Staysail Systems, Inc. <info@staysail.tech>
#
# This software is supplied under the terms of the MIT License, a
# copy of which should be located in the distribution where this
# file was obtained (LICENSE.txt).  A copy of the license may also be
# found online at https://opensource.org/licenses/MIT.
#

nng_deps = []

nng_core_srcs += files('nng.c', 'nng_legacy.c')

subdir('core')
subdir('platform')
subdir('compat/nanomsg')
subdir('sp/protocol')
subdir('sp/transport')
subdir('supplemental/base64')
subdir('supplemental/http')
subdir('supplemental/sha1')
subdir('supplemental/tls')
subdir('supplemental/util')
subdir('supplemental/websocket')
subdir('testing')

nng_lib_defs += 'NNG_TEST_LIB' # TODO

nng_lib_c_defs = ''
foreach symbol : nng_lib_defs
  nng_lib_c_defs += '#define ' + symbol + '\n'
endforeach

foreach item : nng_check_func
  name = item[0]
  header = item[1]
  definition = item[2]

  if cc.has_function(name, prefix: nng_lib_c_defs + '#include <@0@>'.format(header))
    nng_lib_defs += definition
  endif
endforeach

if get_option('nng_compat')
  nng_lib_defs += 'NNG_COMPAT'
endif

foreach proto : nng_proto
  nng_lib_defs += 'NNG_HAVE_' + proto.to_upper()
endforeach

foreach transport : nng_transport
  nng_lib_defs += 'NNG_TRANSPORT_' + transport.to_upper()
endforeach

nng_lib_c_args = []
foreach symbol : nng_lib_defs
  nng_lib_c_args += '-D' + symbol
endforeach

nng_lib = library('nng',
  sources: [
    nng_core_srcs,
    nng_proto_srcs,
    nng_transport_srcs,
    nng_platform_srcs,
    nng_supp_srcs,
    nng_testing_srcs
  ],
  include_directories: [nng_inc, nng_inc_priv],
  c_args: nng_lib_c_args,
  dependencies: nng_deps,
  version: meson.project_version(), # TODO
  install: true
)

nng_dep = declare_dependency(
  include_directories: nng_inc,
  compile_args: nng_lib_c_args,
  dependencies: nng_deps,
  link_with: nng_lib
)

# Install the header files.
install_subdir('../include/nng', install_dir: 'include')

subdir('tools/nngcat')
subdir('tools/perf')

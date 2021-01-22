#
# Copyright 2021 Staysail Systems, Inc. <info@staysail.tech>
#
# This software is supplied under the terms of the MIT License, a
# copy of which should be located in the distribution where this
# file was obtained (LICENSE.txt).  A copy of the license may also be
# found online at https://opensource.org/licenses/MIT.
#

project('nng', 'c',
  version: '1.4.0', # TODO: include/nng/nng.h
  license: 'MIT',
  meson_version: '>= 0.53.0',
  default_options: [
    'buildtype=debugoptimized',
    'b_ndebug=if-release',
    'c_std=c99',
    'warning_level=3'
  ]
)

cc = meson.get_compiler('c')

# User-defined options.

nng_proto = get_option('nng_proto')
nng_transport = get_option('nng_transport')
nng_tls_engine = get_option('nng_tls_engine')
nng_websocket = 'ws' in nng_transport or 'wss' in nng_transport

nng_supp_http = get_option('nng_http') or nng_websocket
nng_supp_base64 = nng_websocket
nng_supp_sha1 = nng_websocket
nng_supp_tls = get_option('nng_tls') and nng_tls_engine != 'none'
nng_supp_websocket = nng_websocket

nng_lib_defs = []
nng_platform_posix = false
nng_platform_windows = false
nng_platform_freertos = false

nng_core_srcs = []
nng_proto_srcs = []
nng_transport_srcs = []
nng_platform_srcs = []
nng_supp_srcs = []
nng_testing_srcs = []

nng_tests = []

nng_check_defs = []
nng_check_func = []
nng_check_lib = []
nng_check_sym = []

host_system = host_machine.system()

if host_system == 'linux'
  nng_lib_defs += [
    'NNG_PLATFORM_POSIX',
    'NNG_PLATFORM_LINUX',
    'NNG_USE_EVENTFD',
    'NNG_HAVE_ABSTRACT_SOCKETS'
  ]
  nng_platform_posix = true

  # TODO: Windows subsystem for Linux -- smells like Linux,
  # but it has some differences (SO_REUSEADDR for one).

elif host_system == 'android'
  nng_lib_defs += [
    'NNG_PLATFORM_POSIX',
    'NNG_PLATFORM_LINUX',
    'NNG_PLATFORM_ANDROID',
    'NNG_USE_EVENTFD',
  ]
  nng_platform_posix = true

elif host_system == 'darwin'
  nng_lib_defs += [
    'NNG_PLATFORM_POSIX',
    'NNG_PLATFORM_DARWIN',
    'NNG_USE_EVENTFD',
  ]
  nng_platform_posix = true

elif host_system == 'freebsd'
  nng_lib_defs += [
    'NNG_PLATFORM_POSIX',
    'NNG_PLATFORM_FREEBSD',
  ]
  nng_platform_posix = true

elif host_system == 'openbsd'
  nng_lib_defs += [
    'NNG_PLATFORM_POSIX',
    'NNG_PLATFORM_OPENBSD',
  ]
  nng_platform_posix = true

elif host_system == 'sunos'
  nng_lib_defs += [
    'NNG_PLATFORM_POSIX',
    'NNG_PLATFORM_SUNOS',
  ]
  nng_platform_posix = true

elif host_system == 'windows'
  nng_lib_defs += [
    'NNG_PLATFORM_WINDOWS',
    'NNG_PLATFORM_SUNOS',
    '_WIN32_WINNT=0x0600'
  ]
  nng_platform_windows = true

elif host_system == 'freertos'
  nng_lib_defs += [
    'NNG_PLATFORM_FREERTOS'
  ]
  nng_platform_freertos = true

else
  warning('This platform may not be supported:', host_system)
  # blithely hope for POSIX to work
  nng_lib_defs += 'NNG_PLATFORM_POSIX'
  nng_platform_posix = true

endif

nng_inc = [ include_directories('include') ]
nng_inc_priv = [ include_directories('src') ]

subdir('src')
subdir('tests')
subdir('docs/man')

if get_option('nng_demo')
  subdir('demo')
endif

# Build tests

if not get_option('nng_tests')
  nng_tests = []
endif

cwd_fragments = meson.current_source_dir().split('/')

foreach test : nng_tests
  index = 0
  scope = []

  foreach fragment : test['source'].split('/')
    if index >= cwd_fragments.length()
      scope += fragment
    endif
    index += 1
  endforeach

  prepared_tests = []

  if test.get('single_suite', true)
    additional_sources = test.get('additional_sources', [])
    foreach t : test['suite']
      prepared_tests += {
        'scope': scope,
        'label': t,
        'additional_sources': additional_sources
      }
    endforeach
  else
    foreach suite : test['suites']
      if suite.get('enable', true)
        additional_sources = suite.get('additional_sources', [])
        foreach t : suite['tests']
          enable = t.length() < 3 or t[2]
          if enable
            prepared_tests += {
              'scope': scope,
              'label': t[0],
              'additional_sources': additional_sources,
              'timeout': t[1]
            }
          endif
        endforeach
      endif
    endforeach
  endif

  suffix = test.get('suffix', true)

  foreach t : prepared_tests
    scope = t['scope']
    label = t['label'] + (suffix ? '_test' : '')

    full_label = scope + [label]
    path = '/'.join(full_label) + '.c'

    name = 'nng'
    exclude_first = true

    foreach fragment : full_label
      if not exclude_first
        name += '.' + fragment
      endif
      exclude_first = false
    endforeach

    test(name,
      executable(name,
        sources: [t['additional_sources'], path],
        include_directories: [nng_inc, 'src', 'src/testing', 'tests'],
        dependencies: nng_dep
      ),
      timeout: t.get('timeout', 30)
    )
  endforeach
endforeach

# Configuration summary

summary_info = {}

summary_info += {'Build demos': get_option('nng_demo')}
summary_info += {'Build extra tools': get_option('nng_tools')}
summary_info += {'Build tests': get_option('nng_tests')}
summary_info += {'Enable statistics': get_option('nng_stats')}
summary_info += {'Enable HTTP API': nng_supp_http}

summary_info += {'TLS support': nng_supp_tls}
if nng_supp_tls
  summary_info += {'TLS engine': nng_tls_engine}
endif

summary_info += {'WebSocket support': nng_supp_websocket}
summary_info += {'Protocols': nng_proto}
summary_info += {'Transport': nng_transport}

summary_info += {'Nanomsg compatibility': get_option('nng_compat')}
summary_info += {'Deprecated functionality': not get_option('nng_elide_deprecated')}

summary(summary_info, bool_yn: true)

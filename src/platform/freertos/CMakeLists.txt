#
# Copyright 2021 Staysail Systems, Inc. <info@staystail.tech>
#
# This software is supplied under the terms of the MIT License, a
# copy of which should be located in the distribution where this
# file was obtained (LICENSE.txt).  A copy of the license may also be
# found online at https://opensource.org/licenses/MIT.
#

#  FreeRTOS.

if (NNG_PLATFORM_FREERTOS)
    target_include_directories(nng PRIVATE ${NNG_FREERTOS_INCDIRS})
    target_compile_definitions(nng PRIVATE NNG_USE_POSIX_RESOLV_GAI)
    target_compile_definitions(nng PRIVATE NNG_PLATFORM_POSIX_DEBUG)
    target_compile_definitions(nng PRIVATE NNG_PLATFORM_POSIX_SOCKADDR)
    target_compile_definitions(nng PRIVATE NNG_RESOLV_CONCURRENCY=1)
    target_compile_definitions(nng PRIVATE NNG_HAVE_GETRANDOM)

    nng_sources(
            freertos_impl.h

            ../posix/posix_errno.c
            ../posix/posix_pipe.c
            ../posix/posix_pollq_poll.c
            ../posix/posix_rand_getrandom.c
            ../posix/posix_resolv_gai.c
            ../posix/posix_sockaddr.c
            ../posix/posix_tcpconn.c
            ../posix/posix_tcpdial.c
            ../posix/posix_tcplisten.c

            freertos_alloc.c
            freertos_atomic.c
            freertos_clock.c
            freertos_debug.c
            freertos_file.c
            freertos_thread.c
    )

endif ()

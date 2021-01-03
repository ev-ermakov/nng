#
# Copyright 2021 Staysail Systems, Inc. <info@staystail.tech>
#
# This software is supplied under the terms of the MIT License, a
# copy of which should be located in the distribution where this
# file was obtained (LICENSE.txt).  A copy of the license may also be
# found online at https://opensource.org/licenses/MIT.
#

if (NNG_PLATFORM_POSIX OR NNG_PLATFORM_FREERTOS)
    # GCC needs libatomic on some architectures (e.g. ARM) because the
    # underlying architecture may lack the necessary atomic primitives.
    # One hopes that the libatomic implementation is superior to just using
    # a pthread mutex.  The symbol chosen here was identified from GCC's
    # libatomic map file.
    #
    # Arguably when using clang, compiler-rt might be better.
    nng_check_lib(atomic __atomic_load_1 NNG_HAVE_LIBATOMIC)

    nng_check_sym(atomic_flag_test_and_set stdatomic.h NNG_HAVE_STDATOMIC)

    nng_sources(
            atomic.c
    )

endif ()

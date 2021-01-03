//
// Copyright 2021 Staysail Systems, Inc. <info@staysail.tech>
//
// This software is supplied under the terms of the MIT License, a
// copy of which should be located in the distribution where this
// file was obtained (LICENSE.txt).  A copy of the license may also be
// found online at https://opensource.org/licenses/MIT.
//

#include "core/nng_impl.h"

#ifdef NNG_PLATFORM_FREERTOS

#include <stdlib.h>
#include <stdio.h>

void
nni_plat_abort(void)
{
	abort();
}

void
nni_plat_printf(const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	(void) vprintf(fmt, ap);
	va_end(ap);
}

void
nni_plat_println(const char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
}

#endif // NNG_PLATFORM_FREERTOS

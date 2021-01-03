//
// Copyright 2021 Garrett D'Amore <garrett@damore.org>
//
// This software is supplied under the terms of the MIT License, a
// copy of which should be located in the distribution where this
// file was obtained (LICENSE.txt).  A copy of the license may also be
// found online at https://opensource.org/licenses/MIT.
//

#include "core/nng_impl.h"

#ifdef NNG_PLATFORM_FREERTOS

#include <string.h>
#include <FreeRTOS.h>

void *
nni_alloc(size_t sz)
{
	return (sz > 0 ? pvPortMalloc(sz) : NULL);
}

void *
nni_zalloc(size_t sz)
{
	void *ptr;

	if ((ptr = nni_alloc(sz)) != NULL) {
		memset(ptr, 0, sz);
	}

	return (ptr);
}

void
nni_free(void *ptr, size_t size)
{
	NNI_ARG_UNUSED(size);
	vPortFree(ptr);
}

#endif // NNG_PLATFORM_FREERTOS

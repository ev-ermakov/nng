//
// Copyright 2021 Staysail Systems, Inc. <info@staysail.tech>
// Copyright 2018 Capitar IT Group BV <info@capitar.com>
//
// This software is supplied under the terms of the MIT License, a
// copy of which should be located in the distribution where this
// file was obtained (LICENSE.txt).  A copy of the license may also be
// found online at https://opensource.org/licenses/MIT.
//

// FreeRTOS atomics.

#include "core/nng_impl.h"

#ifdef NNG_PLATFORM_FREERTOS

#ifndef NNG_HAVE_STDATOMIC

bool
nni_atomic_flag_test_and_set(nni_atomic_flag *f)
{
	bool v;
	nni_freertos_suspend_all();
	v    = f->f;
	f->f = true;
	nni_freertos_resume_all();
	return (v);
}

void
nni_atomic_flag_reset(nni_atomic_flag *f)
{
	nni_freertos_suspend_all();
	f->f = false;
	nni_freertos_resume_all();
}

void
nni_atomic_set_bool(nni_atomic_bool *b, bool n)
{
	nni_freertos_suspend_all();
	b->b = n;
	nni_freertos_resume_all();
}

bool
nni_atomic_get_bool(nni_atomic_bool *b)
{
	bool v;
	nni_freertos_suspend_all();
	v = b->b;
	nni_freertos_resume_all();
	return (v);
}

bool
nni_atomic_swap_bool(nni_atomic_bool *b, bool n)
{
	bool v;
	nni_freertos_suspend_all();
	v    = b->b;
	b->b = n;
	nni_freertos_resume_all();
	return (v);
}

void
nni_atomic_init_bool(nni_atomic_bool *b)
{
	b->b = false;
}

void
nni_atomic_add64(nni_atomic_u64 *v, uint64_t bump)
{
	nni_freertos_suspend_all();
	v->v += bump;
	nni_freertos_resume_all();
}

void
nni_atomic_sub64(nni_atomic_u64 *v, uint64_t bump)
{
	nni_freertos_suspend_all();
	v->v -= bump;
	nni_freertos_resume_all();
}

uint64_t
nni_atomic_get64(nni_atomic_u64 *v)
{
	uint64_t rv;
	nni_freertos_suspend_all();
	rv = v->v;
	nni_freertos_resume_all();
	return (rv);
}

void
nni_atomic_set64(nni_atomic_u64 *v, uint64_t u)
{
	nni_freertos_suspend_all();
	v->v = u;
	nni_freertos_resume_all();
}

uint64_t
nni_atomic_swap64(nni_atomic_u64 *v, uint64_t u)
{
	uint64_t rv;
	nni_freertos_suspend_all();
	rv   = v->v;
	v->v = u;
	nni_freertos_resume_all();
	return (rv);
}

void
nni_atomic_init64(nni_atomic_u64 *v)
{
	v->v = 0;
}

void
nni_atomic_inc64(nni_atomic_u64 *v)
{
	nni_freertos_suspend_all();
	v->v++;
	nni_freertos_resume_all();
}

uint64_t
nni_atomic_dec64_nv(nni_atomic_u64 *v)
{
	uint64_t nv;
	nni_freertos_suspend_all();
	v->v--;
	nv = v->v;
	nni_freertos_resume_all();
	return (nv);
}

bool
nni_atomic_cas64(nni_atomic_u64 *v, uint64_t comp, uint64_t new)
{
	bool result = false;
	nni_freertos_suspend_all();
	if (v->v == comp) {
		v->v   = new;
		result = true;
	}
	nni_freertos_resume_all();
	return (result);
}

void
nni_atomic_init(nni_atomic_int *v)
{
	nni_freertos_suspend_all();
	v->v = 0;
	nni_freertos_resume_all();
}

void
nni_atomic_add(nni_atomic_int *v, int bump)
{
	nni_freertos_suspend_all();
	v->v += bump;
	nni_freertos_resume_all();
}

void
nni_atomic_sub(nni_atomic_int *v, int bump)
{
	nni_freertos_suspend_all();
	v->v -= bump;
	nni_freertos_resume_all();
}

int
nni_atomic_get(nni_atomic_int *v)
{
	int rv;
	nni_freertos_suspend_all();
	rv = v->v;
	nni_freertos_resume_all();
	return (rv);
}

void
nni_atomic_set(nni_atomic_int *v, int i)
{
	nni_freertos_suspend_all();
	v->v = i;
	nni_freertos_resume_all();
}

int
nni_atomic_swap(nni_atomic_int *v, int i)
{
	int rv;
	nni_freertos_suspend_all();
	rv   = v->v;
	v->v = i;
	nni_freertos_resume_all();
	return (rv);
}

void
nni_atomic_inc(nni_atomic_int *v)
{
	nni_freertos_suspend_all();
	v->v++;
	nni_freertos_resume_all();
}

void
nni_atomic_dec(nni_atomic_int *v)
{
	nni_freertos_suspend_all();
	v->v--;
	nni_freertos_resume_all();
}

int
nni_atomic_dec_nv(nni_atomic_int *v)
{
	int nv;
	nni_freertos_suspend_all();
	v->v--;
	nv = v->v;
	nni_freertos_resume_all();
	return (nv);
}

bool
nni_atomic_cas(nni_atomic_int *v, int comp, int new)
{
	bool result = false;
	nni_freertos_suspend_all();
	if (v->v == comp) {
		v->v   = new;
		result = true;
	}
	nni_freertos_resume_all();
	return (result);
}

#endif // NNG_HAVE_STDATOMIC

#endif // NNG_PLATFORM_FREERTOS

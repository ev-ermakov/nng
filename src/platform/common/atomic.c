//
// Copyright 2021 Staysail Systems, Inc. <info@staysail.tech>
// Copyright 2018 Capitar IT Group BV <info@capitar.com>
//
// This software is supplied under the terms of the MIT License, a
// copy of which should be located in the distribution where this
// file was obtained (LICENSE.txt).  A copy of the license may also be
// found online at https://opensource.org/licenses/MIT.
//

// C11 atomics.

#include "core/nng_impl.h"

#if defined(NNG_PLATFORM_POSIX) || defined(NNG_PLATFORM_FREERTOS)

#ifdef NNG_HAVE_STDATOMIC

#include <stdatomic.h>

bool
nni_atomic_flag_test_and_set(nni_atomic_flag *f)
{
	return (atomic_flag_test_and_set(&f->f));
}

void
nni_atomic_flag_reset(nni_atomic_flag *f)
{
	atomic_flag_clear(&f->f);
}

void
nni_atomic_set_bool(nni_atomic_bool *v, bool b)
{
	atomic_store(&v->v, b);
}

bool
nni_atomic_get_bool(nni_atomic_bool *v)
{
	return (atomic_load(&v->v));
}

bool
nni_atomic_swap_bool(nni_atomic_bool *v, bool b)
{
	return (atomic_exchange(&v->v, b));
}

void
nni_atomic_init_bool(nni_atomic_bool *v)
{
	atomic_init(&v->v, false);
}

void
nni_atomic_init(nni_atomic_int *v)
{
	atomic_init(&v->v, 0);
}

void
nni_atomic_add(nni_atomic_int *v, int bump)
{
	(void) atomic_fetch_add_explicit(&v->v, bump, memory_order_relaxed);
}

void
nni_atomic_sub(nni_atomic_int *v, int bump)
{
	(void) atomic_fetch_sub_explicit(&v->v, bump, memory_order_relaxed);
}

int
nni_atomic_get(nni_atomic_int *v)
{
	return (atomic_load(&v->v));
}

void
nni_atomic_set(nni_atomic_int *v, int i)
{
	return (atomic_store(&v->v, i));
}

int
nni_atomic_swap(nni_atomic_int *v, int i)
{
	return (atomic_exchange(&v->v, i));
}

void
nni_atomic_inc(nni_atomic_int *v)
{
	atomic_fetch_add(&v->v, 1);
}

void
nni_atomic_dec(nni_atomic_int *v)
{
	atomic_fetch_sub(&v->v, 1);
}

int
nni_atomic_dec_nv(nni_atomic_int *v)
{
	return (atomic_fetch_sub(&v->v, 1) - 1);
}

bool
nni_atomic_cas(nni_atomic_int *v, int comp, int new)
{
	return (atomic_compare_exchange_strong(&v->v, &comp, new));
}

void
nni_atomic_add64(nni_atomic_u64 *v, uint64_t bump)
{
	(void) atomic_fetch_add_explicit(
	    &v->v, (uint_fast64_t) bump, memory_order_relaxed);
}

void
nni_atomic_sub64(nni_atomic_u64 *v, uint64_t bump)
{
	(void) atomic_fetch_sub_explicit(
	    &v->v, (uint_fast64_t) bump, memory_order_relaxed);
}

uint64_t
nni_atomic_get64(nni_atomic_u64 *v)
{
	return ((uint64_t) atomic_load(&v->v));
}

void
nni_atomic_set64(nni_atomic_u64 *v, uint64_t u)
{
	atomic_store(&v->v, (uint_fast64_t) u);
}

uint64_t
nni_atomic_swap64(nni_atomic_u64 *v, uint64_t u)
{
	return ((uint64_t) atomic_exchange(&v->v, (uint_fast64_t) u));
}

void
nni_atomic_init64(nni_atomic_u64 *v)
{
	atomic_init(&v->v, 0);
}

void
nni_atomic_inc64(nni_atomic_u64 *v)
{
	atomic_fetch_add(&v->v, 1);
}

uint64_t
nni_atomic_dec64_nv(nni_atomic_u64 *v)
{
	uint64_t ov;

	// C11 atomics give the old rather than new value.
	ov = (uint64_t) atomic_fetch_sub(&v->v, 1);
	return (ov - 1);
}

bool
nni_atomic_cas64(nni_atomic_u64 *v, uint64_t comp, uint64_t new)
{
	// It's possible that uint_fast64_t is not the same type underneath
	// as uint64_t.  (Would be unusual!)
	uint_fast64_t cv = (uint_fast64_t) comp;
	uint_fast64_t nv = (uint_fast64_t) new;
	return (atomic_compare_exchange_strong(&v->v, &cv, nv));
}

#endif

#endif

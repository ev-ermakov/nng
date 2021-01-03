//
// Copyright 2021 Staysail Systems, Inc. <info@staysail.tech>
//
// This software is supplied under the terms of the MIT License, a
// copy of which should be located in the distribution where this
// file was obtained (LICENSE.txt).  A copy of the license may also be
// found online at https://opensource.org/licenses/MIT.
//

#ifndef PLATFORM_FREERTOS_IMPL_H
#define PLATFORM_FREERTOS_IMPL_H

#include "core/list.h"

#include <FreeRTOS.h>
#include <semphr.h>

#include <stdbool.h>
#include <stdint.h>

#ifdef NNG_PLATFORM_POSIX_DEBUG
extern int nni_plat_errno(int);
#endif

#ifdef NNG_PLATFORM_POSIX_SOCKADDR
#include <sys/socket.h>
extern int    nni_posix_sockaddr2nn(nni_sockaddr *, const void *, size_t);
extern size_t nni_posix_nn2sockaddr(void *, const nni_sockaddr *);
#endif

typedef struct nni_freertos_bsem nni_freertos_bsem;

// These types are provided for here, to permit them to be directly inlined
// elsewhere.

struct nni_plat_mtx {
	SemaphoreHandle_t handle;
	StaticSemaphore_t buffer;
};

struct nni_freertos_bsem {
	SemaphoreHandle_t handle;
	StaticSemaphore_t buffer;
};

struct nni_plat_cv {
	nni_freertos_bsem sem;
	nni_list          queue;
	nni_plat_mtx     *mtx;
};

struct nni_plat_thr {
	nni_freertos_bsem sem;
	TaskHandle_t      handle;
	void (*func)(void *);
	void *arg;
};

struct nni_plat_flock {
	int fd;
};

#define NNG_PLATFORM_DIR_SEP "/"

#ifdef NNG_HAVE_STDATOMIC

#include <stdatomic.h>

struct nni_atomic_flag {
	atomic_flag f;
};

struct nni_atomic_int {
	atomic_int v;
};

struct nni_atomic_u64 {
	atomic_uint_fast64_t v;
};

struct nni_atomic_bool {
	atomic_bool v;
};

#else // NNG_HAVE_C11_ATOMIC
struct nni_atomic_flag {
	bool f;
};

struct nni_atomic_bool {
	bool b;
};

struct nni_atomic_int {
	int v;
};

struct nni_atomic_u64 {
	uint64_t v;
};

#endif

extern int  nni_posix_resolv_sysinit(void);
extern void nni_posix_resolv_sysfini(void);

extern int  nni_posix_pollq_sysinit(void);
extern void nni_posix_pollq_sysfini(void);

extern void nni_freertos_suspend_all(void);
extern void nni_freertos_resume_all(void);

#endif // PLATFORM_FREERTOS_IMPL_H

//
// Copyright 2021 Staysail Systems, Inc. <info@staysail.tech>
//
// This software is supplied under the terms of the MIT License, a
// copy of which should be located in the distribution where this
// file was obtained (LICENSE.txt).  A copy of the license may also be
// found online at https://opensource.org/licenses/MIT.
//

// FreeRTOS threads.

#include "core/nng_impl.h"
#include <stdio.h>

#ifdef NNG_PLATFORM_FREERTOS

typedef struct nni_freertos_cv_node {
	nni_freertos_bsem sem;
	nni_list_node     node;
} nni_freertos_cv_node;

extern void vTaskAdditionsSetName(TaskHandle_t handle, const char *name);

static int nni_plat_inited = 0;

void
nni_freertos_suspend_all(void)
{
	vTaskSuspendAll();
}

void
nni_freertos_resume_all(void)
{
	if (xTaskResumeAll() == pdFALSE) {
		taskYIELD();
	}
}

static void
nni_freertos_bsem_init(nni_freertos_bsem *bsem)
{
	bsem->handle = xSemaphoreCreateBinaryStatic(&bsem->buffer);
	NNI_ASSERT(bsem->handle != NULL);

	if (bsem->handle == NULL) {
		nni_plat_abort();
	}
}

static void
nni_freertos_bsem_fini(nni_freertos_bsem *bsem)
{
	vSemaphoreDelete(bsem->handle);
}

static void
nni_freertos_bsem_take(nni_freertos_bsem *bsem)
{
	if (xSemaphoreTake(bsem->handle, portMAX_DELAY) != pdTRUE) {
		nni_panic("xSemaphoreTake() failed");
	}
}

static bool
nni_freertos_bsem_take_timed(nni_freertos_bsem *bsem, unsigned timeout)
{
	return (xSemaphoreTake(bsem->handle, pdMS_TO_TICKS(timeout)) == pdTRUE);
}

static void
nni_freertos_bsem_give(nni_freertos_bsem *bsem)
{
	if (xSemaphoreGive(bsem->handle) != pdTRUE) {
		nni_panic("xSemaphoreGive() failed");
	}
}

void
nni_plat_mtx_init(nni_plat_mtx *mtx)
{
	mtx->handle = xSemaphoreCreateMutexStatic(&mtx->buffer);
	NNI_ASSERT(mtx->handle != NULL);

	if (mtx->handle == NULL) {
		nni_plat_abort();
	}
}

void
nni_plat_mtx_fini(nni_plat_mtx *mtx)
{
	vSemaphoreDelete(mtx->handle);
}

void
nni_plat_mtx_lock(nni_plat_mtx *mtx)
{
	if (xSemaphoreTake(mtx->handle, portMAX_DELAY) != pdTRUE) {
		nni_panic("xSemaphoreTake() failed");
	}
}

void
nni_plat_mtx_unlock(nni_plat_mtx *mtx)
{
	if (xSemaphoreGive(mtx->handle) != pdTRUE) {
		nni_panic("xSemaphoreGive() failed");
	}
}

void
nni_plat_cv_init(nni_plat_cv *cv, nni_plat_mtx *mtx)
{
	nni_freertos_bsem_init(&cv->sem);
	nni_freertos_bsem_give(&cv->sem);
	NNI_LIST_INIT(&cv->queue, nni_freertos_cv_node, node);
	cv->mtx = mtx;
}

void
nni_plat_cv_fini(nni_plat_cv *cv)
{
	nni_freertos_bsem_fini(&cv->sem);
}

void
nni_plat_cv_wake(nni_plat_cv *cv)
{
	nni_freertos_cv_node *waiter;

	nni_freertos_bsem_take(&cv->sem);
	nni_freertos_suspend_all();

	while ((waiter = nni_list_first(&cv->queue)) != NULL) {
		nni_list_remove(&cv->queue, waiter);
		nni_freertos_bsem_give(&waiter->sem);
	}

	nni_freertos_bsem_give(&cv->sem);
	nni_freertos_resume_all();
}

void
nni_plat_cv_wake1(nni_plat_cv *cv)
{
	nni_freertos_cv_node *waiter;

	nni_freertos_bsem_take(&cv->sem);
	nni_freertos_suspend_all();

	if ((waiter = nni_list_first(&cv->queue)) != NULL) {
		nni_list_remove(&cv->queue, waiter);
		nni_freertos_bsem_give(&waiter->sem);
	}

	nni_freertos_bsem_give(&cv->sem);
	nni_freertos_resume_all();
}

static void
nni_plat_cv_wait_begin(nni_plat_cv *cv, nni_freertos_cv_node *waiter)
{
	nni_freertos_bsem_init(&waiter->sem);
	NNI_LIST_NODE_INIT(&waiter->node);

	nni_freertos_bsem_take(&cv->sem);
	nni_list_append(&cv->queue, waiter);
	nni_freertos_bsem_give(&cv->sem);

	nni_plat_mtx_unlock(cv->mtx);
}

static void
nni_plat_cv_wait_end(nni_plat_cv *cv, nni_freertos_cv_node *waiter)
{
	nni_freertos_bsem_fini(&waiter->sem);
	nni_plat_mtx_lock(cv->mtx);
}

void
nni_plat_cv_wait(nni_plat_cv *cv)
{
	nni_freertos_cv_node waiter;

	nni_plat_cv_wait_begin(cv, &waiter);
	nni_freertos_bsem_take(&waiter.sem);
	nni_plat_cv_wait_end(cv, &waiter);
}

int
nni_plat_cv_until(nni_plat_cv *cv, nni_time until)
{
	int rv = 0;
	nni_freertos_cv_node waiter;

	nni_plat_cv_wait_begin(cv, &waiter);

	if (!nni_freertos_bsem_take_timed(&waiter.sem, until)) {
		nni_freertos_bsem_take(&cv->sem);
		if (nni_list_node_active(&waiter.node)) {
			nni_list_remove(&cv->queue, &waiter);
		}
		nni_freertos_bsem_give(&cv->sem);
		rv = NNG_ETIMEDOUT;
	}
	nni_plat_cv_wait_end(cv, &waiter);

	return (rv);
}

static void
nni_plat_thr_main(void *arg)
{
	nni_plat_thr *thr = arg;

	thr->func(thr->arg);
	nni_freertos_bsem_give(&thr->sem);

	for (;;) {
		vTaskDelay(portMAX_DELAY);
	}
}

#define NNG_STACK_SIZE configMINIMAL_STACK_SIZE

int
nni_plat_thr_init(nni_plat_thr *thr, void (*fn)(void *), void *arg)
{
	BaseType_t rv;
	char name[configMAX_TASK_NAME_LEN];

	thr->func = fn;
	thr->arg  = arg;

	nni_freertos_bsem_init(&thr->sem);

	rv = xTaskCreate(nni_plat_thr_main, NULL, NNG_STACK_SIZE, thr, 1, &thr->handle);
	if (rv != pdTRUE) {
		return (NNG_ENOMEM);
	}

	snprintf(name, sizeof(name), "nng:%p", thr->handle);
	vTaskAdditionsSetName(thr->handle, name);

	return (0);
}

void
nni_plat_thr_fini(nni_plat_thr *thr)
{
	nni_freertos_bsem_take(&thr->sem);
	nni_freertos_bsem_fini(&thr->sem);
	vTaskDelete(thr->handle);
}

bool
nni_plat_thr_is_self(nni_plat_thr *thr)
{
	return (xTaskGetCurrentTaskHandle() == thr->handle);
}

void
nni_plat_thr_set_name(nni_plat_thr *thr, const char *name)
{
	TaskHandle_t handle = NULL;

	if (thr == NULL) {
		handle = xTaskGetCurrentTaskHandle();
	} else {
		handle = thr->handle;
	}

	vTaskAdditionsSetName(handle, name);
}

int
nni_plat_init(int (*helper)(void))
{
	int rv = 0;

	if (nni_plat_inited) {
		return (0); // fast path
	}
	nni_freertos_suspend_all();

	if (nni_plat_inited) {
		nni_freertos_resume_all();
		return (0);
	}
	if ((rv = nni_posix_resolv_sysinit()) != 0) {
		return (rv);
	}
	if ((rv = nni_posix_pollq_sysinit()) != 0) {
		nni_posix_resolv_sysfini();
		return (rv);
	}
	if ((rv = helper()) != 0) {
		nni_posix_resolv_sysfini();
		nni_posix_pollq_sysinit();
	}

	nni_plat_inited = rv == 0;
	nni_freertos_resume_all();

	return (rv);
}

void
nni_plat_fini(void)
{
	nni_posix_resolv_sysfini();
	nni_posix_pollq_sysfini();
}

int
nni_plat_ncpu(void)
{
	return (1);
}

#endif // NNG_PLATFORM_FREERTOS

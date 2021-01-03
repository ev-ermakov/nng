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

static nni_plat_mtx mtx;
static nni_id_map   map;

int
nni_plat_pipe_open(int *wfd, int *rfd)
{
	uint32_t fds[2];
	QueueHandle_t queue;

	if ((queue = xQueueCreate(32, sizeof(uint8_t))) == NULL) {
		return (NNG_ENOMEM);
	}

	nni_plat_mtx_lock(&mtx);
	nni_id_alloc(&map, &fds[0], queue);
	nni_id_alloc(&map, &fds[1], queue);
	nni_plat_mtx_unlock(&mtx);

	*wfd = fds[0];
	*rfd = fds[1];

	return (0);
}

void
nni_plat_pipe_close(int wfd, int rfd)
{
	QueueHandle_t queue[2];

	nni_plat_mtx_lock(&mtx);
	queue[0] = nni_id_get(&map, wfd);
	queue[1] = nni_id_get(&map, rfd);
	nni_id_remove(&map, wfd);
	nni_id_remove(&map, rfd);
	nni_plat_mtx_unlock(&mtx);

	NNI_ASSERT(queue[0] == queue[1]);
	NNI_ASSERT(queue[0] != NULL);

	vQueueDelete(queue[0]);
}

void
nni_plat_pipe_raise(int wfd)
{
	QueueHandle_t queue;

	nni_plat_mtx_lock(&mtx);
	queue = nni_id_get(&map, wfd);
	nni_plat_mtx_unlock(&mtx);

	NNI_ASSERT(queue != NULL);

	xQueueSend(queue, &(uint8_t) { 1 }, 0);
}

void
nni_plat_pipe_clear(int rfd)
{
	QueueHandle_t queue;

	nni_plat_mtx_lock(&mtx);
	queue = nni_id_get(&map, rfd);
	nni_plat_mtx_unlock(&mtx);

	NNI_ASSERT(queue != NULL);

	for (;;) {
		// Completely drain the pipe, but don't wait.
		// This coalesces events somewhat.
		if (xQueueReceive(queue, &(uint8_t) { 0 }, 0) != pdTRUE) {
			return;
		}
	}
}

int
nni_freertos_pipe_sysinit(void)
{
	nni_plat_mtx_init(&mtx);
	nni_id_map_init(&map, 0, 0, false);
	return (0);
}

void nni_freertos_pipe_sysfini(void)
{
	nni_id_map_fini(&map);
	nni_plat_mtx_fini(&mtx);
}

#endif // NNG_PLATFORM_FREERTOS

//
// Copyright 2021 Staysail Systems, Inc. <info@staysail.tech>
//
// This software is supplied under the terms of the MIT License, a
// copy of which should be located in the distribution where this
// file was obtained (LICENSE.txt).  A copy of the license may also be
// found online at https://opensource.org/licenses/MIT.
//

// Running:
//   $ ./build.sh
//   $ ./demo
//
//   pong: received PING
//   ping: received PONG
//   pong: received PING
//   ping: received PONG
//   pong: received PING
//   ping: received PONG
//   pong: received PING
//   ping: received PONG
//   tasks:
//   nng:poll:poll  	6		2%
//   app:stats      	0		<1%
//   nng:0x55b93e75e	2		<1%
//   IDLE           	376		125%
//   nng:resolver   	0		<1%
//   nng:aio:expire 	0		<1%
//   nng:reap2      	0		<1%
//   app:startup    	0		<1%
//   nng:timer      	0		<1%
//   nng:task       	1		<1%
//   nng:task       	0		<1%
//   nng:0x55b93e75e	0		<1%
//

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <time.h>

#include <nng/nng.h>
#include <nng/protocol/reqrep0/rep.h>
#include <nng/protocol/reqrep0/req.h>
#include <nng/supplemental/util/platform.h>

#include <FreeRTOS.h>
#include <task.h>

void vApplicationStackOverflowHook(TaskHandle_t task, char *name)
{
	fprintf(stderr, "*** stack overflow: %p -- %s\n", task, name);
	abort();
}

void
vApplicationMallocFailedHook()
{
	fprintf(stderr, "*** malloc() failed\n");
	abort();
}

void
vApplicationGetIdleTaskMemory(StaticTask_t **p_tcb,
	StackType_t **p_stack, uint32_t *n_stack)
{
	static StaticTask_t tcb;
	static StackType_t stack[configMINIMAL_STACK_SIZE];

	*p_tcb = &tcb;
	*p_stack = stack;
	*n_stack = configMINIMAL_STACK_SIZE;
}

#if 0
void vApplicationGetTimerTaskMemory(StaticTask_t **ppxTimerTaskTCBBuffer,
    StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize)
{
	static StaticTask_t xTimerTaskTCB;
	static StackType_t uxTimerTaskStack[configTIMER_TASK_STACK_DEPTH];

	*ppxTimerTaskTCBBuffer = &xTimerTaskTCB;
	*ppxTimerTaskStackBuffer = uxTimerTaskStack;
	*pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
}
#endif

void log_msg(const char *format, ...)
{
	va_list argv;
	va_start(argv, format);

	portENTER_CRITICAL();
	vfprintf(stderr, format, argv);
	portEXIT_CRITICAL();

	va_end(argv);
}

static void task_stats(void *arg)
{
	char buf[1024];
	int *stop_stats = arg;

	log_msg("in task_stats()\n");
	nng_thread_set_name(NULL, "app:stats");

	while (*stop_stats == 0) {
		vTaskGetRunTimeStats(buf);
		log_msg("tasks:\n%s\n", buf);
		nng_msleep(1000);
	}
}

static void task_ping(void *arg)
{
	int rv = 0;
	nng_socket sock;

	log_msg("in task_ping()\n");
	nng_thread_set_name(NULL, "app:ping");

	rv = nng_req0_open(&sock);
	configASSERT(rv == 0);
	rv = nng_dial(sock, "inproc://server", NULL, 0);
	configASSERT(rv == 0);
	nng_setopt_ms(sock, NNG_OPT_SENDTIMEO, 1000);

	while (rv == 0) {
		char *buf = NULL;
		size_t sz = 0;

		rv = nng_send(sock, "PING", 4, 0);

		if (rv == 0) {
			rv = nng_recv(sock, &buf, &sz, NNG_FLAG_ALLOC);

			if (rv == 0) {
				log_msg("ping: received %.*s\n", (int) sz, buf);
				nng_free(buf, sz);
			}
		}
		nng_msleep(100);
	}
	log_msg("ping: last error: %s\n", nng_strerror(rv));
	nng_close(sock);
}

static void task_pong(void *arg)
{
	int rv = 0;
	nng_socket sock;
	int n = 10;

	log_msg("in task_pong()\n");
	nng_thread_set_name(NULL, "app:pong");

	rv = nng_rep0_open(&sock);
	configASSERT(rv == 0);
	rv = nng_listen(sock, "inproc://server", NULL, 0);
	configASSERT(rv == 0);

	while (n-- && rv == 0) {
		char *buf = NULL;
		size_t sz = 0;

		rv = nng_recv(sock, &buf, &sz, NNG_FLAG_ALLOC);

		if (sz == 4) {
			log_msg("pong: received %.*s\n", 4, buf);
			buf[1] = 'O';
			rv = nng_send(sock, buf, sz, NNG_FLAG_ALLOC);
			configASSERT(rv == 0);
			continue;
		}
		nng_free(buf, sz);
	}
	log_msg("pong: last error: %s\n", nng_strerror(rv));
	nng_close(sock);
}

static void task_startup(void *arg)
{
	int rv = 0;
	int stop_stats = 0;
	nng_thread *ping = NULL;
	nng_thread *pong = NULL;
	nng_thread *stats = NULL;

	log_msg("in task_startup\n");

	nng_thread_create(&stats, task_stats, &stop_stats);
	nng_thread_create(&pong, task_pong, NULL);
	nng_thread_create(&ping, task_ping, NULL);

	nng_thread_destroy(pong);
	nng_thread_destroy(ping);

	nng_msleep(1000);
	stop_stats = 1;
	nng_thread_destroy(stats);

	nng_fini();

	vTaskEndScheduler();
	configASSERT(0);
}

int main()
{
	int rv = 0;
	TaskHandle_t app;

	srand(time(NULL));

	rv = xTaskCreate(task_startup, "app:startup", configMINIMAL_STACK_SIZE, NULL, 1, &app);
	configASSERT(rv == pdTRUE);

	vTaskStartScheduler();
	vTaskDelete(app);

	return EXIT_SUCCESS;
}

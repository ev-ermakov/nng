//
// Copyright 2021 Staysail Systems, Inc. <info@staysail.tech>
//
// This software is supplied under the terms of the MIT License, a
// copy of which should be located in the distribution where this
// file was obtained (LICENSE.txt).  A copy of the license may also be
// found online at https://opensource.org/licenses/MIT.
//

#ifndef FREERTOSCONFIG_H
#define FREERTOSCONFIG_H

#ifndef NDEBUG
#include <assert.h>
#define configASSERT                              assert
#endif

#define configCHECK_FOR_STACK_OVERFLOW            1
#define configGENERATE_RUN_TIME_STATS             1
#define configIDLE_SHOULD_YIELD                   1
#define configINCLUDE_FREERTOS_TASK_C_ADDITIONS_H 1
#define configMAX_PRIORITIES                      4
#define configMAX_TASK_NAME_LEN                   16
#define configMINIMAL_STACK_SIZE                  128
#define configSUPPORT_STATIC_ALLOCATION           1
#define configTICK_RATE_HZ                        100
#define configTOTAL_HEAP_SIZE                    (64 * 1024)
#define configUSE_16_BIT_TICKS                    0
#define configUSE_IDLE_HOOK                       0
#define configUSE_MALLOC_FAILED_HOOK              1
#define configUSE_MUTEXES                         1
#define configUSE_PREEMPTION                      1
#define configUSE_STATS_FORMATTING_FUNCTIONS      1
#define configUSE_TICK_HOOK                       0
#define configUSE_TRACE_FACILITY                  1

#define INCLUDE_vTaskDelay                        1
#define INCLUDE_vTaskDelete                       1

#endif

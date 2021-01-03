//
// Copyright 2021 Garrett D'Amore <garrett@damore.org>
// Copyright 2017 Capitar IT Group BV <info@capitar.com>
//
// This software is supplied under the terms of the MIT License, a
// copy of which should be located in the distribution where this
// file was obtained (LICENSE.txt).  A copy of the license may also be
// found online at https://opensource.org/licenses/MIT.
//

// FreeRTOS clock stuff.
#include "core/nng_impl.h"

#ifdef NNG_PLATFORM_FREERTOS

#include <FreeRTOS.h>
#include <task.h>

// Use FreeRTOS realtime stuff
nni_time
nni_plat_clock(void)
{
	return xTaskGetTickCount() * portTICK_PERIOD_MS;
}

void
nni_plat_sleep(nni_duration ms)
{
	vTaskDelay(pdMS_TO_TICKS(ms));
}

#endif // NNG_PLATFORM_FREERTOS

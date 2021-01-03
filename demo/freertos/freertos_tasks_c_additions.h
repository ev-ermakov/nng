//
// Copyright 2021 Staysail Systems, Inc. <info@staysail.tech>
//
// This software is supplied under the terms of the MIT License, a
// copy of which should be located in the distribution where this
// file was obtained (LICENSE.txt).  A copy of the license may also be
// found online at https://opensource.org/licenses/MIT.
//

#ifndef FREERTOS_TASKS_C_ADDITIONS_H
#define FREERTOS_TASKS_C_ADDITIONS_H

void vTaskAdditionsSetName(TaskHandle_t handle, const char *name)
{
	TCB_t *tcb = prvGetTCBFromHandle(handle);

	if (name == NULL) {
		tcb->pcTaskName[0] = 0x00;
	} else {
		for (UBaseType_t i = 0; i < (UBaseType_t) configMAX_TASK_NAME_LEN; i++) {
			tcb->pcTaskName[i] = name[i];
			if (name[i] == 0x00) {
				break;
			}
		}
		tcb->pcTaskName[configMAX_TASK_NAME_LEN - 1] = '\0';
	}
}

#endif /* FREERTOS_TASKS_C_ADDITIONS_H */

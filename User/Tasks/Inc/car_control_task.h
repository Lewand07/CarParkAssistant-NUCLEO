#ifndef CAR_CONTROL_TASK_H
#define CAR_CONTROL_TASK_H

#include "car_setup.h"
#include "cmsis_os.h"

extern osMessageQueueId_t CarInstructionQueueHandle;

/**
 * @brief Car Control Task.
 */
void CarControlTask(void);

#endif  // CAR_CONTROL_TASK_H

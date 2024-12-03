#ifndef PARK_ASSIST_TASK_H
#define PARK_ASSIST_TASK_H

#include "car_interface.h"
#include "cmsis_os.h"
#include "sensors_setup.h"
#include "sensors_task.h"

// Global mutex for synchronizing access to shared sensors data
extern osMutexId_t SensorsDataMutexHandle;

/**
 * @brief Park Assist Task
 */
void ParkAssistTask(void);

#endif  // PARK_ASSIST_TASK_H

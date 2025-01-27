#ifndef PARK_ASSIST_TASK_H
#define PARK_ASSIST_TASK_H

#include "car_interface.h"
#include "cmsis_os.h"
#include "sensors_setup.h"
#include "sensors_task.h"

/* Constants */
#define MIN_OBSTACLE_DISTANCE_MM 300U  // Minimum distance to detect an obstacle

// Global variables
extern osMutexId_t SensorsDataMutexHandle;
extern osMessageQueueId_t CarInstructionQueueHandle;
extern Sensor_Data sensors_data[SENSORS_NUMBER];

/**
 * @brief Park Assist Task
 */
void ParkAssistTask(void);

#endif  // PARK_ASSIST_TASK_H

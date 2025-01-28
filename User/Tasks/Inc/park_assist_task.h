#ifndef PARK_ASSIST_TASK_H
#define PARK_ASSIST_TASK_H

#include "car_interface.h"
#include "cmsis_os.h"
#include "sensors_setup.h"
#include "sensors_task.h"

/* Constants */
#define MIN_OBSTACLE_DISTANCE_MM  300  // Minimum distance to detect an obstacle
#define MIN_PARKING_SPOT_DEPTH_MM 200  // Minimum depth of a parking spot
#define MIN_CONSECUTIVE_COLUMNS   24U  // Minimum number of consecutive columns to detect spot

// Global variables
extern osMutexId_t SensorsDataMutexHandle;
extern osMessageQueueId_t CarInstructionQueueHandle;
extern Sensor_Data sensors_data[SENSORS_NUMBER];

/**
 * @brief Park Assist Task
 */
void ParkAssistTask(void);

#endif  // PARK_ASSIST_TASK_H

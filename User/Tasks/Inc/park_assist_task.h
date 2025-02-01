#ifndef PARK_ASSIST_TASK_H
#define PARK_ASSIST_TASK_H

#include "car_interface.h"
#include "cmsis_os.h"
#include "sensors_setup.h"
#include "sensors_task.h"

/* Constants */
#define MIN_OBSTACLE_DISTANCE_MM  300  // Minimum distance to detect an obstacle
#define MIN_PARKING_SPOT_DEPTH_MM 200  // Minimum depth of a parking spot
#define MIN_CONSECUTIVE_COLUMNS   40U  // Minimum number of consecutive columns to detect spot
#define BASE_DISTANCE_MM          100  // Base distance for delay calculations

// Global variables
extern osMutexId_t SensorsDataMutexHandle;
extern osMessageQueueId_t CarInstructionQueueHandle;
extern Sensor_Data sensors_data[SENSORS_NUMBER];

/* Parking States */
typedef enum {
    PARKING_IDLE,
    PARKING_ALIGN_FRONT,
    PARKING_REVERSE_STEER,
    PARKING_REVERSE_CENTER,
    PARKING_ADJUST,
    PARKING_COMPLETE
} ParkingState;

/**
 * @brief Park Assist Task
 */
void ParkAssistTask(void);

#endif  // PARK_ASSIST_TASK_H

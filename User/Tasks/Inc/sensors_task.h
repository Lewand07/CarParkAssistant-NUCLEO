#ifndef SENSORS_TASK_H
#define SENSORS_TASK_H

#include "cmsis_os.h"
#include "sensors_setup.h"

#define SENSOR_SCAN_FREQ_HZ  10U
#define SENSOR_SCAN_DELAY_MS (1000U) / SENSOR_SCAN_FREQ_HZ

// Global mutex for synchronizing access to shared sensors data
extern osMutexId_t SensorsDataMutexHandle;

/**
 * @brief Sensors Task.
 */
void SensorsTask(void);

#endif  // SENSORS_TASK_H

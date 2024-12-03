#ifndef SENSORS_TASK_H
#define SENSORS_TASK_H

#include "cmsis_os.h"
#include "sensors_setup.h"

#define SENSOR_SCAN_FREQ_HZ  10U
#define SENSOR_SCAN_DELAY_MS (1000U) / SENSOR_SCAN_FREQ_HZ

/**
 * @brief Sensors Task.
 */
void SensorsTask(void);

#endif  // SENSORS_TASK_H

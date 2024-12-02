#ifndef SENSORS_SETUP_H
#define SENSORS_SETUP_H

#include "gpio.h"
#include "i2c.h"
#include "sensor_interface.h"

/* Number of sensors */
#define SENSORS_NUMBER 2
/* Macros for accessing given sensor */
#define FRONT_SENSOR_IDX 0
#define REAR_SENSOR_IDX  1

/* Sensors I2C addresses */
#define SENSOR_DEFAULT_ADDR 0x52
#define FRONT_SENSOR_ADDR   0x69
#define REAR_SENSOR_ADDR    SENSOR_DEFAULT_ADDR

/* Global Access to Sensors and Sensors Data */
extern Sensor_Interface sensors[SENSORS_NUMBER];
extern Sensor_Data sensors_data[SENSORS_NUMBER];

/**
 * @brief Initialize all sensors.
 * @return Status of the setup.
 */
Sensor_Status Sensors_Setup(void);

#endif  // SENSORS_SETUP_H

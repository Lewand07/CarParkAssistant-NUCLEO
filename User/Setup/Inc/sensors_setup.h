#ifndef SENSORS_SETUP_H
#define SENSORS_SETUP_H

#include "gpio.h"
#include "sensor_interface.h"
#include "stm32f7xx_nucleo_bus.h"

/* Number of sensors */
#define SENSORS_NUMBER_L3 4U
#define SENSORS_NUMBER_L5 4U
#define SENSORS_NUMBER    (SENSORS_NUMBER_L3 + SENSORS_NUMBER_L5)

/* Sensors I2C addresses */
#define SENSOR_DEFAULT_ADDR 0x52  // 0x29 in 7-bit format
#define SENSOR_ADDR_OFFSET  0x04  // 4-bit offset between sensors
#define SENSOR_MAX_ADDR     0xFE  // max address for a 7-bit I2C address
#define CALC_SENSOR_ADDR(i) (SENSOR_MAX_ADDR - ((i)*SENSOR_ADDR_OFFSET))

/* Enum for sensor indexes */
enum Sensor_Index {
    SENSOR_L3_FRONT = 0U,
    SENSOR_L5_FRONT,
    SENSOR_L3_RIGHT,
    SENSOR_L5_RIGHT,
    SENSOR_L3_REAR,
    SENSOR_L5_REAR,
    SENSOR_L3_LEFT,
    SENSOR_L5_LEFT
};

/* Global Access to Sensors and Sensors Data */
extern Sensor_Interface sensors[SENSORS_NUMBER];
extern Sensor_Data sensors_data[SENSORS_NUMBER];

/**
 * @brief Initialize all sensors.
 * @return Status of the setup.
 */
Sensor_Status Sensors_Setup(void);

#endif  // SENSORS_SETUP_H

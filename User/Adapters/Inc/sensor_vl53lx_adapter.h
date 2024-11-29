#ifndef SERVO_VL53LX_ADAPTER_H
#define SERVO_VL53LX_ADAPTER_H

#include "vl53lx_api.h"
#include "sensor_interface.h"


/**
 * @brief Initialize the sensor interface.
 * @param sensor_instance Pointer to the sensor instance structure.
 * @return Status of the operation.
 */
Sensor_Status Sensor_Adapter_VL53LX_Init(void* sensor_instance);

/**
 * @brief Set the angle of the sensor.
 * @param sensor_instance Pointer to the sensor instance structure.
 * @param data Sensor_Data structure to acquire data from the sensor.
 * @return Status of the operation.
 */
Sensor_Status Sensor_Adapter_VL53LX_ReadData(void* sensor_instance, Sensor_Data* data);

/**
 * @brief Create the sensor interface.
 * @param sensor_device Pointer to the VL53LX sensor structure.
 * @return Sensor interface.
 */
Sensor_Interface Sensor_VL53LX_Create(VL53LX_DEV sensor_device);

#endif // SERVO_VL53LX_ADAPTER_H

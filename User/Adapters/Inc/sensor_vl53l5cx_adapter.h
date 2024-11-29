#ifndef SERVO_VL53L5CX_ADAPTER_H
#define SERVO_VL53L5CX_ADAPTER_H

#include "vl53l5cx_api.h"
#include "sensor_interface.h"

/**
 * @brief Initialize the sensor interface.
 * @param sensor_instance Pointer to the sensor instance structure.
 * @return Status of the operation.
 */
Sensor_Status Sensor_Adapter_VL53L5CX_Init(void* sensor_instance);

/**
 * @brief Set the angle of the sensor.
 * @param sensor_instance Pointer to the sensor instance structure.
 * @param data Sensor_Data structure to acquire data from the sensor.
 * @return Status of the operation.
 */
Sensor_Status Sensor_Adapter_VL53L5CX_ReadData(void* sensor_instance, Sensor_Data* data);

/**
 * @brief Create the sensor interface.
 * @param sensor_device Pointer to the VL53L5CX sensor structure.
 * @return Sensor interface.
 */
Sensor_Interface Sensor_VL53L5CX_Create(VL53L5CX_Configuration* sensor_device);

#endif // SERVO_VL53L5CX_ADAPTER_H

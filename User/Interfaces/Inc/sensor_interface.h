#ifndef SENSOR_INTERFACE_H
#define SENSOR_INTERFACE_H

#include <stddef.h>
#include <stdint.h>

#define MAX_SENSOR_ROWS     8
#define MAX_SENSOR_COLS     8
#define SENSOR_INVALID_DATA -1

typedef enum {
    SENSOR_OK = 0,
    SENSOR_ERROR
} Sensor_Status;

typedef struct {
    int32_t distances[MAX_SENSOR_ROWS][MAX_SENSOR_COLS];
    uint8_t rows;
    uint8_t cols;
} Sensor_Data;

typedef struct {
    void* sensor_instance;

    /* Function pointers for sensor operations */
    Sensor_Status (*initialize)(void* sensor_instance);
    Sensor_Status (*read_data)(void* sensor_instance, Sensor_Data* data);
} Sensor_Interface;

/**
 * @brief Initialize the sensor interface.
 * @param sensor Pointer to the sensor interface structure.
 * @return Status of the operation.
 */
Sensor_Status Sensor_Init(Sensor_Interface* sensor);

/**
 * @brief Set the angle of the sensor.
 * @param sensor Pointer to the sensor interface structure.
 * @param data Sensor_Data structure to acquire data from the sensor.
 * @return Status of the operation.
 */
Sensor_Status Sensor_ReadData(Sensor_Interface* sensor, Sensor_Data* data);

#endif  // SENSOR_INTERFACE_H

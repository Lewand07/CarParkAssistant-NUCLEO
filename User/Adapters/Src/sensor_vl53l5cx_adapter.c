#include "sensor_vl53l5cx_adapter.h"

/* Adapter Initialization Function */
Sensor_Status Sensor_Adapter_VL53L5CX_Init(void* sensor_instance) {
    VL53L5CX_Configuration* dev = (VL53L5CX_Configuration*)sensor_instance;

    if ((NULL == dev) || (0U != vl53l5cx_is_alive(dev, NULL)) || (0U != vl53l5cx_init(dev))) {
        return SENSOR_ERROR;
    }

    /* Configure default settings */
    if ((0U != vl53l5cx_set_resolution(dev, VL53L5CX_RESOLUTION_8X8)) ||
        (0U != vl53l5cx_set_ranging_mode(dev, VL53L5CX_RANGING_MODE_CONTINUOUS)) ||
        (0U != vl53l5cx_set_ranging_frequency_hz(dev, 10U))) {
        return SENSOR_ERROR;
    }

    if (0U != vl53l5cx_start_ranging(dev)) {
        return SENSOR_ERROR;
    }

    return SENSOR_OK;
}

Sensor_Status Sensor_Adapter_VL53L5CX_ReadData(void* sensor_instance, Sensor_Data* data) {
    VL53L5CX_Configuration* dev = (VL53L5CX_Configuration*)sensor_instance;
    VL53L5CX_ResultsData results;
    uint8_t data_ready = 0U;
    uint8_t i, j;

    if ((NULL == dev) || (NULL == data)) {
        return SENSOR_ERROR;
    }

    memset(data->distances, 0, sizeof(data->distances));
    data->rows = MAX_SENSOR_ROWS;
    data->cols = MAX_SENSOR_COLS;

    /* Poll for data readiness */
    if (vl53l5cx_check_data_ready(dev, &data_ready) != 0U || data_ready == 0U) {
        return SENSOR_ERROR;
    }

    /* Retrieve ranging data */
    if (vl53l5cx_get_ranging_data(dev, &results) != 0U) {
        return SENSOR_ERROR;
    }

    for (i = 0U; i < data->rows; i++) {
        for (j = 0U; j < data->cols; j++) {
            uint16_t distance_index = (i * data->cols) + j;
            data->distances[i][j] = results.distance_mm[distance_index];
        }
    }

    return SENSOR_OK;
}

Sensor_Interface Sensor_VL53L5CX_Create(VL53L5CX_Configuration* sensor_device) {
    Sensor_Interface sensor = {NULL, NULL, NULL};

    if (NULL != sensor_device) {
        sensor.sensor_instance = sensor_device;
        sensor.initialize = Sensor_Adapter_VL53L5CX_Init;
        sensor.read_data = Sensor_Adapter_VL53L5CX_ReadData;
    }

    return sensor;
}

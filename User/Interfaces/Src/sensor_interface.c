#include "sensor_interface.h"

Sensor_Status Sensor_Init(Sensor_Interface* sensor) {
    if ((NULL == sensor) || (NULL == sensor->initialize)) {
        return SENSOR_ERROR;
    }

    return sensor->initialize(sensor->sensor_instance);
}

Sensor_Status Sensor_ReadData(Sensor_Interface* sensor, Sensor_Data* data) {
    if ((NULL == sensor) || (NULL == sensor->read_data)) {
        return SENSOR_ERROR;
    }

    return sensor->read_data(sensor->sensor_instance, data);
}

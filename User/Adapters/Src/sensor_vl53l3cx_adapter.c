#include "sensor_vl53l3cx_adapter.h"

Sensor_Status Sensor_Adapter_VL53L3CX_Init(void* sensor_instance) {
    VL53L3CX_Object_t* dev = (VL53L3CX_Object_t*)sensor_instance;

    if ((NULL == dev) || (VL53L3CX_Init(dev) != VL53L3CX_OK)) {
        return SENSOR_ERROR;
    }

    /* Configure default settings */
    VL53L3CX_ProfileConfig_t profile;
    profile.RangingProfile = VL53L3CX_PROFILE_MEDIUM;
    profile.TimingBudget = 30U; /* 16 ms < TimingBudget < 500 ms */
    profile.Frequency = 10U; /* Induces intermeasurement period, set to ZERO for normal ranging */
    profile.EnableAmbient = 0U; /* Enable: 1, Disable: 0 */
    profile.EnableSignal = 0U;  /* Enable: 1, Disable: 0 */

    if (VL53L3CX_ConfigProfile(dev, &profile) != VL53L3CX_OK) {
        return SENSOR_ERROR;
    }

    if (VL53L3CX_Start(dev, VL53L3CX_MODE_ASYNC_CONTINUOUS) != VL53L3CX_OK) {
        return SENSOR_ERROR;
    }

    return SENSOR_OK;
}

Sensor_Status Sensor_Adapter_VL53L3CX_ReadData(void* sensor_instance, Sensor_Data* data) {
    VL53L3CX_Object_t* dev = (VL53L3CX_Object_t*)sensor_instance;
    VL53L3CX_Result_t results;
    int32_t status = 0;

    if ((NULL == dev) || (NULL == data)) {
        return SENSOR_ERROR;
    }

    /* Clear the distances array */
    memset(data->distances, 0, sizeof(data->distances));
    data->rows = 1; /* VL53L3CX uses a single column for detected objects */
    data->cols = 0; /* Will be set dynamically */

    /* Poll for data readiness */
    status = VL53L3CX_GetDistance(dev, &results);
    if (status != VL53L3CX_OK) {
        return SENSOR_ERROR;
    }

    for (uint8_t i = 0; i < results.NumberOfZones; i++) {
        for (uint8_t j = 0; j < results.ZoneResult[i].NumberOfTargets; j++) {
            data->distances[i][j] = results.ZoneResult[i].Distance[j];
        }
        data->cols = results.ZoneResult[i].NumberOfTargets;
    }

    return SENSOR_OK;
}

Sensor_Interface Sensor_VL53L3CX_Create(VL53L3CX_Object_t* sensor_device) {
    Sensor_Interface sensor = {NULL, NULL, NULL};

    if (NULL != sensor_device) {
        sensor.sensor_instance = sensor_device;
        sensor.initialize = Sensor_Adapter_VL53L3CX_Init;
        sensor.read_data = Sensor_Adapter_VL53L3CX_ReadData;
    }

    return sensor;
}

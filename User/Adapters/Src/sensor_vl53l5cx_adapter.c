#include "sensor_vl53l5cx_adapter.h"

Sensor_Status Sensor_Adapter_VL53L5CX_Init(void* sensor_instance) {
    VL53L5CX_Object_t* dev = (VL53L5CX_Object_t*)sensor_instance;

    if ((NULL == dev) || (VL53L5CX_Init(dev) != VL53L5CX_OK)) {
        return SENSOR_ERROR;
    }

    /* Configure default settings */
    VL53L5CX_ProfileConfig_t profile;
    profile.RangingProfile = VL53L5CX_PROFILE_8x8_CONTINUOUS;
    profile.TimingBudget = 30U; /* 16 ms < TimingBudget < 500 ms */
    profile.Frequency = 10U; /* Induces intermeasurement period, set to ZERO for normal ranging */
    profile.EnableAmbient = 1U; /* Enable: 1, Disable: 0 */
    profile.EnableSignal = 1U;  /* Enable: 1, Disable: 0 */

    if (VL53L5CX_ConfigProfile(dev, &profile) != VL53L5CX_OK) {
        return SENSOR_ERROR;
    }

    if (VL53L5CX_Start(dev, VL53L5CX_MODE_ASYNC_CONTINUOUS) != VL53L5CX_OK) {
        return SENSOR_ERROR;
    }

    return SENSOR_OK;
}

Sensor_Status Sensor_Adapter_VL53L5CX_ReadData(void* sensor_instance, Sensor_Data* data) {
    VL53L5CX_Object_t* dev = (VL53L5CX_Object_t*)sensor_instance;
    VL53L5CX_Result_t results;
    int32_t status = 0;
    uint8_t i, j, k, l;
    uint8_t zones_per_line = 8;

    if ((NULL == dev) || (NULL == data)) {
        return SENSOR_ERROR;
    }

    /* Clear the distances array */
    memset(data->distances, -1, sizeof(data->distances));
    data->rows = 8; /* VL53L5CX uses an 8x8 matrix for detected objects */
    data->cols = 8;

    /* Poll for data readiness */
    status = VL53L5CX_GetDistance(dev, &results);
    if (status != VL53L5CX_OK) {
        return SENSOR_ERROR;
    }

    for (j = 0; j < results.NumberOfZones; j += zones_per_line) {
        for (l = 0; l < VL53L5CX_NB_TARGET_PER_ZONE; l++) {
            for (k = 0; k < zones_per_line; k++) {
                i = j / zones_per_line;
                if (results.ZoneResult[j + k].NumberOfTargets > 0) {
                    data->distances[i][k] = results.ZoneResult[j + k].Distance[l];
                } else {
                    data->distances[i][k] = SENSOR_INVALID_DATA;
                }
            }
        }
    }

    return SENSOR_OK;
}

Sensor_Interface Sensor_VL53L5CX_Create(VL53L5CX_Object_t* sensor_device) {
    Sensor_Interface sensor = {NULL, NULL, NULL};

    if (NULL != sensor_device) {
        sensor.sensor_instance = sensor_device;
        sensor.initialize = Sensor_Adapter_VL53L5CX_Init;
        sensor.read_data = Sensor_Adapter_VL53L5CX_ReadData;
    }

    return sensor;
}

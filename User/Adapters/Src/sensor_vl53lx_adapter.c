#include "sensor_vl53lx_adapter.h"

Sensor_Status Sensor_Adapter_VL53LX_Init(void* sensor_instance) {
    VL53LX_DEV dev = (VL53LX_DEV)sensor_instance;

    if ((NULL == dev) || (VL53LX_WaitDeviceBooted(dev)) || (VL53LX_DataInit(dev)) ||
        (VL53LX_StartMeasurement(dev))) {
        return SENSOR_ERROR;
    }

    return SENSOR_OK;
}

Sensor_Status Sensor_Adapter_VL53LX_ReadData(void* sensor_instance, Sensor_Data* data) {
    VL53LX_DEV Dev = (VL53LX_DEV)sensor_instance;
    VL53LX_MultiRangingData_t multi_ranging_data;
    uint8_t NewDataReady = 0;
    int status = 0;

    if ((Dev == NULL) || (data == NULL)) {
        return SENSOR_ERROR;
    }

    /* Clear the distances array */
    memset(data->distances, 0, sizeof(data->distances));
    data->rows = 1; /* VL53LX uses a single column for detected objects */
    data->cols = 0; /* Will be set dynamically */

    do { /* Polling Mode */
        status = VL53LX_GetMeasurementDataReady(Dev, &NewDataReady);
        HAL_Delay(2); /* Polling period */
        if ((!status) && (0 != NewDataReady)) {
            status = VL53LX_GetMultiRangingData(Dev, &multi_ranging_data);

            if (0 == status) {
                /* Process the detected objects */
                uint8_t object_count = multi_ranging_data.NumberOfObjectsFound;
                data->cols = object_count;

                for (uint8_t j = 0; j < object_count; j++) {
                    uint16_t range_mm = multi_ranging_data.RangeData[j].RangeMilliMeter;
                    if (MAX_SENSOR_COLS > j) {
                        data->distances[0][j] = range_mm; /* Populate row 0 */
                    }
                }

                /* Clear interrupts and start a new measurement */
                status = VL53LX_ClearInterruptAndStartMeasurement(Dev);
                break; /* Exit polling after valid data */
            }
        }
    } while (1);

    return (status == 0) ? SENSOR_OK : SENSOR_ERROR;
}

Sensor_Interface Sensor_VL53LX_Create(VL53LX_DEV sensor_device) {
    Sensor_Interface sensor = {NULL, NULL, NULL};

    if (NULL != sensor_device) {
        sensor.sensor_instance = sensor_device;
        sensor.initialize = Sensor_Adapter_VL53LX_Init;
        sensor.read_data = Sensor_Adapter_VL53LX_ReadData;
    }

    return sensor;
}

#include "sensors_setup.h"

#include "sensor_vl53l5cx_adapter.h"
#include "sensor_vl53lx_adapter.h"

Sensor_Interface sensors[SENSORS_NUMBER];
Sensor_Data sensors_data[SENSORS_NUMBER];

/* Static Sensors Devices */
static VL53LX_Dev_t dev_sensorl3_front = {.I2cHandle = &hi2c1, .I2cDevAddr = SENSOR_DEFAULT_ADDR};

static VL53LX_DEV Dev_sensorl3_front = &dev_sensorl3_front;

static VL53L5CX_Configuration dev_sensorl5_rear = {.platform.address = SENSOR_DEFAULT_ADDR};

Sensor_Status Sensors_Setup(void) {
    uint8_t i;
    // setup front sensor
    VL53LX_SetDeviceAddress(Dev_sensorl3_front, FRONT_SENSOR_ADDR);
    Dev_sensorl3_front->I2cDevAddr = FRONT_SENSOR_ADDR;
    // setup rear sensor
    dev_sensorl5_rear.platform.address = REAR_SENSOR_ADDR;
    HAL_GPIO_WritePin(VL53L5CX_LPn_GPIO_Port, VL53L5CX_LPn_Pin, GPIO_PIN_SET);

    sensors[FRONT_SENSOR_IDX] = Sensor_VL53LX_Create(Dev_sensorl3_front);
    sensors[REAR_SENSOR_IDX] = Sensor_VL53L5CX_Create(&dev_sensorl5_rear);

    for (i = 0; i < SENSORS_NUMBER; ++i) {
        if (SENSOR_OK != Sensor_Init(&sensors[i])) {
            printf("error %d\n\r", i);
            return SENSOR_ERROR;
        }
    }

    return SENSOR_OK;
}

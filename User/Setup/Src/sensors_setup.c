#include "sensors_setup.h"
#include <stdio.h>
#include "gpio.h"
#include "sensor_vl53l3cx_adapter.h"
#include "sensor_vl53l5cx_adapter.h"

/* Global Access to Sensors and Sensors Data */
Sensor_Interface sensors[SENSORS_NUMBER];
Sensor_Data sensors_data[SENSORS_NUMBER];

/* Static sensor objects */
static VL53L3CX_Object_t VL53L3CX_sensors[SENSORS_NUMBER_L3];
static VL53L5CX_Object_t VL53L5CX_sensors[SENSORS_NUMBER_L5];

/* Sensor power pins and ports */
static GPIO_TypeDef* sensor_power_ports[SENSORS_NUMBER] = {
        S1_PWR_GPIO_Port, S2_PWR_GPIO_Port, S3_PWR_GPIO_Port, S4_PWR_GPIO_Port,
        S5_PWR_GPIO_Port, S6_PWR_GPIO_Port, S7_PWR_GPIO_Port, S8_PWR_GPIO_Port};

static uint16_t sensor_power_pins[SENSORS_NUMBER] = {S1_PWR_Pin, S2_PWR_Pin, S3_PWR_Pin,
                                                     S4_PWR_Pin, S5_PWR_Pin, S6_PWR_Pin,
                                                     S7_PWR_Pin, S8_PWR_Pin};
/* Sensor power pins and ports:
 * VL53L3CX:   VL53L5CX:
 * S1_PWR_Pin, S2_PWR_Pin -> Front
 * S3_PWR_Pin, S4_PWR_Pin -> Left
 * S6_PWR_Pin, S5_PWR_Pin -> Right
 * S7_PWR_Pin, S8_PWR_Pin -> Rear
 */

/* Private function declarations */
/**
 * @brief Set power state of a sensor.
 * @param sensor_index Index of the sensor.
 * @param state GPIO_PIN_SET to turn on, GPIO_PIN_RESET to turn off.
 */
static void set_sensor_power(uint8_t sensor_index, uint8_t power_state);

/**
 * @brief Reset all sensors by turning them off and on with delays.
 */
static void reset_all_sensors(void);

Sensor_Status Sensors_Setup(void) {
    Sensor_Status status = SENSOR_OK;
    uint16_t i, addr;

    reset_all_sensors();

    // disable all sensors
    for (i = 0; i < SENSORS_NUMBER; ++i) {
        set_sensor_power(i, GPIO_PIN_RESET);
    }

    // initialize sensors
    for (i = 0; i < SENSORS_NUMBER; ++i) {
        addr = CALC_SENSOR_ADDR(i);

        if (i % 2) {
            VL53L5CX_Object_t* Dev = &VL53L5CX_sensors[i / 2];
            Dev->IO.Address = SENSOR_DEFAULT_ADDR;
            Dev->IO.Init = BSP_I2C1_Init;
            Dev->IO.DeInit = BSP_I2C1_DeInit;
            Dev->IO.WriteReg = BSP_I2C1_WriteReg16;
            Dev->IO.ReadReg = BSP_I2C1_ReadReg16;
            Dev->IO.GetTick = BSP_GetTick;

            if (VL53L5CX_OK != VL53L5CX_RegisterBusIO(Dev, &Dev->IO)) {
                printf("Failed to register bus IO for L5 %d sensor.\n\r", i);
                status = SENSOR_ERROR;
            }
            set_sensor_power(i, GPIO_PIN_SET);
            VL53L5CX_SetAddress(Dev, addr);
            sensors[i] = Sensor_VL53L5CX_Create(Dev);
        } else {
            VL53L3CX_Object_t* Dev = &VL53L3CX_sensors[i / 2];
            Dev->IO.Address = SENSOR_DEFAULT_ADDR;
            Dev->IO.Init = BSP_I2C1_Init;
            Dev->IO.DeInit = BSP_I2C1_DeInit;
            Dev->IO.WriteReg = BSP_I2C1_Send;
            Dev->IO.ReadReg = BSP_I2C1_Recv;
            Dev->IO.GetTick = BSP_GetTick;
            if (VL53L3CX_OK != VL53L3CX_RegisterBusIO(Dev, &Dev->IO)) {
                printf("Failed to register bus IO for L3 %d sensor.\n\r", i);
                status = SENSOR_ERROR;
            }
            set_sensor_power(i, GPIO_PIN_SET);
            VL53L3CX_SetAddress(Dev, addr);
            sensors[i] = Sensor_VL53L3CX_Create(Dev);
        }

        if (SENSOR_OK != Sensor_Init(&sensors[i])) {
            printf("Failed to initialize sensor %d.\n\r", i);
            status = SENSOR_ERROR;
        }
    }

    return status;
}

static void set_sensor_power(uint8_t sensor_index, uint8_t power_state) {
    if (sensor_index >= SENSORS_NUMBER) {
        return;
    }

    if (power_state) {
        HAL_GPIO_WritePin(sensor_power_ports[sensor_index], sensor_power_pins[sensor_index],
                          GPIO_PIN_SET);
    } else {
        HAL_GPIO_WritePin(sensor_power_ports[sensor_index], sensor_power_pins[sensor_index],
                          GPIO_PIN_RESET);
    }
    HAL_Delay(2);
}

static void reset_all_sensors(void) {
    for (uint8_t i = 0; i < SENSORS_NUMBER; i++) {
        set_sensor_power(i, GPIO_PIN_RESET);
    }
    HAL_Delay(2);
    for (uint8_t i = 0; i < SENSORS_NUMBER; i++) {
        set_sensor_power(i, GPIO_PIN_SET);
    }
    HAL_Delay(2);
    for (uint8_t i = 0; i < SENSORS_NUMBER; i++) {
        set_sensor_power(i, GPIO_PIN_RESET);
    }
    HAL_Delay(2);
    for (uint8_t i = 0; i < SENSORS_NUMBER; i++) {
        set_sensor_power(i, GPIO_PIN_SET);
    }
    HAL_Delay(2);
}

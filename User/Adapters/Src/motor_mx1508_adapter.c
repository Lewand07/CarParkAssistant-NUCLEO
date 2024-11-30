#include "motor_mx1508_adapter.h"

Motor_Status Motor_Adapter_MX1508Init(void* motor_instance) {
    MX1508_Motor_DEV* dev = (MX1508_Motor_DEV*)motor_instance;

    if (NULL == dev || MX1508_OK != MX1508_Init(dev)) {
        return MOTOR_ERROR;
    }

    return MOTOR_OK;
}

Motor_Status Motor_Adapter_MX1508SetSpeed(void* motor_instance, int direction, uint8_t speed) {
    MX1508_Motor_DEV* dev = (MX1508_Motor_DEV*)motor_instance;

    if (NULL == dev ||
        MX1508_OK != MX1508_SetSpeed(dev, (MX1508_Motor_Direction)direction, speed)) {
        return MOTOR_ERROR;
    }

    return MOTOR_OK;
}

Motor_Status Motor_Adapter_MX1508Stop(void* motor_instance) {
    MX1508_Motor_DEV* dev = (MX1508_Motor_DEV*)motor_instance;

    if ((NULL == dev) || (MX1508_OK != MX1508_Stop(dev))) {
        return MOTOR_ERROR;
    }

    return MOTOR_OK;
}

Motor_Interface Motor_MX1508Create(MX1508_Motor_DEV* motor_device) {
    Motor_Interface motor = {NULL, NULL, NULL, NULL};

    if (NULL != motor_device) {
        motor.motor_instance = motor_device;
        motor.initialize = Motor_Adapter_MX1508Init;
        motor.set_speed = Motor_Adapter_MX1508SetSpeed;
        motor.stop = Motor_Adapter_MX1508Stop;
    }

    return motor;
}

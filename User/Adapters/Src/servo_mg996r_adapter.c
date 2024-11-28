#include "servo_mg996r_adapter.h"


Servo_Status Servo_Adapter_MG996RInit(void* servo_instance) {
    MG996R_Servo_DEV* dev = (MG996R_Servo_DEV*)servo_instance;

    if (NULL == dev || MG996R_OK != MG996R_Init(dev)) {
        return SERVO_ERROR;
    }

    return SERVO_OK;
}

Servo_Status Servo_Adapter_MG996RSetAngle(void* servo_instance, float angle) {
    MG996R_Servo_DEV* dev = (MG996R_Servo_DEV*)servo_instance;

    if (NULL == dev || MG996R_OK != MG996R_SetAngle(dev, angle)) {
        return SERVO_ERROR;
    }

    return SERVO_OK;
}

Servo_Interface Servo_MG996RCreate(MG996R_Servo_DEV* servo_device) {
    Servo_Interface servo = { NULL, NULL, NULL };

    if (NULL != servo_device) {
        servo.servo_instance = servo_device;
        servo.initialize = Servo_Adapter_MG996RInit;
        servo.set_angle = Servo_Adapter_MG996RSetAngle;
    }

    return servo;
}

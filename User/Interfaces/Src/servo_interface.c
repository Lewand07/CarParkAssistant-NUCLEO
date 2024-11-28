#include "servo_interface.h"

Servo_Status Servo_Init(Servo_Interface* servo) {
    if ((NULL == servo) || (NULL == servo->initialize)) {
        return SERVO_ERROR;
    }

    return servo->initialize(servo->servo_instance);
}

Servo_Status Servo_SetAngle(Servo_Interface* servo, float angle) {
    if ((NULL == servo) || (NULL == servo->set_angle)) {
        return SERVO_ERROR;
    }

    return servo->set_angle(servo->servo_instance, angle);
}

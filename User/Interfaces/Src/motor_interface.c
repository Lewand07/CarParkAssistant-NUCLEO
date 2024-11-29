#include "motor_interface.h"

Motor_Status Motor_Init(Motor_Interface* motor) {
    if ((NULL == motor) || (NULL == motor->initialize)) {
        return MOTOR_ERROR;
    }

    return motor->initialize(motor->motor_instance);
}

Motor_Status Motor_SetSpeed(Motor_Interface* motor, int direction, uint8_t speed) {
    if ((NULL == motor) || (NULL == motor->set_speed)) {
        return MOTOR_ERROR;
    }

    return motor->set_speed(motor->motor_instance, direction, speed);
}

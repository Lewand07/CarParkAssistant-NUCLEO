#include "car_interface.h"

Car_Status Car_Init(Car_Interface* car) {
    if (NULL == car) {
        return CAR_ERROR;
    }

    /* Initialize motor */
    if (MOTOR_OK != Motor_Init(&car->motor)) {
        return CAR_ERROR_MOTOR;
    }

    /* Initialize servo */
    if (SERVO_OK != Servo_Init(&car->servo)) {
        return CAR_ERROR_SERVO;
    }

    return CAR_OK;
}

Car_Status Car_SetSteering(Car_Interface* car, float angle) {
    if (NULL == car) {
        return CAR_ERROR;
    }

    if (SERVO_OK != Servo_SetAngle(&car->servo, angle)) {
        return CAR_ERROR_SERVO;
    }

    return CAR_OK;
}

Car_Status Car_SetSpeed(Car_Interface* car, Car_Direction direction, uint8_t speed) {
    if (NULL == car) {
        return CAR_ERROR;
    }

    if (MOTOR_OK != Motor_SetSpeed(&car->motor, (int)direction, speed)) {
        return CAR_ERROR_MOTOR;
    }

    return CAR_OK;
}

Car_Status Car_Stop(Car_Interface* car) {
    if (NULL == car) {
        return CAR_ERROR;
    }

    if (MOTOR_OK != Motor_Stop(&car->motor)) {
        return CAR_ERROR_MOTOR;
    }

    return CAR_OK;
}

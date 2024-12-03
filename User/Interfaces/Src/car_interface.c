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

Car_Status Car_HandleInstruction(Car_Interface* car, Car_Instruction instruction) {
    Car_Status status = CAR_OK;

    switch (instruction.direction) {
        case CAR_FORWARD:
            status = Car_SetSpeed(car, CAR_FORWARD, CAR_DEFAULT_SPEED);
            break;
        case CAR_BACKWARD:
            status = Car_SetSpeed(car, CAR_BACKWARD, CAR_DEFAULT_SPEED);
            break;
        case CAR_STOP:
            status = Car_Stop(car);
            break;
        default:
            break;
    }

    if (CAR_OK == status) {
        switch (instruction.steering) {
            case CAR_LEFT:
                status = Car_SetSteering(car, CAR_LEFT_ANGLE);
                break;
            case CAR_CENTER:
                status = Car_SetSteering(car, CAR_CENTER_ANGLE);
                break;
            case CAR_RIGHT:
                status = Car_SetSteering(car, CAR_RIGHT_ANGLE);
                break;
            default:
                break;
        }
    }

    return status;
}

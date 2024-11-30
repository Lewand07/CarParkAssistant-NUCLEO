#ifndef CAR_INTERFACE_H
#define CAR_INTERFACE_H

#include "motor_interface.h"
#include "servo_interface.h"

typedef enum {
    CAR_OK = 0,
    CAR_ERROR,
    CAR_ERROR_SERVO,
    CAR_ERROR_MOTOR
} Car_Status;

typedef struct {
    Motor_Interface motor;
    Servo_Interface servo;
} Car_Interface;

/**
 * @brief Initialize the car controller.
 * @param car Pointer to the car controller structure.
 * @return Status of the initialization.
 */
Car_Status Car_Init(Car_Interface* car);

/**
 * @brief Set the steering angle of the car.
 * @param car Pointer to the car controller structure.
 * @param angle Steering angle (0–180°).
 * @return Status of the operation.
 */
Car_Status Car_SetSteering(Car_Interface* car, float angle);

/**
 * @brief Set the car speed and direction.
 * @param car Pointer to the car controller structure.
 * @param direction Desired direction (FORWARD or BACKWARD).
 * @param speed Speed as a percentage (0–100%).
 * @return Status of the operation.
 */
Car_Status Car_SetSpeed(Car_Interface* car, int direction, uint8_t speed);

/**
 * @brief Stop the car.
 * @param car Pointer to the car controller structure.
 * @return Status of the operation.
 */
Car_Status Car_Stop(Car_Interface* car);

#endif  // CAR_INTERFACE_H

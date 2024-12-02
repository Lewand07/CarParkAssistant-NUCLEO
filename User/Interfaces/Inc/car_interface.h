#ifndef CAR_INTERFACE_H
#define CAR_INTERFACE_H

#include "motor_interface.h"
#include "servo_interface.h"

// Default car steering macros (redefine in the setup file if needed)
#define CAR_STEERING_LEFT   0.f
#define CAR_STEERING_RIGHT  180.f
#define CAR_STEERING_CENTER 90.f

typedef enum {
    CAR_OK = 0,
    CAR_ERROR,
    CAR_ERROR_SERVO,
    CAR_ERROR_MOTOR
} Car_Status;

typedef enum {
    CAR_FORWARD,
    CAR_BACKWARD,
    CAR_STOP,
    CAR_COAST
} Car_Direction;

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
Car_Status Car_SetSpeed(Car_Interface* car, Car_Direction direction, uint8_t speed);

/**
 * @brief Stop the car.
 * @param car Pointer to the car controller structure.
 * @return Status of the operation.
 */
Car_Status Car_Stop(Car_Interface* car);

#endif  // CAR_INTERFACE_H

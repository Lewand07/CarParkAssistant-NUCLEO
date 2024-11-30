#ifndef MOTOR_INTERFACE_H
#define MOTOR_INTERFACE_H

#include <stddef.h>
#include <stdint.h>

typedef enum {
    MOTOR_OK = 0,
    MOTOR_ERROR
} Motor_Status;

typedef struct {
    void* motor_instance;

    /* Function pointers for motor operations */
    Motor_Status (*initialize)(void* motor_instance);
    Motor_Status (*set_speed)(void* motor_instance, int direction, uint8_t speed);
    Motor_Status (*stop)(void* motor_instance);
} Motor_Interface;

/**
 * @brief Initialize the motor interface.
 * @param motor Pointer to the motor interface structure.
 * @return Status of the operation.
 */
Motor_Status Motor_Init(Motor_Interface* motor);

/**
 * @brief Set the speed of the motor.
 * @param motor Pointer to the motor interface structure.
 * @param direction Value of the moving direction.
 * @param speed Speed in percentage (0 - 100%).
 * @return Status of the operation.
 */
Motor_Status Motor_SetSpeed(Motor_Interface* motor, int direction, uint8_t speed);

/**
 * @brief Stop the motor.
 * @param motor Pointer to the motor interface structure.
 * @return Status of the operation.
 */
Motor_Status Motor_Stop(Motor_Interface* motor);

#endif  // MOTOR_INTERFACE_H

#ifndef SERVO_INTERFACE_H
#define SERVO_INTERFACE_H

#include <stddef.h>

typedef enum {
    SERVO_OK = 0,
    SERVO_ERROR
} Servo_Status;

typedef struct {
    void* servo_instance;

    /* Function pointers for servo operations */
    Servo_Status (*initialize)(void* servo_instance);
    Servo_Status (*set_angle)(void* servo_instance, float angle);
} Servo_Interface;

/**
 * @brief Initialize the servo interface.
 * @param servo Pointer to the servo interface structure.
 * @return Status of the operation.
 */
Servo_Status Servo_Init(Servo_Interface* servo);

/**
 * @brief Set the angle of the servo.
 * @param servo Pointer to the servo interface structure.
 * @param angle Steering angle (0–180°).
 * @return Status of the operation.
 */
Servo_Status Servo_SetAngle(Servo_Interface* servo, float angle);

#endif // SERVO_INTERFACE_H

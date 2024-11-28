#ifndef SERVO_MG996R_ADAPTER_H
#define SERVO_MG996R_ADAPTER_H

#include "mg996r_servo_api.h"
#include "servo_interface.h"


/**
 * @brief Initialize the servo interface.
 * @param servo_instance Pointer to the servo instance structure.
 * @return Status of the operation.
 */
Servo_Status Servo_Adapter_MG996RInit(void* servo_instance);

/**
 * @brief Set the angle of the servo.
 * @param servo_instance Pointer to the servo instance structure.
 * @param angle Steering angle (0–180°).
 * @return Status of the operation.
 */
Servo_Status Servo_Adapter_MG996RSetAngle(void* servo_instance, float angle);

/**
 * @brief Create the servo interface.
 * @param servo_device Pointer to the MG-996R servo structure.
 * @return Servo interface.
 */
Servo_Interface Servo_MG996RCreate(MG996R_Servo_DEV* servo_device);

#endif // SERVO_MG996R_ADAPTER_H

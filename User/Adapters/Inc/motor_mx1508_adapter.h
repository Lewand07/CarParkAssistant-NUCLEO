#ifndef MOTOR_MX1508_ADAPTER_H
#define MOTOR_MX1508_ADAPTER_H

#include "motor_interface.h"
#include "mx1508_motor_api.h"

/**
 * @brief Initialize the motor interface.
 * @param motor_instance Pointer to the motor instance structure.
 * @return Status of the operation.
 */
Motor_Status Motor_Adapter_MX1508_Init(void* motor_instance);

/**
 * @brief Set the speed of the motor.
 * @param motor Pointer to the motor interface structure.
 * @param direction Value of the moving direction (enum from the driver).
 * @param speed Speed in percentage (0 - 100%).
 * @return Status of the operation.
 */
Motor_Status Motor_Adapter_MX1508_SetSpeed(void* motor_instance, int direction, uint8_t speed);

/**
 * @brief Stop the motor.
 * @param motor Pointer to the motor interface structure.
 * @return Status of the operation.
 */
Motor_Status Motor_Adapter_MX1508_Stop(void* motor_instance);

/**
 * @brief Create the motor interface.
 * @param motor_device Pointer to the MG-996R motor structure.
 * @return Motor interface.
 */
Motor_Interface Motor_MX1508_Create(MX1508_Motor_DEV* motor_device);

#endif  // MOTOR_MX1508_ADAPTER_H

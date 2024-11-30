#ifndef MX1508_MOTOR_API_H
#define MX1508_MOTOR_API_H

#include "stm32f7xx_hal.h"

/* Motor speed limits */
#define MAX_MOTOR_SPEED (100U)

/* Motor configuration */
typedef struct {
    TIM_HandleTypeDef* PWM_TIM_Instance; /* Timer instance */
    uint32_t PWM_Channel1;               /* Channel for PWM1 */
    uint32_t PWM_Channel2;               /* Channel for PWM2 */
    uint32_t PWM_CLK;                    /* Timer clock frequency in Hz */
} MX1508_Motor_DEV;

/* Motor direction */
typedef enum {
    MOTOR_FORWARD,
    MOTOR_BACKWARD,
    MOTOR_STOP,
    MOTOR_COAST
} MX1508_Motor_Direction;

/* Motor status */
typedef enum {
    MX1508_OK = 0,
    MX1508_ERROR_NULL_PTR,
    MX1508_ERROR_INVALID_SPEED,
    MX1508_ERROR_INVALID_CONFIG
} MX1508_Status;

/**
 * @brief Initialize the MX1508 motor driver.
 * @param dev Pointer to the motor configuration structure.
 * @return MX1508_Status indicating success or failure.
 */
MX1508_Status MX1508_Init(const MX1508_Motor_DEV* dev);

/**
 * @brief Set the motor speed and direction.
 * @param dev Pointer to the motor configuration structure.
 * @param direction Desired motor direction.
 * @param speed Speed as a percentage (0–100%).
 * @return MX1508_Status indicating success or failure.
 */
MX1508_Status MX1508_SetSpeed(const MX1508_Motor_DEV* dev, MX1508_Motor_Direction direction,
                              uint8_t speed);

/**
 * @brief Stop the motor.
 * @param dev Pointer to the motor configuration structure.
 * @return MX1508_Status indicating success or failure.
 */
MX1508_Status MX1508_Stop(const MX1508_Motor_DEV* dev);

#endif  // MX1508_MOTOR_API_H

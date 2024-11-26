#ifndef MG996R_SERVO_API_H_
#define MG996R_SERVO_API_H_

#include "stm32f7xx_hal.h"

/* Servo angle limits */
#define MG996R_MIN_ANGLE 0.0f
#define MG996R_MAX_ANGLE 180.0f

/* Servo Configuration */
typedef struct {
    TIM_HandleTypeDef* TIM_Instance; /* Pointer to the timer handle */
    volatile uint32_t* TIM_CCRx;     /* Pointer to the timer's CCR register */
    uint32_t TIM_Channel;            /* Timer channel */
    uint32_t TIM_CLK;                /* Timer clock frequency in Hz */
    float MinPulse;                  /* Minimum pulse width*/
    float MaxPulse;                  /* Maximum pulse width */
} MG996R_Servo_DEV;

/* Servo Status */
typedef enum {
    MG996R_OK = 0,
    MG996R_ERROR_NULL_PTR,
    MG996R_ERROR_INVALID_ANGLE,
    MG996R_ERROR_INVALID_CONFIG
} MG996R_Status;

/**
 * @brief Initialize the MG996R servo motor.
 * @param dev Pointer to the servo configuration structure.
 */
MG996R_Status MG996R_Init(const MG996R_Servo_DEV* dev);

/**
 * @brief Set the servo angle (in degrees, range 0–180°).
 * @param dev Pointer to the servo configuration structure.
 * @param angle Desired angle in degrees.
 */
MG996R_Status MG996R_SetAngle(const MG996R_Servo_DEV* dev, float angle);

/**
 * @brief Set the PWM pulse width directly (in timer ticks).
 * @param dev Pointer to the servo configuration structure.
 * @param pulse Pulse width in timer ticks.
 */
MG996R_Status MG996R_SetPulse(const MG996R_Servo_DEV* dev, uint16_t pulse);

#endif  // MG996R_SERVO_API_H_

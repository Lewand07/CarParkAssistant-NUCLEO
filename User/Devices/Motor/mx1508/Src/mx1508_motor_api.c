#include "mx1508_motor_api.h"

MX1508_Status MX1508_Init(const MX1508_Motor_DEV* dev) {
    if (NULL == dev) {
        return MX1508_ERROR_NULL_PTR;
    }

    /* Start PWM for both channels */
    if ((HAL_OK != HAL_TIM_PWM_Start(dev->PWM_TIM_Instance, dev->PWM_Channel1)) ||
        (HAL_OK != HAL_TIM_PWM_Start(dev->PWM_TIM_Instance, dev->PWM_Channel2))) {
        return MX1508_ERROR_INVALID_CONFIG;
    }

    return MX1508_OK;
}

MX1508_Status MX1508_SetSpeed(const MX1508_Motor_DEV* dev, MX1508_Motor_Direction direction,
                              uint8_t speed) {
    uint16_t duty_cycle;

    if (NULL == dev) {
        return MX1508_ERROR_NULL_PTR;
    }

    if (MAX_MOTOR_SPEED < speed) {
        return MX1508_ERROR_INVALID_SPEED;
    }

    /* Calculate the duty cycle */
    duty_cycle = (uint16_t)(((float)speed / 100.0f) * (float)dev->PWM_CLK);

    switch (direction) {
        case MOTOR_FORWARD:
            __HAL_TIM_SET_COMPARE(dev->PWM_TIM_Instance, dev->PWM_Channel1, duty_cycle);
            __HAL_TIM_SET_COMPARE(dev->PWM_TIM_Instance, dev->PWM_Channel2, 0U);
            break;

        case MOTOR_BACKWARD:
            __HAL_TIM_SET_COMPARE(dev->PWM_TIM_Instance, dev->PWM_Channel1, 0U);
            __HAL_TIM_SET_COMPARE(dev->PWM_TIM_Instance, dev->PWM_Channel2, duty_cycle);
            break;

        case MOTOR_STOP:
            return MX1508_Stop(dev);

        case MOTOR_COAST:
            __HAL_TIM_SET_COMPARE(dev->PWM_TIM_Instance, dev->PWM_Channel1, (uint16_t)dev->PWM_CLK);
            __HAL_TIM_SET_COMPARE(dev->PWM_TIM_Instance, dev->PWM_Channel2, (uint16_t)dev->PWM_CLK);
            break;

        default:
            return MX1508_ERROR_INVALID_CONFIG;
    }

    return MX1508_OK;
}

MX1508_Status MX1508_Stop(const MX1508_Motor_DEV* dev) {
    if (NULL == dev) {
        return MX1508_ERROR_NULL_PTR;
    }

    /* Set duty cycles to 0 to stop the motor */
    __HAL_TIM_SET_COMPARE(dev->PWM_TIM_Instance, dev->PWM_Channel1, 0U);
    __HAL_TIM_SET_COMPARE(dev->PWM_TIM_Instance, dev->PWM_Channel2, 0U);

    return MX1508_OK;
}

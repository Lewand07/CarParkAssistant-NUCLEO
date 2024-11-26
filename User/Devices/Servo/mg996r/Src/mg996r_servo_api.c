#include "mg996r_servo_api.h"

MG996R_Status MG996R_Init(const MG996R_Servo_DEV* dev) {
    if (NULL == dev) {
        return MG996R_ERROR_NULL_PTR;
    }

    if (HAL_OK != HAL_TIM_PWM_Start(dev->TIM_Instance, dev->TIM_Channel)) {
        return MG996R_ERROR_INVALID_CONFIG;
    }

    return MG996R_OK;
}

MG996R_Status MG996R_SetAngle(const MG996R_Servo_DEV* dev, float angle) {
    if (NULL == dev) {
        return MG996R_ERROR_NULL_PTR;
    }

    if (MG996R_MIN_ANGLE > angle || MG996R_MAX_ANGLE < angle) {
        return MG996R_ERROR_INVALID_ANGLE;
    }

    float pulse_ms = dev->MinPulse + ((angle / MG996R_MAX_ANGLE) * (dev->MaxPulse - dev->MinPulse));

    uint16_t pulse_ticks = (uint16_t)((pulse_ms * (float)dev->TIM_CLK) / 1000.0f);

    return MG996R_SetPulse(dev, pulse_ticks);
}

MG996R_Status MG996R_SetPulse(const MG996R_Servo_DEV* dev, uint16_t pulse) {
    if (NULL == dev) {
        return MG996R_ERROR_NULL_PTR;
    }

    *(dev->TIM_CCRx) = pulse;

    return MG996R_OK;
}

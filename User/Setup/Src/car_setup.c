#include "car_setup.h"

#include "motor_mx1508_adapter.h"
#include "servo_mg996r_adapter.h"

Car_Interface car;

/* Static Motor and Servo Devices */
static MX1508_Motor_DEV motor_dev = {.PWM_TIM_Instance = &htim3,
                                     .PWM_Channel1 = TIM_CHANNEL_1,
                                     .PWM_Channel2 = TIM_CHANNEL_2,
                                     .PWM_CLK = 1000U};

static MG996R_Servo_DEV servo_dev = {.TIM_Instance = &htim2,
                                     .TIM_Channel = TIM_CHANNEL_1,
                                     // servo_dev.TIM_CCRx is handled inside the function
                                     .TIM_CLK = 10000U,
                                     .MinPulse = 1.0f,
                                     .MaxPulse = 2.0f};

Car_Status Car_Setup(void) {
    // handle non-static member initialization
    servo_dev.TIM_CCRx = &htim2.Instance->CCR1;

    car.motor = Motor_MX1508_Create(&motor_dev);
    car.servo = Servo_MG996R_Create(&servo_dev);

    return Car_Init(&car);
}

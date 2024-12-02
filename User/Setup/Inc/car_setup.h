#ifndef CAR_SETUP_H
#define CAR_SETUP_H

#include "car_interface.h"
#include "tim.h"

// Override car steering macros (hardware specific values)
#if defined CAR_STEERING_LEFT
#undef CAR_STEERING_LEFT
#endif
#if defined CAR_STEERING_RIGHT
#undef CAR_STEERING_RIGHT
#endif
#if defined CAR_STEERING_CENTER
#undef CAR_STEERING_CENTER
#endif

#define CAR_STEERING_LEFT   10.f
#define CAR_STEERING_RIGHT  170.f
#define CAR_STEERING_CENTER 90.f
/* Global Access to Car */
extern Car_Interface car;

/**
 * @brief Initialize all devices and the car interface.
 * @return Status of the setup.
 */
Car_Status Car_Setup(void);

#endif  // CAR_SETUP_H

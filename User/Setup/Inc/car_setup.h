#ifndef CAR_SETUP_H
#define CAR_SETUP_H

#include "car_interface.h"
#include "tim.h"

// Override car steering macros (hardware specific values)
#if defined CAR_LEFT_ANGLE
#undef CAR_LEFT_ANGLE
#endif
#if defined CAR_RIGHT_ANGLE
#undef CAR_RIGHT_ANGLE
#endif
#if defined CAR_CENTER_ANGLE
#undef CAR_CENTER_ANGLE
#endif

#define CAR_LEFT_ANGLE   10.f
#define CAR_RIGHT_ANGLE  170.f
#define CAR_CENTER_ANGLE 90.f
/* Global Access to Car */
extern Car_Interface car;

/**
 * @brief Initialize all devices and the car interface.
 * @return Status of the setup.
 */
Car_Status Car_Setup(void);

#endif  // CAR_SETUP_H

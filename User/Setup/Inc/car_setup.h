#ifndef CAR_SETUP_H
#define CAR_SETUP_H

#include "car_interface.h"
#include "sensor_interface.h"
#include "tim.h"

/* Global Access to Car */
extern Car_Interface car;

/**
 * @brief Initialize all devices and the car interface.
 * @return Status of the setup.
 */
Car_Status Car_Setup(void);

#endif /* CAR_SETUP_H */

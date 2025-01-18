/**
  ******************************************************************************
  * @file    custom_tof_conf.h
  * @author  IMG SW Application Team
  * @brief   This file contains definitions of the TOF components bus interfaces
  *          for custom boards
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CUSTOM_TOF_CONF_H__
#define __CUSTOM_TOF_CONF_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"
#include "stm32f7xx_nucleo_bus.h"
#include "stm32f7xx_nucleo_errno.h"

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

#define USE_CUSTOM_RANGING_VL53L3CX (1U)
#define USE_CUSTOM_RANGING_VL53L5CX (1U)

#define CUSTOM_VL53L3CX_I2C_INIT      BSP_I2C1_Init
#define CUSTOM_VL53L3CX_I2C_DEINIT    BSP_I2C1_DeInit
#define CUSTOM_VL53L3CX_I2C_WRITEREG  BSP_I2C1_Send
#define CUSTOM_VL53L3CX_I2C_READREG   BSP_I2C1_Recv

#define CUSTOM_VL53L5CX_I2C_INIT      BSP_I2C1_Init
#define CUSTOM_VL53L5CX_I2C_DEINIT    BSP_I2C1_DeInit
#define CUSTOM_VL53L5CX_I2C_WRITEREG  BSP_I2C1_WriteReg16
#define CUSTOM_VL53L5CX_I2C_READREG   BSP_I2C1_ReadReg16

#ifdef __cplusplus
}
#endif

#endif /* __CUSTOM_TOF_CONF_H__*/

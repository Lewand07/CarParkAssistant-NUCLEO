/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "sensors_task.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for CarControlTask */
osThreadId_t CarControlTaskHandle;
const osThreadAttr_t CarControlTask_attributes = {
  .name = "CarControlTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for SensorsTask */
osThreadId_t SensorsTaskHandle;
const osThreadAttr_t SensorsTask_attributes = {
  .name = "SensorsTask",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for ParkAssistTask */
osThreadId_t ParkAssistTaskHandle;
const osThreadAttr_t ParkAssistTask_attributes = {
  .name = "ParkAssistTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartCarControlTask(void *argument);
void StartSensorsTask(void *argument);
void StartParkAssistTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of CarControlTask */
  CarControlTaskHandle = osThreadNew(StartCarControlTask, NULL, &CarControlTask_attributes);

  /* creation of SensorsTask */
  SensorsTaskHandle = osThreadNew(StartSensorsTask, NULL, &SensorsTask_attributes);

  /* creation of ParkAssistTask */
  ParkAssistTaskHandle = osThreadNew(StartParkAssistTask, NULL, &ParkAssistTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartCarControlTask */
/**
  * @brief  Function implementing the CarControlTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartCarControlTask */
void StartCarControlTask(void *argument)
{
  /* USER CODE BEGIN StartCarControlTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartCarControlTask */
}

/* USER CODE BEGIN Header_StartSensorsTask */
/**
* @brief Function implementing the SensorsTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartSensorsTask */
void StartSensorsTask(void *argument)
{
  /* USER CODE BEGIN StartSensorsTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartSensorsTask */
}

/* USER CODE BEGIN Header_StartParkAssistTask */
/**
* @brief Function implementing the ParkAssistTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartParkAssistTask */
void StartParkAssistTask(void *argument)
{
  /* USER CODE BEGIN StartParkAssistTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartParkAssistTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */


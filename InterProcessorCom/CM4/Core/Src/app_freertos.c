/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : app_freertos.c
  * Description        : Code for freertos applications
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
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
typedef StaticTimer_t osStaticTimerDef_t;
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
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for AppTask */
osThreadId_t AppTaskHandle;
const osThreadAttr_t AppTask_attributes = {
  .name = "AppTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityRealtime1,
};
/* Definitions for Timer_5ms */
osTimerId_t Timer_5msHandle;
const osTimerAttr_t Timer_5ms_attributes = {
  .name = "Timer_5ms"
};
/* Definitions for Timer_10ms */
osTimerId_t Timer_10msHandle;
osStaticTimerDef_t Timer_10msControlBlock;
const osTimerAttr_t Timer_10ms_attributes = {
  .name = "Timer_10ms",
  .cb_mem = &Timer_10msControlBlock,
  .cb_size = sizeof(Timer_10msControlBlock),
};
/* Definitions for Timer_25ms */
osTimerId_t Timer_25msHandle;
const osTimerAttr_t Timer_25ms_attributes = {
  .name = "Timer_25ms"
};
/* Definitions for Timer_50ms */
osTimerId_t Timer_50msHandle;
osStaticTimerDef_t Timer_50msControlBlock;
const osTimerAttr_t Timer_50ms_attributes = {
  .name = "Timer_50ms",
  .cb_mem = &Timer_50msControlBlock,
  .cb_size = sizeof(Timer_50msControlBlock),
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void AppTask_Entry(void *argument);
void App_Cyclic_Task_5ms(void *argument);
void App_Cyclic_Task_10ms(void *argument);
void App_Cyclic_Task_25ms(void *argument);
void App_Cyclic_Task_50ms(void *argument);

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

  /* Create the timer(s) */
  /* creation of Timer_5ms */
  Timer_5msHandle = osTimerNew(App_Cyclic_Task_5ms, osTimerPeriodic, NULL, &Timer_5ms_attributes);

  /* creation of Timer_10ms */
  Timer_10msHandle = osTimerNew(App_Cyclic_Task_10ms, osTimerPeriodic, NULL, &Timer_10ms_attributes);

  /* creation of Timer_25ms */
  Timer_25msHandle = osTimerNew(App_Cyclic_Task_25ms, osTimerPeriodic, NULL, &Timer_25ms_attributes);

  /* creation of Timer_50ms */
  Timer_50msHandle = osTimerNew(App_Cyclic_Task_50ms, osTimerPeriodic, NULL, &Timer_50ms_attributes);

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of AppTask */
  AppTaskHandle = osThreadNew(AppTask_Entry, NULL, &AppTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
__weak void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_AppTask_Entry */
/**
* @brief Function implementing the AppTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_AppTask_Entry */
__weak void AppTask_Entry(void *argument)
{
  /* USER CODE BEGIN AppTask_Entry */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END AppTask_Entry */
}

/* App_Cyclic_Task_5ms function */
__weak void App_Cyclic_Task_5ms(void *argument)
{
  /* USER CODE BEGIN App_Cyclic_Task_5ms */

  /* USER CODE END App_Cyclic_Task_5ms */
}

/* App_Cyclic_Task_10ms function */
__weak void App_Cyclic_Task_10ms(void *argument)
{
  /* USER CODE BEGIN App_Cyclic_Task_10ms */

  /* USER CODE END App_Cyclic_Task_10ms */
}

/* App_Cyclic_Task_25ms function */
__weak void App_Cyclic_Task_25ms(void *argument)
{
  /* USER CODE BEGIN App_Cyclic_Task_25ms */

  /* USER CODE END App_Cyclic_Task_25ms */
}

/* App_Cyclic_Task_50ms function */
__weak void App_Cyclic_Task_50ms(void *argument)
{
  /* USER CODE BEGIN App_Cyclic_Task_50ms */

  /* USER CODE END App_Cyclic_Task_50ms */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

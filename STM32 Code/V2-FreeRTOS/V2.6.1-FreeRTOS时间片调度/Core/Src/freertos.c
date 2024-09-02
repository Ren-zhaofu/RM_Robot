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
List_t          TestList;
ListItem_t      ListItem1;
ListItem_t      ListItem2;
ListItem_t      ListItem3;
/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for LED_Red */
osThreadId_t LED_RedHandle;
const osThreadAttr_t LED_Red_attributes = {
  .name = "LED_Red",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for LED_Green */
osThreadId_t LED_GreenHandle;
const osThreadAttr_t LED_Green_attributes = {
  .name = "LED_Green",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for KEY */
osThreadId_t KEYHandle;
const osThreadAttr_t KEY_attributes = {
  .name = "KEY",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void Task_LED_Red(void *argument);
void Task_LED_Green(void *argument);
void Task_KEY(void *argument);

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
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of LED_Red */
  LED_RedHandle = osThreadNew(Task_LED_Red, NULL, &LED_Red_attributes);

  /* creation of LED_Green */
  LED_GreenHandle = osThreadNew(Task_LED_Green, NULL, &LED_Green_attributes);

  /* creation of KEY */
  KEYHandle = osThreadNew(Task_KEY, NULL, &KEY_attributes);

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
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_Task_LED_Red */
/**
* @brief Function implementing the LED_Red thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Task_LED_Red */
void Task_LED_Red(void *argument)
{
  /* USER CODE BEGIN Task_LED_Red */
  /* Infinite loop */
  for(;;)
  {
    LED_Red_Toggle();
    osDelay(1000);
  }
  /* USER CODE END Task_LED_Red */
}

/* USER CODE BEGIN Header_Task_LED_Green */
/**
* @brief Function implementing the LED_Green thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Task_LED_Green */
void Task_LED_Green(void *argument)
{
  /* USER CODE BEGIN Task_LED_Green */
  uint32_t task1_num = 0;
  /* Infinite loop */
  for(;;)
  {
    taskENTER_CRITICAL();
    printf("task1运行次数：%d\r\n",++task1_num);
    taskEXIT_CRITICAL();
//    LED_Green_Toggle();
    Delay_ms(10);
  }
  /* USER CODE END Task_LED_Green */
}

/* USER CODE BEGIN Header_Task_KEY */
/**
* @brief Function implementing the KEY thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Task_KEY */
void Task_KEY(void *argument)
{
  /* USER CODE BEGIN Task_KEY */
  uint32_t task2_num = 0;
  /* Infinite loop */
  for(;;)
  {
    taskENTER_CRITICAL();
    printf("task2运行次数：%d\r\n",++task2_num);
    taskEXIT_CRITICAL();
//    LED_Green_Toggle();
    Delay_ms(10);
  }
  /* USER CODE END Task_KEY */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */


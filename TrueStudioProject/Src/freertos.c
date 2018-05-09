/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2018 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

/* USER CODE BEGIN Includes */     
#include "ADC_MC.h"
#include "Matlab.h"
/* USER CODE END Includes */

/* Variables -----------------------------------------------------------------*/
osThreadId defaultTaskHandle;
uint32_t defaultTaskBuffer[ 256 ];
osStaticThreadDef_t defaultTaskControlBlock;
osThreadId CAN_IRQHandle;
uint32_t CAN_Buffer[ 1024 ];
osStaticThreadDef_t CAN_ControlBlock;
osThreadId MatlabHandle;
uint32_t MatlabBuffer[ 1024 ];
osStaticThreadDef_t MatlabControlBlock;
osThreadId ADC1_IRQHandle;
uint32_t ADC1_Buffer[ 1024 ];
osStaticThreadDef_t ADC1_ControlBlock;
osThreadId ADC2_IRQHandle;
uint32_t ADC2_5Buffer[ 256 ];
osStaticThreadDef_t ADC2_ControlBlock;
osSemaphoreId ADC1Handle;
osStaticSemaphoreDef_t ADC1_SEM_ControlBlock;
osSemaphoreId CANHandle;
osStaticSemaphoreDef_t CAN_SEM_ControlBlock;
osSemaphoreId ADC2Handle;
osStaticSemaphoreDef_t ADC2_SEM_ControlBlock;
osSemaphoreId Matlab_SEMHandle;
osStaticSemaphoreDef_t Matlab_ControlBlock;

/* USER CODE BEGIN Variables */

/* USER CODE END Variables */

/* Function prototypes -------------------------------------------------------*/
void StartDefaultTask(void const * argument);
void CAN_IRQ_Entry(void const * argument);
void Matlab_Entry(void const * argument);
void ADC1_Entry(void const * argument);
void ADC2_Entry(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* USER CODE BEGIN FunctionPrototypes */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc);
void HAL_ADC_ErrorCallback(ADC_HandleTypeDef *hadc);
/* USER CODE END FunctionPrototypes */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* Hook prototypes */

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];
  
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}                   
/* USER CODE END GET_IDLE_TASK_MEMORY */

/* Init FreeRTOS */

void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
       
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* definition and creation of ADC1 */
  osSemaphoreStaticDef(ADC1, &ADC1_SEM_ControlBlock);
  ADC1Handle = osSemaphoreCreate(osSemaphore(ADC1), 1);

  /* definition and creation of CAN */
  osSemaphoreStaticDef(CAN, &CAN_SEM_ControlBlock);
  CANHandle = osSemaphoreCreate(osSemaphore(CAN), 1);

  /* definition and creation of ADC2 */
  osSemaphoreStaticDef(ADC2, &ADC2_SEM_ControlBlock);
  ADC2Handle = osSemaphoreCreate(osSemaphore(ADC2), 1);

  /* definition and creation of Matlab_SEM */
  osSemaphoreStaticDef(Matlab_SEM, &Matlab_ControlBlock);
  Matlab_SEMHandle = osSemaphoreCreate(osSemaphore(Matlab_SEM), 1);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadStaticDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 256, defaultTaskBuffer, &defaultTaskControlBlock);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of CAN_IRQ */
  osThreadStaticDef(CAN_IRQ, CAN_IRQ_Entry, osPriorityHigh, 0, 1024, CAN_Buffer, &CAN_ControlBlock);
  CAN_IRQHandle = osThreadCreate(osThread(CAN_IRQ), NULL);

  /* definition and creation of Matlab */
  osThreadStaticDef(Matlab, Matlab_Entry, osPriorityNormal, 0, 1024, MatlabBuffer, &MatlabControlBlock);
  MatlabHandle = osThreadCreate(osThread(Matlab), NULL);

  /* definition and creation of ADC1_IRQ */
  osThreadStaticDef(ADC1_IRQ, ADC1_Entry, osPriorityAboveNormal, 0, 1024, ADC1_Buffer, &ADC1_ControlBlock);
  ADC1_IRQHandle = osThreadCreate(osThread(ADC1_IRQ), NULL);

  /* definition and creation of ADC2_IRQ */
  osThreadStaticDef(ADC2_IRQ, ADC2_Entry, osPriorityIdle, 0, 256, ADC2_5Buffer, &ADC2_ControlBlock);
  ADC2_IRQHandle = osThreadCreate(osThread(ADC2_IRQ), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */
}

/* StartDefaultTask function */
void StartDefaultTask(void const * argument)
{

  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* CAN_IRQ_Entry function */
void CAN_IRQ_Entry(void const * argument)
{
  /* USER CODE BEGIN CAN_IRQ_Entry */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END CAN_IRQ_Entry */
}

/* Matlab_Entry function */
void Matlab_Entry(void const * argument)
{
  /* USER CODE BEGIN Matlab_Entry */
	Matlab_Init();
  /* Infinite loop */
  for(;;)
  {
	  osSemaphoreWait(Matlab_SEMHandle,0);
	  Matlab_Step();
  }
  /* USER CODE END Matlab_Entry */
}

/* ADC1_Entry function */
void ADC1_Entry(void const * argument)
{
  /* USER CODE BEGIN ADC1_Entry */
	ADC1_MC_Init();
  /* Infinite loop */
  for(;;)
  {
	  osSemaphoreWait(ADC1Handle,0);
	  ADC1_IRQ_Handler();
  }
  /* USER CODE END ADC1_Entry */
}

/* ADC2_Entry function */
void ADC2_Entry(void const * argument)
{
  /* USER CODE BEGIN ADC2_Entry */
	ADC2_MC_Init();
  /* Infinite loop */
  for(;;)
  {
	  osSemaphoreWait(ADC2Handle,0);
	  ADC2_IRQ_Handler();
  }
  /* USER CODE END ADC2_Entry */
}

/* USER CODE BEGIN Application */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	if(hadc==&hadc1)
		osSemaphoreRelease(ADC1Handle);
	if(hadc==&hadc2)
		osSemaphoreRelease(ADC2Handle);
};

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM2)
		osSemaphoreRelease(Matlab_SEMHandle);
}

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

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
#include "CAN_MC.h"
#include "MPU_6050_MC.h"
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
uint32_t ADC2_5Buffer[ 1024 ];
osStaticThreadDef_t ADC2_ControlBlock;
osThreadId CAN_IRQ_RxHandle;
uint32_t CAN_Rx_Buffer[ 1024 ];
osStaticThreadDef_t CAN_Rx_ControlBlock;
osThreadId TB_CANHandle;
uint32_t TB_CAN_7Buffer[ 256 ];
osStaticThreadDef_t TB_CAN_ControlBlock;
osThreadId MPUHandle;
uint32_t MPU_Buffer[ 256 ];
osStaticThreadDef_t MPU_ControlBlock;
osTimerId MatlabTimerHandle;
osStaticTimerDef_t MatlabTimerControlBlock;
osSemaphoreId ADC1Handle;
osStaticSemaphoreDef_t ADC1_SEM_ControlBlock;
osSemaphoreId CANHandle;
osStaticSemaphoreDef_t CAN_SEM_ControlBlock;
osSemaphoreId ADC2Handle;
osStaticSemaphoreDef_t ADC2_SEM_ControlBlock;
osSemaphoreId Matlab_SEMHandle;
osStaticSemaphoreDef_t Matlab_ControlBlock;
osSemaphoreId CAN_RXHandle;
osStaticSemaphoreDef_t CAN_RXControlBlock;
osSemaphoreId MPU_SEMHandle;
osStaticSemaphoreDef_t MPU_SEM_ControlBlock;

/* USER CODE BEGIN Variables */

/* USER CODE END Variables */

/* Function prototypes -------------------------------------------------------*/
void StartDefaultTask(void const * argument);
void CAN_IRQ_Entry(void const * argument);
void Matlab_Entry(void const * argument);
void ADC1_Entry(void const * argument);
void ADC2_Entry(void const * argument);
void CAN_IRQ_Rx_Entry(void const * argument);
void TB_CAN_Entry(void const * argument);
void MPU_Entry(void const * argument);
void MatlabTimerCallback(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* USER CODE BEGIN FunctionPrototypes */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc);
void HAL_ADC_ErrorCallback(ADC_HandleTypeDef *hadc);
/* USER CODE END FunctionPrototypes */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* GetTimerTaskMemory prototype (linked to static allocation support) */
void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize );

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

/* USER CODE BEGIN GET_TIMER_TASK_MEMORY */
static StaticTask_t xTimerTaskTCBBuffer;
static StackType_t xTimerStack[configTIMER_TASK_STACK_DEPTH];
  
void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize )  
{
  *ppxTimerTaskTCBBuffer = &xTimerTaskTCBBuffer;
  *ppxTimerTaskStackBuffer = &xTimerStack[0];
  *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
  /* place for user code */
}                   
/* USER CODE END GET_TIMER_TASK_MEMORY */

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

  /* definition and creation of CAN_RX */
  osSemaphoreStaticDef(CAN_RX, &CAN_RXControlBlock);
  CAN_RXHandle = osSemaphoreCreate(osSemaphore(CAN_RX), 1);

  /* definition and creation of MPU_SEM */
  osSemaphoreStaticDef(MPU_SEM, &MPU_SEM_ControlBlock);
  MPU_SEMHandle = osSemaphoreCreate(osSemaphore(MPU_SEM), 1);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* Create the timer(s) */
  /* definition and creation of MatlabTimer */
  osTimerStaticDef(MatlabTimer, MatlabTimerCallback, &MatlabTimerControlBlock);
  MatlabTimerHandle = osTimerCreate(osTimer(MatlabTimer), osTimerPeriodic, NULL);

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  osTimerStart(MatlabTimerHandle,50);
  /* USER CODE END RTOS_TIMERS */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadStaticDef(defaultTask, StartDefaultTask, osPriorityIdle, 0, 256, defaultTaskBuffer, &defaultTaskControlBlock);
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
  osThreadStaticDef(ADC2_IRQ, ADC2_Entry, osPriorityAboveNormal, 0, 1024, ADC2_5Buffer, &ADC2_ControlBlock);
  ADC2_IRQHandle = osThreadCreate(osThread(ADC2_IRQ), NULL);

  /* definition and creation of CAN_IRQ_Rx */
  osThreadStaticDef(CAN_IRQ_Rx, CAN_IRQ_Rx_Entry, osPriorityHigh, 0, 1024, CAN_Rx_Buffer, &CAN_Rx_ControlBlock);
  CAN_IRQ_RxHandle = osThreadCreate(osThread(CAN_IRQ_Rx), NULL);

  /* definition and creation of TB_CAN */
  osThreadStaticDef(TB_CAN, TB_CAN_Entry, osPriorityLow, 0, 256, TB_CAN_7Buffer, &TB_CAN_ControlBlock);
  TB_CANHandle = osThreadCreate(osThread(TB_CAN), NULL);

  /* definition and creation of MPU */
  osThreadStaticDef(MPU, MPU_Entry, osPriorityAboveNormal, 0, 256, MPU_Buffer, &MPU_ControlBlock);
  MPUHandle = osThreadCreate(osThread(MPU), NULL);

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
    osDelay(1000);
  }
  /* USER CODE END StartDefaultTask */
}

/* CAN_IRQ_Entry function */
void CAN_IRQ_Entry(void const * argument)
{
  /* USER CODE BEGIN CAN_IRQ_Entry */
	CAN_MC_Init();
	CAN_MC_Connect();
	CAN_MC_CyclicDataEnable();
  /* Infinite loop */
  for(;;)
  {
    osSemaphoreWait(CANHandle,osWaitForever);
    CAN_MC_TimerCallback();
  }
  /* USER CODE END CAN_IRQ_Entry */
}

/* Matlab_Entry function */
void Matlab_Entry(void const * argument)
{
  /* USER CODE BEGIN Matlab_Entry */
	osSemaphoreWait(Matlab_SEMHandle,osWaitForever);
	Matlab_Init();
  /* Infinite loop */
  for(;;)
  {
	  osSemaphoreWait(Matlab_SEMHandle,osWaitForever);
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
	  osSemaphoreWait(ADC1Handle,osWaitForever);
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
	  osSemaphoreWait(ADC2Handle,osWaitForever);
	  ADC2_IRQ_Handler();
  }
  /* USER CODE END ADC2_Entry */
}

/* CAN_IRQ_Rx_Entry function */
void CAN_IRQ_Rx_Entry(void const * argument)
{
  /* USER CODE BEGIN CAN_IRQ_Rx_Entry */
  /* Infinite loop */
  for(;;)
  {
    osSemaphoreWait(CAN_RXHandle,osWaitForever);
    CAN_MC_ReceiveCallback();
  }
  /* USER CODE END CAN_IRQ_Rx_Entry */
}

/* TB_CAN_Entry function */
void TB_CAN_Entry(void const * argument)
{
  /* USER CODE BEGIN TB_CAN_Entry */
	CanTxMsgTypeDef Tx;
  /* Infinite loop */
  for(;;)
  {
    osDelay(1000);
    CAN_MC_TorqueCommand(1000);
    WriteLED_Green(0);
    osDelay(1000);
    CAN_MC_TorqueCommand(-1000);
    WriteLED_Green(1);
    /*Tx.DLC=6;
    Tx.IDE=CAN_ID_STD;
    Tx.StdId=CAN_ID_RX;
    Tx.Data[0]=REG_BUS_DC;
    Tx.Data[1]=1;
    Tx.Data[2]=2;
    hcan.pTxMsg=&Tx;
    HAL_CAN_Transmit_IT(&hcan);*/
  }
  /* USER CODE END TB_CAN_Entry */
}

/* MPU_Entry function */
void MPU_Entry(void const * argument)
{
  /* USER CODE BEGIN MPU_Entry */
	MPU_6050_Init();
  /* Infinite loop */
  for(;;)
  {
    osSemaphoreWait(MPU_SEMHandle,osWaitForever);
    MPU_6050_GetData();
  }
  /* USER CODE END MPU_Entry */
}

/* MatlabTimerCallback function */
void MatlabTimerCallback(void const * argument)
{
  /* USER CODE BEGIN MatlabTimerCallback */
  osSemaphoreRelease(Matlab_SEMHandle);
  osSemaphoreRelease(CANHandle);
  osSemaphoreRelease(MPU_SEMHandle);
  /* USER CODE END MatlabTimerCallback */
}

/* USER CODE BEGIN Application */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	if(hadc->Instance==ADC1)
	{
		osSemaphoreRelease(ADC1Handle);
		//for Test
		//HAL_GPIO_TogglePin(Test_GPIO_Port,Test_Pin);
	}
	if(hadc->Instance==ADC2)
	{
		osSemaphoreRelease(ADC2Handle);
		//for Test
		//HAL_GPIO_TogglePin(Test_GPIO_Port,Test_Pin);
	}
};

void HAL_CAN_RxCpltCallback(CAN_HandleTypeDef* hcan)
{
	osSemaphoreRelease(CAN_RXHandle);
}

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

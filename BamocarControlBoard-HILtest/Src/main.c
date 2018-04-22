
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f3xx_hal.h"
#include "can.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* USER CODE BEGIN Includes */
#define CAN_DATA_LEN 4 //ilośc bajtów danych
#define CAN_ID_TX 0x201 //ID ramki wysyłanej do sterownika, wykorzystywane w filtrach
//#define CAN_ID_RX 0x181 //ID ramki odebranej ze sterownika, wykorzystywane w filtrach
#define CAN_ID_RX 0x201

//#include <string.h>
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
CanTxMsgTypeDef Tx; //struktura przechwoująca ramkę do wysłania
static uint8_t DataUART[CAN_DATA_LEN]; //dane odebrane przez UART
static uint8_t DataCAN[CAN_DATA_LEN]; //dane odebrane z magistrali CAN
CanRxMsgTypeDef Rx; //struktura przechwoująca ramkę do odebrania
CanRxMsgTypeDef Rx2; //do drugiej kolejki
CAN_FilterConfTypeDef Rx_Filter; //struktura do konfiguracji filtra
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/
void HAL_CAN_TxCpltCallback(CAN_HandleTypeDef *hcan){
	HAL_GPIO_WritePin(LEDMain_GPIO_Port, LEDMain_Pin, GPIO_PIN_SET); //świecimy jeśli wyślemy ramke
	TIM16->CNT=0;
	HAL_TIM_Base_Start_IT(&htim16);
}

void HAL_CAN_RxCpltCallback(CAN_HandleTypeDef *hcan){
// można dorzucic wewnętrzną weryfikację poprawności danych
//	if(Rx.Data[0]==cośtam)
//	i zapalanie innej diody z kolejnym timerem
//	HAL_GPIO_WritePin(LEDMain_GPIO_Port, LEDMain_Pin, GPIO_PIN_SET); //świecimy jeśli wyślemy ramke
//	TIM16->CNT=0;
//	HAL_TIM_Base_Start_IT(&htim16);

	uint8_t i;
	for(i=0; i<CAN_DATA_LEN; i++){
		DataCAN[i] = Rx.Data[i];
	}

	HAL_UART_Transmit_DMA(&huart2, DataCAN, sizeof(DataCAN)); //wysłanie danych przez UART

	HAL_CAN_Receive_IT(hcan, CAN_FIFO0); //powrót do nasłuchiwania przerwań
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim->Instance == TIM16){
		HAL_GPIO_WritePin(LEDMain_GPIO_Port, LEDMain_Pin, GPIO_PIN_RESET);
		HAL_TIM_Base_Stop_IT(&htim16);
	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	uint8_t i;
	for(i=0; i<CAN_DATA_LEN; i++){ //pętla do przepisania danych
		Tx.Data[i] = DataUART[i];
	}

	HAL_CAN_Transmit_IT(&hcan); //wysłanie ramki przez CANa

	HAL_UART_Receive_DMA(huart, DataUART, CAN_DATA_LEN); // ponowne włączenie nasłuchiwania na przerwania, byc może niekonieczne
}

//void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart){
//}
/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_TIM16_Init();
  MX_USART2_UART_Init();
  MX_CAN_Init();
  /* USER CODE BEGIN 2 */

  // konfiguracja przerwañ w CAN-ie
  __HAL_CAN_ENABLE_IT(&hcan, CAN_IT_FMP0);
  __HAL_CAN_ENABLE_IT(&hcan, CAN_IT_FMP1);

  //konfiguracja ramki nadawczej
  Tx.DLC = CAN_DATA_LEN;
  Tx.RTR = CAN_RTR_DATA;
  Tx.IDE = CAN_ID_STD; //wersja podstawowa ID
  Tx.StdId = CAN_ID_TX;
  hcan.pTxMsg = &Tx; //przekazanie konfiguracji ramki do głównej struktury

  //konfiguracja filtra ramki odbiorczej
  Rx_Filter.FilterNumber = 1;
  Rx_Filter.FilterMode = CAN_FILTERMODE_IDMASK;	//ustawiamy filtrowanie przez maske, a nie przez listę
  Rx_Filter.FilterMaskIdHigh = 0xFFFF; // obie maski na 1, nie mają wtedy znaczenia
  Rx_Filter.FilterMaskIdLow = 0xFFFF;
  Rx_Filter.FilterIdHigh = CAN_ID_RX << 5; //ustawiamy takie highID jakie ID ma p³ytka wysy³aj¹ca oraz przesuwamy bitowo o 5, bo ID ma tylko 11 bitów
  Rx_Filter.FilterIdLow = 0x00; //troche nie wiemy czemu ale zmiana low nic nie zmienia w dzia³aniu naszego kodu - bo tutaj w tym trybie filtrów podajecie drugi identyfikator, który filtr przepusci
  Rx_Filter.FilterActivation = ENABLE; //aktywacja filtra
  HAL_CAN_ConfigFilter(&hcan, &Rx_Filter); //odpalenie filtra

  //konfiguracja ramki odbiorczej
  hcan.pRxMsg = &Rx; //przesłąnie wskaźnika na ramkę do głównej struktury
  hcan.pRx1Msg = &Rx2; //dla drugiej kolejki
  HAL_CAN_Receive_IT(&hcan, CAN_FIFO0); //pierwsze przerwanie CAN na kolejce numer 0

  //pierwsze uruchomienie timera, konieczne ze względu na błąd w bibliotece HAL
  HAL_TIM_Base_Start_IT(&htim16); //tutaj wykonujemy start, stop i wyzerowanie timera, żeby wyeliminowac błąd, w którym
  HAL_TIM_Base_Stop_IT(&htim16);  // pierwsze przerwanie nie działało poprawnie
  TIM16->CNT=0;

  HAL_UART_Receive_DMA(&huart2, DataUART, CAN_DATA_LEN); //rozpoczęcie nasłuchiwania na dane z UARTa

  HAL_CAN_Receive_IT(&hcan, CAN_FIFO0); //pierwsze przerwanie CAN na kolejce numer 0
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */

  }
  /* USER CODE END 3 */

}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART2|RCC_PERIPHCLK_TIM16;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  PeriphClkInit.Tim16ClockSelection = RCC_TIM16CLK_HCLK;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1) 
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

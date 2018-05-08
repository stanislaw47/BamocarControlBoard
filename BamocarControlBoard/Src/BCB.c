#include "BCB.h"

//includes
#include <string.h>
#include "stm32f3xx_hal.h"

void BCB_Transmit(CanTxMsgTypeDef* pTx, CAN_HandleTypeDef *hpcan, uint8_t* Data){
	memcpy(pTx->Data, Data, sizeof(pTx->Data)); //przepisanie danych
	HAL_CAN_Transmit_IT(hpcan); //wysłanie ramki przez CANa
}

void BCB_Init(CAN_HandleTypeDef *hpcan){
	// konfiguracja przerwañ w CAN-ie
	__HAL_CAN_ENABLE_IT(hpcan, CAN_IT_FMP0);
	__HAL_CAN_ENABLE_IT(hpcan, CAN_IT_FMP1);

	//konfiguracja ramki nadawczej
	Tx.DLC = CAN_DATA_LEN_TX;
	Tx.RTR = CAN_RTR_DATA;
	Tx.IDE = CAN_ID_STD; //wersja podstawowa ID
	Tx.StdId = CAN_ID_TX;
	hpcan->pTxMsg = &Tx; //przekazanie konfiguracji ramki do głównej struktury

	//konfiguracja filtra ramki odbiorczej
	Rx_Filter.FilterNumber = 1;
	Rx_Filter.FilterMode = CAN_FILTERMODE_IDMASK;	//ustawiamy filtrowanie przez maske, a nie przez listę
	Rx_Filter.FilterMaskIdHigh = 0xFFFF; // obie maski na 1, nie mają wtedy znaczenia
	Rx_Filter.FilterMaskIdLow = 0xFFFF;
	Rx_Filter.FilterIdHigh = CAN_ID_RX << 5; //ustawiamy takie highID jakie ID ma p³ytka wysy³aj¹ca oraz przesuwamy bitowo o 5, bo ID ma tylko 11 bitów
	Rx_Filter.FilterIdLow = 0x00; //troche nie wiemy czemu ale zmiana low nic nie zmienia w dzia³aniu naszego kodu - bo tutaj w tym trybie filtrów podajecie drugi identyfikator, który filtr przepusci
	Rx_Filter.FilterActivation = ENABLE; //aktywacja filtra
	HAL_CAN_ConfigFilter(hpcan, &Rx_Filter); //odpalenie filtra

	//konfiguracja ramki odbiorczej
	hpcan->pRxMsg = &Rx; //przesłąnie wskaźnika na ramkę do głównej struktury
	hpcan->pRx1Msg = &Rx2; //dla drugiej kolejki
	HAL_CAN_Receive_IT(hpcan, CAN_FIFO0); //pierwsze przerwanie CAN na kolejce numer 0
}

void BCB_Connect(CAN_HandleTypeDef *hpcan){

}

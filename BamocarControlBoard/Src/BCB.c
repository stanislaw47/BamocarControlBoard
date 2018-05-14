#include "BCB.h"

//includes
#include <string.h>
#include "stm32f3xx_hal.h"


void BCB_Transmit(CAN_HandleTypeDef *hpcan, uint8_t d1, uint8_t d2, uint8_t d3){
	hpcan->pTxMsg->Data[0] = d1;
	hpcan->pTxMsg->Data[1] = d2;
	hpcan->pTxMsg->Data[2] = d3;
	while(HAL_CAN_Transmit_IT(hpcan) != HAL_OK)
		HAL_CAN_Transmit_IT(hpcan); //wysłanie ramki przez CANa
}

void BCB_Init(CAN_HandleTypeDef *hpcan){
	// włączenie obsługi przerwań CAN-a dla kolejek 0 oraz 1
	__HAL_CAN_ENABLE_IT(hpcan, CAN_IT_FMP0);
	__HAL_CAN_ENABLE_IT(hpcan, CAN_IT_FMP1);

	//konfiguracja ramki nadawczej
	TxMessage.DLC = CAN_DATA_LEN_TX;
	TxMessage.RTR = CAN_RTR_DATA;
	TxMessage.IDE = CAN_ID_STD; //wersja podstawowa ID
	TxMessage.StdId = CAN_ID_TX;
	hpcan->pTxMsg = &TxMessage; //przekazanie konfiguracji ramki do głównej struktury

	//konfiguracja filtra ramki odbiorczej
	RxFilter.FilterNumber = 1;
	RxFilter.FilterMode = CAN_FILTERMODE_IDMASK;	//ustawiamy filtrowanie przez maske, a nie przez listę
	RxFilter.FilterMaskIdHigh = 0xFFFF; // obie maski na 1, nie mają wtedy znaczenia
	RxFilter.FilterMaskIdLow = 0xFFFF;
	RxFilter.FilterIdHigh = CAN_ID_RX << 5; //ustawiamy takie highID jakie ID ma p³ytka wysy³aj¹ca oraz przesuwamy bitowo o 5, bo ID ma tylko 11 bitów
	RxFilter.FilterIdLow = 0x00; //troche nie wiemy czemu ale zmiana low nic nie zmienia w dzia³aniu naszego kodu - bo tutaj w tym trybie filtrów podajecie drugi identyfikator, który filtr przepusci
	RxFilter.FilterActivation = ENABLE; //aktywacja filtra
	if (HAL_CAN_ConfigFilter(hpcan, &RxFilter) != HAL_OK) //odpalenie filtra i jednoczesne sprawdzenie poprawności
		HAL_GPIO_WritePin(LEDMain_GPIO_Port, LEDMain_Pin, GPIO_PIN_SET);

	//konfiguracja ramki odbiorczej
	hpcan->pRxMsg = &RxMessage; //przesłąnie wskaźnika na ramkę do głównej struktury
	hpcan->pRx1Msg = &RxMessage2; //dla drugiej kolejki
	HAL_CAN_Receive_IT(hpcan, CAN_FIFO0);
}

void BCB_Connect(CAN_HandleTypeDef *hpcan){
	//wysłanie pierwszej ramki
	uint8_t tmp[CAN_DATA_LEN_RX] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

	// is device ready?
//	hpcan->pTxMsg->Data[0] = READ;
//	hpcan->pTxMsg->Data[1] = READY;
//	hpcan->pTxMsg->Data[2] = REPLY_NOW;
//	HAL_CAN_Transmit_IT(hpcan); //wysłanie ramki przez CANa
	BCB_Transmit(hpcan, READ, READY, REPLY_NOW);
	tmp[0] = READY;
	if(!memcmp(BCB_GetReady() , tmp, CAN_DATA_LEN_RX))
		HAL_GPIO_WritePin(LEDMain_GPIO_Port, LEDMain_Pin, GPIO_PIN_SET);

	//is FRG set?
//	hpcan->pTxMsg->Data[0] = READ;
//	hpcan->pTxMsg->Data[1] = FRG;
//	hpcan->pTxMsg->Data[2] = REPLY_NOW;
//	HAL_CAN_Transmit_IT(hpcan); //wysłanie ramki przez CANa
	BCB_Transmit(hpcan, READ, FRG, REPLY_NOW);
	tmp[0] = FRG;
	if(!memcmp(BCB_GetFRG(), tmp, CAN_DATA_LEN_RX))
		HAL_GPIO_WritePin(LEDMain_GPIO_Port, LEDMain_Pin, GPIO_PIN_SET);

//	HAL_Delay(1);
	//enable drive
//	hpcan->pTxMsg->Data[0] = MODE;
//	hpcan->pTxMsg->Data[1] = ENABLE;
//	hpcan->pTxMsg->Data[2] = 0x00;
//	HAL_CAN_Transmit_IT(hpcan); //wysłanie ramki przez CANa
	BCB_Transmit(hpcan, MODE, ENABLE, 0x00);
}

void BCB_CyclicDataEnable(CAN_HandleTypeDef *hpcan){
//	HAL_Delay(1); //ważne ze względu na przepełnienie kolejki ramek struktury hcan

	//konfiguracja wysyłania cyklicznie danych
//	hpcan->pTxMsg->Data[0] = READ;
//	hpcan->pTxMsg->Data[1] = SPEED;
//	hpcan->pTxMsg->Data[2] = DATA_FREQ;
//	HAL_CAN_Transmit_IT(hpcan); //wysłanie ramki przez CANa
	BCB_Transmit(hpcan, READ, SPEED, DATA_FREQ);

//	HAL_Delay(1);
//	hpcan->pTxMsg->Data[0] = READ;
//	hpcan->pTxMsg->Data[1] = TORQUE;
//	hpcan->pTxMsg->Data[2] = DATA_FREQ;
//	HAL_CAN_Transmit_IT(hpcan); //wysłanie ramki przez CANa
	BCB_Transmit(hpcan, READ, TORQUE, DATA_FREQ);

//	HAL_Delay(1);
//	hpcan->pTxMsg->Data[0] = READ;
//	hpcan->pTxMsg->Data[1] = BUS_DC;
//	hpcan->pTxMsg->Data[2] = DATA_FREQ;
//	HAL_CAN_Transmit_IT(hpcan); //wysłanie ramki przez CANa
	BCB_Transmit(hpcan, READ, BUS_DC, DATA_FREQ);
}

void BCB_CyclicDataDisable(CAN_HandleTypeDef *hpcan){
	//wyłączenie wysyłania danych cyklicznie
//	hpcan->pTxMsg->Data[0] = READ;
//	hpcan->pTxMsg->Data[1] = SPEED;
//	hpcan->pTxMsg->Data[2] = REPLY_STOP;
//	HAL_CAN_Transmit_IT(hpcan); //wysłanie ramki przez CANa
	BCB_Transmit(hpcan, READ, SPEED, REPLY_NOW);

//	hpcan->pTxMsg->Data[0] = READ;
//	hpcan->pTxMsg->Data[1] = TORQUE;
//	hpcan->pTxMsg->Data[2] = REPLY_STOP;
//	HAL_CAN_Transmit_IT(hpcan); //wysłanie ramki przez CANa
	BCB_Transmit(hpcan, READ, TORQUE, REPLY_STOP);

//	hpcan->pTxMsg->Data[0] = READ;
//	hpcan->pTxMsg->Data[1] = BUS_DC;
//	hpcan->pTxMsg->Data[2] = REPLY_STOP;
//	HAL_CAN_Transmit_IT(hpcan); //wysłanie ramki przez CANa
	BCB_Transmit(hpcan, READ, BUS_DC, REPLY_STOP);
}

void BCB_Disconnect(CAN_HandleTypeDef *hpcan){
	//wyłączenie sterownika
//	hpcan->pTxMsg->Data[0] = MODE;
//	hpcan->pTxMsg->Data[1] = DISABLE;
//	hpcan->pTxMsg->Data[2] = 0x00;
//	HAL_CAN_Transmit_IT(hpcan); //wysłanie ramki przez CANa
	BCB_Transmit(hpcan, MODE, DISABLE, 0x00);
}

void BCB_Lock(){
	Locked = 1;
}

void BCB_Unlock(){
	BCB_CAN_Data_Handler = BCB_CAN_Data_Handler2;
	Locked = 0;
}

uint8_t* BCB_GetSpeed(){
	return BCB_CAN_Data_Handler.Speed;
}

uint8_t* BCB_GetReady(){
	return BCB_CAN_Data_Handler.Ready;
}

uint8_t* BCB_GetFRG(){
	return BCB_CAN_Data_Handler.Frg;
}

uint8_t* BCB_GetTorque(){
	return BCB_CAN_Data_Handler.Torque;
}

uint8_t* BCB_GetCurrent(){
	return BCB_CAN_Data_Handler.Current;
}

uint8_t* BCB_GetBusDC(){
	return BCB_CAN_Data_Handler.BusDC;
}

void BCB_SpeedCommand(CAN_HandleTypeDef *hpcan, uint8_t d1, uint8_t d2){
//	hpcan->pTxMsg->Data[0] = SET_SPEED;
//	hpcan->pTxMsg->Data[1] = d2;
//	hpcan->pTxMsg->Data[2] = d1;
//	HAL_CAN_Transmit_IT(hpcan); //wysłanie ramki przez CANa
	BCB_Transmit(hpcan, SET_SPEED, d2, d1);
}
void BCB_TorqueCommand(CAN_HandleTypeDef *hpcan, uint8_t d1, uint8_t d2){
//	hpcan->pTxMsg->Data[0] = SET_TORQUE;
//	hpcan->pTxMsg->Data[1] = d2;
//	hpcan->pTxMsg->Data[2] = d1;
//	HAL_CAN_Transmit_IT(hpcan); //wysłanie ramki przez CANa
	BCB_Transmit(hpcan, SET_TORQUE, d2, d1);
}

void BCB_StopCommand(CAN_HandleTypeDef *hpcan){
//	hpcan->pTxMsg->Data[0] = SET_SPEED;
//	hpcan->pTxMsg->Data[1] = 0x00; //zerowa wartośc prędkości
//	hpcan->pTxMsg->Data[2] = 0x00;
//	HAL_CAN_Transmit_IT(hpcan); //wysłanie ramki przez CANa
	BCB_Transmit(hpcan, SET_SPEED, 0x00, 0x00);

}

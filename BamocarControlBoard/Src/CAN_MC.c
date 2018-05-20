#include "CAN_MC.h"

//includes
#include <string.h>
//#include "stm32f3xx_hal.h"


void CAN_MC_Transmit(CAN_HandleTypeDef *hpcan, uint8_t d1, uint8_t d2, uint8_t d3){
	hpcan->pTxMsg->Data[0] = d1;
	hpcan->pTxMsg->Data[1] = d2;
	hpcan->pTxMsg->Data[2] = d3;
	while(HAL_CAN_Transmit_IT(hpcan) != HAL_OK) //wysłanie ramki przez CANa
		;
}

void CAN_MC_ReceiveCallback(CAN_HandleTypeDef *hpcan){
	switch(hpcan->pRxMsg->Data[0]){
		case SPEED:
			if(Locked) memcpy(CAN_MC_CAN_Data_Handler2.Speed, hpcan->pRxMsg->Data, sizeof(hpcan->pRxMsg->Data));
			else memcpy(CAN_MC_CAN_Data_Handler.Speed, hpcan->pRxMsg->Data, sizeof(hpcan->pRxMsg->Data));
			break;
		case CURRENT:
			if(Locked) memcpy(CAN_MC_CAN_Data_Handler2.Current, hpcan->pRxMsg->Data, sizeof(hpcan->pRxMsg->Data));
			else memcpy(CAN_MC_CAN_Data_Handler.Current, hpcan->pRxMsg->Data, sizeof(hpcan->pRxMsg->Data));
			break;
		case STATUS:
			if(Locked) memcpy(CAN_MC_CAN_Data_Handler2.Status, hpcan->pRxMsg->Data, sizeof(hpcan->pRxMsg->Data));
			else memcpy(CAN_MC_CAN_Data_Handler.Status, hpcan->pRxMsg->Data, sizeof(hpcan->pRxMsg->Data));
			break;
		case TORQUE:
			if(Locked) memcpy(CAN_MC_CAN_Data_Handler2.Torque, hpcan->pRxMsg->Data, sizeof(hpcan->pRxMsg->Data));
			else memcpy(CAN_MC_CAN_Data_Handler.Torque, hpcan->pRxMsg->Data, sizeof(hpcan->pRxMsg->Data));
			break;
		case READY:
			if(Locked) memcpy(CAN_MC_CAN_Data_Handler2.Ready, hpcan->pRxMsg->Data, sizeof(hpcan->pRxMsg->Data));
			else memcpy(CAN_MC_CAN_Data_Handler.Ready, hpcan->pRxMsg->Data, sizeof(hpcan->pRxMsg->Data));
			break;
		case FRG:
			if(Locked) memcpy(CAN_MC_CAN_Data_Handler2.Frg, hpcan->pRxMsg->Data, sizeof(hpcan->pRxMsg->Data));
			else memcpy(CAN_MC_CAN_Data_Handler.Frg, hpcan->pRxMsg->Data, sizeof(hpcan->pRxMsg->Data));
			break;
		case BUS_DC:
			if(Locked) memcpy(CAN_MC_CAN_Data_Handler2.BusDC, hpcan->pRxMsg->Data, sizeof(hpcan->pRxMsg->Data));
			else memcpy(CAN_MC_CAN_Data_Handler.BusDC, hpcan->pRxMsg->Data, sizeof(hpcan->pRxMsg->Data));
			break;
		default:  //other data
			if(Locked) memcpy(CAN_MC_CAN_Data_Handler2.Others, hpcan->pRxMsg->Data, sizeof(hpcan->pRxMsg->Data));
			else memcpy(CAN_MC_CAN_Data_Handler.Others, hpcan->pRxMsg->Data, sizeof(hpcan->pRxMsg->Data));
			break;
	}
}

void CAN_MC_Init(CAN_HandleTypeDef *hpcan){
	// turn on CAN interrupts for queues 0 and 1
	__HAL_CAN_ENABLE_IT(hpcan, CAN_IT_FMP0);
	__HAL_CAN_ENABLE_IT(hpcan, CAN_IT_FMP1);

	//configuration of transmit frame
	TxMessage.DLC = CAN_DATA_LEN_TX;
	TxMessage.RTR = CAN_RTR_DATA;
	TxMessage.IDE = CAN_ID_STD; //standard ID version
	TxMessage.StdId = CAN_ID_TX;
	hpcan->pTxMsg = &TxMessage; //pass this structure to main structure of CAN handler

	//configuration of frame filter
	RxFilter.FilterNumber = 1;
	RxFilter.FilterMode = CAN_FILTERMODE_IDMASK; //set filtering mode to mask, not list
	RxFilter.FilterMaskIdHigh = 0xFFFF; //when mask is set to max, it doesn't matter
	RxFilter.FilterMaskIdLow = 0xFFFF;
	RxFilter.FilterIdHigh = CAN_ID_RX << 5; //CAN ID has only 11 bits, so it has to be moved by 5 bits
	RxFilter.FilterIdLow = 0x00; //to work fine, it has to be set to zero
	RxFilter.FilterActivation = ENABLE; //activation of filter
	if (HAL_CAN_ConfigFilter(hpcan, &RxFilter) != HAL_OK) //turn on filter and check whether it's fine
		HAL_GPIO_WritePin(LEDMain_GPIO_Port, LEDMain_Pin, GPIO_PIN_SET);

	//configuration od receive frame
	hpcan->pRxMsg = &RxMessage; //pass this structure to main structure of CAN handler
	hpcan->pRx1Msg = &RxMessage2; //for second queue
//	HAL_CAN_Receive_IT(hpcan, CAN_FIFO0);
}

void CAN_MC_Connect(CAN_HandleTypeDef *hpcan){
	uint8_t tmp[CAN_DATA_LEN_RX] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

	// is device ready?
	CAN_MC_Transmit(hpcan, READ, READY, REPLY_NOW);
	tmp[0] = READY;
	if(!memcmp(CAN_MC_GetReady() , tmp, CAN_DATA_LEN_RX))
		HAL_GPIO_WritePin(LEDMain_GPIO_Port, LEDMain_Pin, GPIO_PIN_SET);

	//is FRG set?
	CAN_MC_Transmit(hpcan, READ, FRG, REPLY_NOW);
	tmp[0] = FRG;
	if(!memcmp(CAN_MC_GetFRG(), tmp, CAN_DATA_LEN_RX))
		HAL_GPIO_WritePin(LEDMain_GPIO_Port, LEDMain_Pin, GPIO_PIN_SET);

	//enable drive
	CAN_MC_Transmit(hpcan, MODE, MOTOR_ENABLE, 0x00);
}

void CAN_MC_CyclicDataEnable(CAN_HandleTypeDef *hpcan){
	//send command to start cyclic data
	CAN_MC_Transmit(hpcan, READ, SPEED, DATA_FREQ);
	CAN_MC_Transmit(hpcan, READ, TORQUE, DATA_FREQ);
	CAN_MC_Transmit(hpcan, READ, BUS_DC, DATA_FREQ);
}

void CAN_MC_CyclicDataDisable(CAN_HandleTypeDef *hpcan){
	//send command to stop cyclic data
	CAN_MC_Transmit(hpcan, READ, SPEED, REPLY_STOP);
	CAN_MC_Transmit(hpcan, READ, TORQUE, REPLY_STOP);
	CAN_MC_Transmit(hpcan, READ, BUS_DC, REPLY_STOP);
}

void CAN_MC_Disconnect(CAN_HandleTypeDef *hpcan){
	//enable of drive
	CAN_MC_Transmit(hpcan, MODE, MOTOR_DISABLE, 0x00);
}

void CAN_MC_Lock(){
	Locked = 1;
}

void CAN_MC_Unlock(){
	CAN_MC_CAN_Data_Handler = CAN_MC_CAN_Data_Handler2;
	Locked = 0;
}

uint8_t* CAN_MC_GetSpeed(){
	return CAN_MC_CAN_Data_Handler.Speed;
}

uint8_t* CAN_MC_GetReady(){
	return CAN_MC_CAN_Data_Handler.Ready;
}

uint8_t* CAN_MC_GetFRG(){
	return CAN_MC_CAN_Data_Handler.Frg;
}

uint8_t* CAN_MC_GetTorque(){
	return CAN_MC_CAN_Data_Handler.Torque;
}

uint8_t* CAN_MC_GetCurrent(){
	return CAN_MC_CAN_Data_Handler.Current;
}

uint8_t* CAN_MC_GetBusDC(){
	return CAN_MC_CAN_Data_Handler.BusDC;
}

void CAN_MC_SpeedCommand(CAN_HandleTypeDef *hpcan, uint8_t d1, uint8_t d2){
	CAN_MC_Transmit(hpcan, SET_SPEED, d2, d1);
}

void CAN_MC_TorqueCommand(CAN_HandleTypeDef *hpcan, uint8_t d1, uint8_t d2){
	CAN_MC_Transmit(hpcan, SET_TORQUE, d2, d1);
}

void CAN_MC_StopCommand(CAN_HandleTypeDef *hpcan){
	CAN_MC_Transmit(hpcan, SET_SPEED, 0x00, 0x00);
}

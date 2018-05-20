#include "CAN_MC.h"

//includes
#include <string.h>


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
			CAN_MC_Data.Speed = ((uint16_t)(hpcan->pRxMsg->Data[1]) << 8) | hpcan->pRxMsg->Data[2];
			break;
		case CURRENT:
			CAN_MC_Data.Current = ((uint16_t)(hpcan->pRxMsg->Data[1]) << 8) | hpcan->pRxMsg->Data[2];
			break;
		case STATUS:{
			CAN_MC_Data.Status = hpcan->pRxMsg->Data[3];
			CAN_MC_Data.Status = (CAN_MC_Data.Status << 8) + hpcan->pRxMsg->Data[2];
			CAN_MC_Data.Status = (CAN_MC_Data.Status << 8) + hpcan->pRxMsg->Data[1];
			CAN_MC_Data.Status = (CAN_MC_Data.Status << 8) + hpcan->pRxMsg->Data[0];
			break;}
		case TORQUE:
			CAN_MC_Data.Torque = ((uint16_t)(hpcan->pRxMsg->Data[1]) << 8) | hpcan->pRxMsg->Data[2];
			break;
		case READY:
			CAN_MC_Data.Ready = ((uint16_t)(hpcan->pRxMsg->Data[1]) << 8) | hpcan->pRxMsg->Data[2];
			break;
		case FRG:
			CAN_MC_Data.Frg = ((uint16_t)(hpcan->pRxMsg->Data[1]) << 8) | hpcan->pRxMsg->Data[2];
			break;
		case BUS_DC:
			CAN_MC_Data.BusDC = ((uint16_t)(hpcan->pRxMsg->Data[1]) << 8) | hpcan->pRxMsg->Data[2];
			break;
		default:{  //other data
			CAN_MC_Data.Others = hpcan->pRxMsg->Data[3];
			CAN_MC_Data.Others = (CAN_MC_Data.Others << 8) + hpcan->pRxMsg->Data[2];
			CAN_MC_Data.Others = (CAN_MC_Data.Others << 8) + hpcan->pRxMsg->Data[1];
			CAN_MC_Data.Others = (CAN_MC_Data.Others << 8) + hpcan->pRxMsg->Data[0];
			break;}
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
	RxFilter.FilterMode = CAN_FILTERSCALE_16BIT; //16 bits mask mode
	RxFilter.FilterMaskIdHigh = 0xFFFF; //when mask is set to max, it doesn't matter
	RxFilter.FilterMaskIdLow = 0xFFFF;
	RxFilter.FilterIdHigh = CAN_ID_RX << 5; //CAN ID has only 11 bits, so it has to be moved by 5 bits
	RxFilter.FilterIdLow = 0x00; //to work fine, it has to be set to zero
	RxFilter.FilterFIFOAssignment = CAN_FIFO0;
	RxFilter.FilterActivation = ENABLE; //activation of filter
	if (HAL_CAN_ConfigFilter(hpcan, &RxFilter) != HAL_OK) //turn on filter and check whether it's fine
		SET_BIT(CAN_MC_Status, 1<<CAN_FILTER_ERROR);

	//configuration od receive frame
	hpcan->pRxMsg = &RxMessage; //pass this structure to main structure of CAN handler
	hpcan->pRx1Msg = &RxMessage2; //for second queue
	if (HAL_CAN_Receive_IT(hpcan, CAN_FIFO0) != HAL_OK)
		SET_BIT(CAN_MC_Status, 1<<CAN_RX_ERROR);
}

void CAN_MC_Connect(CAN_HandleTypeDef *hpcan){
	// is device ready?
	CAN_MC_Transmit(hpcan, READ, READY, REPLY_NOW);
	if(hpcan->pRxMsg->Data[1] != 0x01 || hpcan->pRxMsg->Data[2] != 0x00 || hpcan->pRxMsg->Data[3] != 0x00)
		SET_BIT(CAN_MC_Status, 1<<MC_READY);

	//is FRG set?
	CAN_MC_Transmit(hpcan, READ, FRG, REPLY_NOW);
	if(hpcan->pRxMsg->Data[1] != 0x01 || hpcan->pRxMsg->Data[2] != 0x00 || hpcan->pRxMsg->Data[3] != 0x00)
		SET_BIT(CAN_MC_Status, 1<<MC_FRG);

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
	CAN_MC_DataLocked = CAN_MC_Data;
	SET_BIT(CAN_MC_Status, 1<<LOCKED);
}

void CAN_MC_Unlock(){
	CLEAR_BIT(CAN_MC_Status, 1<<LOCKED);
}

uint16_t CAN_MC_GetSpeed(){
	return CAN_MC_Data.Speed;
}

uint16_t CAN_MC_GetReady(){
	return CAN_MC_Data.Ready;
}

uint16_t CAN_MC_GetFRG(){
	return CAN_MC_Data.Frg;
}

uint16_t CAN_MC_GetTorque(){
	return CAN_MC_Data.Torque;
}

uint16_t CAN_MC_GetCurrent(){
	return CAN_MC_Data.Current;
}

uint16_t CAN_MC_GetBusDC(){
	return CAN_MC_Data.BusDC;
}

void CAN_MC_SpeedCommand(CAN_HandleTypeDef *hpcan, uint16_t data){
	CAN_MC_Transmit(hpcan, SET_SPEED, data % 256, data >> 8 % 256);
}

void CAN_MC_TorqueCommand(CAN_HandleTypeDef *hpcan, uint16_t data){
	CAN_MC_Transmit(hpcan, SET_TORQUE, data % 256, data >> 8 % 256);
}

void CAN_MC_StopCommand(CAN_HandleTypeDef *hpcan){
	CAN_MC_Transmit(hpcan, SET_SPEED, 0x00, 0x00);
}

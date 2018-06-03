#include "CAN_MC.h"


void CAN_MC_Transmit(uint8_t d1, uint8_t d2, uint8_t d3){
	CanTxMsgTypeDef Frame = *hcan.pTxMsg;
	Frame.Data[0] = d1;
	Frame.Data[1] = d2;
	Frame.Data[2] = d3;
	fifo_push(&TxBuffer, &Frame);
}

void CAN_MC_ReceiveCallback(void){
	switch(hcan.pRxMsg->Data[0]){
		case SPEED:
			CAN_MC_Data.Speed = ((uint16_t)(hcan.pRxMsg->Data[1]) << 8) | hcan.pRxMsg->Data[2];
			break;
		case CURRENT:
			CAN_MC_Data.Current = ((uint16_t)(hcan.pRxMsg->Data[1]) << 8) | hcan.pRxMsg->Data[2];
			break;
		case STATUS:{
			CAN_MC_Data.Status = hcan.pRxMsg->Data[3];
			CAN_MC_Data.Status = (CAN_MC_Data.Status << 8) + hcan.pRxMsg->Data[2];
			CAN_MC_Data.Status = (CAN_MC_Data.Status << 8) + hcan.pRxMsg->Data[1];
			CAN_MC_Data.Status = (CAN_MC_Data.Status << 8) + hcan.pRxMsg->Data[0];
			break;}
		case TORQUE:
			CAN_MC_Data.Torque = ((int16_t)(hcan.pRxMsg->Data[1]) << 8) | hcan.pRxMsg->Data[2];
			break;
		case READY:
			CAN_MC_Data.Ready = ((uint16_t)(hcan.pRxMsg->Data[1]) << 8) | hcan.pRxMsg->Data[2];
			break;
		case FRG:
			CAN_MC_Data.Frg = ((uint16_t)(hcan.pRxMsg->Data[1]) << 8) | hcan.pRxMsg->Data[2];
			break;
		case BUS_DC:
			CAN_MC_Data.BusDC = ((uint16_t)(hcan.pRxMsg->Data[1]) << 8) | hcan.pRxMsg->Data[2];
			break;
		default:{  //other data
			CAN_MC_Data.Others = hcan.pRxMsg->Data[3];
			CAN_MC_Data.Others = (CAN_MC_Data.Others << 8) + hcan.pRxMsg->Data[2];
			CAN_MC_Data.Others = (CAN_MC_Data.Others << 8) + hcan.pRxMsg->Data[1];
			CAN_MC_Data.Others = (CAN_MC_Data.Others << 8) + hcan.pRxMsg->Data[0];
			break;}
	}
}

void CAN_MC_TimerCallback(void){
	if(!fifo_empty(&TxBuffer) && !READ_BIT(CAN_MC_Status, 1<<CAN_TX_ERROR)){
		fifo_pop(&TxBuffer, hcan.pTxMsg);
		if(HAL_CAN_Transmit_IT(&hcan) != HAL_OK)
			SET_BIT(CAN_MC_Status, 1<<CAN_TX_ERROR);
	}
}

void CAN_MC_Init(void){
	// initialize buffer for transmit frames
	fifo_init(&TxBuffer);

	//configuration of transmit frame
	TxMessage.DLC = CAN_DATA_LEN_TX;
	TxMessage.RTR = CAN_RTR_DATA;
	TxMessage.IDE = CAN_ID_STD; //standard ID version
	TxMessage.StdId = CAN_ID_TX;
	hcan.pTxMsg = &TxMessage; //pass this structure to main structure of CAN handler

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
	if (HAL_CAN_ConfigFilter(&hcan, &RxFilter) != HAL_OK) //turn on filter and check whether it's fine
		SET_BIT(CAN_MC_Status, 1<<CAN_FILTER_ERROR);

	//configuration od receive frame
	hcan.pRxMsg = &RxMessage; //pass this structure to main structure of CAN handler
	hcan.pRx1Msg = &RxMessage2; //for second queue
	if (HAL_CAN_Receive_IT(&hcan, CAN_FIFO0) != HAL_OK)
		SET_BIT(CAN_MC_Status, 1<<CAN_RX_ERROR);
}

void CAN_MC_Connect(void){
	// is device ready?
	CAN_MC_Transmit(READ, READY, REPLY_NOW);
	if(hcan.pRxMsg->Data[1] != 0x01 || hcan.pRxMsg->Data[2] != 0x00 || hcan.pRxMsg->Data[3] != 0x00)
		SET_BIT(CAN_MC_Status, 1<<MC_READY);

	//is FRG set?
	CAN_MC_Transmit(READ, FRG, REPLY_NOW);
	if(hcan.pRxMsg->Data[1] != 0x01 || hcan.pRxMsg->Data[2] != 0x00 || hcan.pRxMsg->Data[3] != 0x00)
		SET_BIT(CAN_MC_Status, 1<<MC_FRG);

	//enable drive
	CAN_MC_Transmit(MODE, MOTOR_ENABLE, 0x00);
}

void CAN_MC_CyclicDataEnable(void){
	//send command to start cyclic data
	CAN_MC_Transmit(READ, SPEED, DATA_FREQ);
	CAN_MC_Transmit(READ, TORQUE, DATA_FREQ);
	CAN_MC_Transmit(READ, BUS_DC, DATA_FREQ);
}

void CAN_MC_CyclicDataDisable(void){
	//send command to stop cyclic data
	CAN_MC_Transmit(READ, SPEED, REPLY_STOP);
	CAN_MC_Transmit(READ, TORQUE, REPLY_STOP);
	CAN_MC_Transmit(READ, BUS_DC, REPLY_STOP);
}

void CAN_MC_Disconnect(void){
	//disnable of drive
	CAN_MC_Transmit(MODE, MOTOR_DISABLE, 0x00);
}

void CAN_MC_Lock(){
	CAN_MC_DataLocked = CAN_MC_Data;
	SET_BIT(CAN_MC_Status, 1<<LOCKED);
}

void CAN_MC_Unlock(){
	CLEAR_BIT(CAN_MC_Status, 1<<LOCKED);
}

void CAN_MC_SendStatus(uint32_t ErrorCode){
	CanTxMsgTypeDef Frame = *hcan.pTxMsg;
	uint32_t hal_err = HAL_CAN_GetError(&hcan);
	Frame.DLC = 8;
	Frame.StdId = CAN_ID_TX_STATUS;

	//errors from HAL_CAN driver
	Frame.Data[0] = hal_err >> 24 % 256;
	Frame.Data[1] = hal_err >> 16 % 256;
	Frame.Data[2] = hal_err >> 8 % 256;
	Frame.Data[3] = hal_err % 256;

	//status of CAN_MC library
	Frame.Data[4] = CAN_MC_Status;

	//value of ErrorCode
	Frame.Data[5] = ErrorCode % 256;
	Frame.Data[6] = ErrorCode >> 8 % 256;
	Frame.Data[7] = ErrorCode >> 16 % 256;

	fifo_push(&TxBuffer, &Frame);
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

int16_t CAN_MC_GetTorque(){
	return CAN_MC_Data.Torque;
}

uint16_t CAN_MC_GetCurrent(){
	return CAN_MC_Data.Current;
}

uint16_t CAN_MC_GetBusDC(){
	return CAN_MC_Data.BusDC;
}

void CAN_MC_SpeedCommand(uint16_t data){
	CAN_MC_Transmit(SET_SPEED, data % 256, data >> 8 % 256);
}

void CAN_MC_TorqueCommand(uint16_t data){
	CAN_MC_Transmit(SET_TORQUE, data % 256, data >> 8 % 256);
}

void CAN_MC_StopCommand(void){
	CAN_MC_Transmit(SET_SPEED, 0x00, 0x00);
}

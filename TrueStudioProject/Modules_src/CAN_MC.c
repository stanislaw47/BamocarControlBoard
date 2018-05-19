#include <CAN_MC.h>
#include <string.h>
#include "CAN_MC.h"


void BCB_Transmit(CAN_HandleTypeDef *hpcan, uint8_t d1, uint8_t d2, uint8_t d3){
	hpcan->pTxMsg->Data[0] = d1;
	hpcan->pTxMsg->Data[1] = d2;
	hpcan->pTxMsg->Data[2] = d3;
	while(HAL_CAN_Transmit_IT(hpcan) != HAL_OK) //wysłanie ramki przez CANa
		;
}



void CAN_MC_Init(void){

	/*
	 * CAN_MC_TxBuffer initialisation
	 */
	uint8_t index;
	for(index=0;index<RxBufferLength;index++)
	{
		CAN_MC_TxBuffer.Buffer[index].DLC=CAN_DATA_LEN_TX;
		CAN_MC_TxBuffer.Buffer[index].StdId=CAN_ID_TX;
		CAN_MC_TxBuffer.Buffer[index].IDE=CAN_ID_STD;
	}

	CAN_MC_TxBuffer.Buffer[TX_CURRENT_LIMIT].Data[0]=REG_CUR_LIM;

	CAN_MC_TxBuffer.Buffer[TX_TORQUE].Data[0]=REG_TORQUE;

	CAN_MC_TxBuffer.Buffer[TX_VDC].Data[0]=REG_READ;
	CAN_MC_TxBuffer.Buffer[TX_VDC].Data[1]=REG_BUS_DC;
	CAN_MC_TxBuffer.Buffer[TX_VDC].Data[2]=DATA_FREQ;

	/*
	 * Filters and Rx struct initialisation
	 */
	RxFilter.FilterNumber = 0;
	RxFilter.FilterMode = CAN_FILTERMODE_IDMASK;
	RxFilter.FilterMaskIdHigh = 0xFFFF;
	RxFilter.FilterMaskIdLow = 0xFFFF;
	RxFilter.FilterIdHigh = CAN_ID_RX << 5;
	RxFilter.FilterIdLow = 0x00;
	RxFilter.FilterFIFOAssignment = CAN_FIFO0;
	RxFilter.FilterActivation = ENABLE;
	RxFilter.FilterMode=CAN_FILTERSCALE_16BIT;
	if (HAL_CAN_ConfigFilter(&hcan, &RxFilter) != HAL_OK)
		SET_BIT(CAN_MC_Status,CAN_MC_FILT_ERROR);

	/*
	 * Rx structures address assignment
	 */
	hcan.pRxMsg = &RxMessage1;
	hcan.pRx1Msg = &RxMessage2;
	if (HAL_CAN_Receive_IT(&hcan,CAN_FIFO0) != HAL_OK)
		SET_BIT(CAN_MC_Status,CAN_MC_RX_ERROR);
}
void CAN_MC_Lock()
{
	if(CAN_MC_Status)
		SET_BIT(CAN_MC_Status,CAN_MC_OVERRUN);
	else
		CAN_MC_Locked = 1;
}
void CAN_MC_Unlock()
{
	uint8_t index=0;
	for(index=0;index<RxBufferLength;index++)
		if(READ_BIT(CAN_MC_InDataLocked.Status,1<<index))
			CAN_MC_InData.Data[index]=CAN_MC_InDataLocked.Data[index];
	CAN_MC_Locked = 0;
}



uint16_t BCB_GetBusDC()
{
	return CAN_MC_InData.Data[RX_VDC];
}



void CAN_MC_CyclicDataEnable(void)
{
	SET_BIT(CAN_MC_TxBuffer.Status,1<<TX_VDC);
}
void CAN_MC_TorqueCommand(uint16_t DataToSend)
{
	CAN_MC_TxBuffer.Buffer[TX_TORQUE].Data[1] = DataToSend % 256;
	CAN_MC_TxBuffer.Buffer[TX_TORQUE].Data[2] = DataToSend >> 8 % 256;
	SET_BIT(CAN_MC_TxBuffer.Status,1<<TX_TORQUE);
}
void CAN_MC_CurrentLimitCommand(uint16_t DataToSend)
{
	CAN_MC_TxBuffer.Buffer[TX_CURRENT_LIMIT].Data[1] = DataToSend % 256;
	CAN_MC_TxBuffer.Buffer[TX_CURRENT_LIMIT].Data[2] = DataToSend >> 8 % 256;
	SET_BIT(CAN_MC_TxBuffer.Status,1<<TX_CURRENT_LIMIT);
}



void CAN_MC_TransmitCallback(void)
{
	uint8_t index=0;
	for(index=0;index<RxBufferLength;index++)
	if(READ_BIT(CAN_MC_TxBuffer.Status,1<<index))
	{
		hcan.pTxMsg=&(CAN_MC_TxBuffer.Buffer[index]);
		if(HAL_CAN_Transmit_IT(&hcan) != HAL_OK)
			return;
		else
			CLEAR_BIT(CAN_MC_TxBuffer.Status,1<<index);
	}
}
void CAN_MC_ReceiveCallback(void)
{
	switch(hcan.pRxMsg->Data[0])
	{
		case REG_BUS_DC:
			if(CAN_MC_Locked)
			{
				CAN_MC_InDataLocked.Data[RX_VDC] = hcan.pRxMsg->Data[1];
				CAN_MC_InDataLocked.Data[RX_VDC] |= hcan.pRxMsg->Data[1] << 8;
				SET_BIT(CAN_MC_InDataLocked.Status,RX_VDC);
			}
			else
			{
				CAN_MC_InData.Data[RX_VDC] = hcan.pRxMsg->Data[1];
				CAN_MC_InData.Data[RX_VDC] |= hcan.pRxMsg->Data[1] << 8;
			}
			break;
	}
	if (HAL_CAN_Receive_IT(&hcan,CAN_FIFO0) != HAL_OK)
		SET_BIT(CAN_MC_Status,CAN_MC_RX_ERROR);
}

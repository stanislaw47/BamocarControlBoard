#ifndef BCB_
#define BCB_

//includes
#include <string.h>
#include "stm32f3xx_hal.h"

//defines
#define CAN_DATA_LEN_TX 3 //ilo�c bajt�w danych
#define CAN_DATA_LEN_RX 6 //ilo�c bajt�w danych odbieranych ze sterownika, zosta�a ustawiona poprzez NDrive
#define CAN_ID_TX 0x201 //ID ramki wysy�anej do sterownika, wykorzystywane w filtrach
#define CAN_ID_RX 0x181 //ID ramki odebranej ze sterownika, wykorzystywane w filtrach
#define DATA_FREQ 0x32 //cz�stotliwosc z jak� Bamcoar b�dzie zwraca� ramki danych


//static uint8_t DataCAN[CAN_DATA_LEN_RX]; //dane odebrane z magistrali CAN
CanTxMsgTypeDef Tx; //struktura przechwouj�ca ramk� do wys�ania
CanRxMsgTypeDef Rx; //struktura przechwouj�ca ramk� do odebrania
CanRxMsgTypeDef Rx2; //do drugiej kolejki
CAN_FilterConfTypeDef Rx_Filter; //struktura do konfiguracji filtra

struct BCB_CAN_Data{
	uint8_t Status[CAN_DATA_LEN_RX];
	uint8_t Speed[CAN_DATA_LEN_RX];
	uint8_t Current[CAN_DATA_LEN_RX];
//	uint8_t Torque[CAN_DATA_LEN_RX];
	uint8_t Others[CAN_DATA_LEN_RX];
}BCB_CAN_Data_Handler, BCB_CAN_Data_Handler2;

void BCB_Init(CAN_HandleTypeDef *hpcan);
void BCB_Connect(CAN_HandleTypeDef *hpcan);
void BCB_Transmit(CanTxMsgTypeDef* pTx, CAN_HandleTypeDef *hpcan, uint8_t* Data);
uint8_t* GetSpeed();

#endif //BCB_

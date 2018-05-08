#ifndef BCB_
#define BCB_

//includes
#include <string.h>
#include "stm32f3xx_hal.h"

//defines
#define CAN_DATA_LEN_TX 3 //iloœc bajtów danych
#define CAN_DATA_LEN_RX 6 //iloœc bajtów danych odbieranych ze sterownika, zosta³a ustawiona poprzez NDrive
#define CAN_ID_TX 0x201 //ID ramki wysy³anej do sterownika, wykorzystywane w filtrach
#define CAN_ID_RX 0x181 //ID ramki odebranej ze sterownika, wykorzystywane w filtrach
#define DATA_FREQ 0x32 //czêstotliwosc z jak¹ Bamcoar bêdzie zwraca³ ramki danych


//static uint8_t DataCAN[CAN_DATA_LEN_RX]; //dane odebrane z magistrali CAN
CanTxMsgTypeDef Tx; //struktura przechwouj¹ca ramkê do wys³ania
CanRxMsgTypeDef Rx; //struktura przechwouj¹ca ramkê do odebrania
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

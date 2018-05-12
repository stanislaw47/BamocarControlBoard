//This library is used to provide low-level control of Bamocar Motor Controller
//Developed by AGH Racing Electric Team

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
#define DATA_FREQ 0x32 //cz�stotliwosc z jak� Bamcoar b�dzie zwraca� ramki danych [50ms]
#define READ 0x3d //odczytywanie warto�ci rejestru
#define REPLY_NOW 0x00 //rozkaz natychmiastowej odpowiedzi
#define SPEED 0x30 // rejestr do odczytu pr�dko�ci
#define SET_SPEED //rejestr do ustawiania pr�dko�ci zadanej
#define CURRENT 0x20 //rejestr do odczytu pr�du
#define TORQUE 0xa8 //rejestr do odczytu momentu obrotowego
#define STATUS 0x40 //rejestr do odczytu statusu
#define READY 0xe2 //rejestr do odczytu czy urz�dzenie jest gotowe
#define FRG 0xe8 //rejestr do ustawienia warto�ci FRG
#define MODE 0x51 //rejestr do odczytu trybu i w��czania/wy��czania sterownika


CanTxMsgTypeDef TxMessage; //struktura przechwouj�ca ramk� do wys�ania
CanRxMsgTypeDef RxMessage; //struktura przechwouj�ca ramk� do odebrania
CanRxMsgTypeDef RxMessage2; //do drugiej kolejki
CAN_FilterConfTypeDef RxFilter; //struktura do konfiguracji filtra

struct BCB_CAN_Data{
	uint8_t Status[CAN_DATA_LEN_RX];
	uint8_t Speed[CAN_DATA_LEN_RX];
	uint8_t Current[CAN_DATA_LEN_RX];
	uint8_t Torque[CAN_DATA_LEN_RX];
	uint8_t Ready[CAN_DATA_LEN_RX];
	uint8_t Frg[CAN_DATA_LEN_RX];
	uint8_t Others[CAN_DATA_LEN_RX];
}BCB_CAN_Data_Handler, BCB_CAN_Data_Handler2;

void BCB_Init(CAN_HandleTypeDef *hpcan);
void BCB_Connect(CAN_HandleTypeDef *hpcan);
void BCB_Disconnect(CAN_HandleTypeDef *hpcan);
void BCB_Transmit(CAN_HandleTypeDef *hpcan, uint8_t* Data);
uint8_t* BCB_GetSpeed();
uint8_t* BCB_GetReady();
uint8_t* BCB_GetFRG();
void BCB_StopMotor();

#endif //BCB_

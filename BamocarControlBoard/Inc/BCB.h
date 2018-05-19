//This library is used to provide low-level control of Bamocar Motor Controller
//Developed by AGH Racing Electric Team

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
#define DATA_FREQ 0x32 //czêstotliwosc z jak¹ Bamocar bêdzie zwraca³ ramki danych [50ms]
#define READ 0x3d //odczytywanie wartoœci rejestru
#define REPLY_NOW 0x00 //rozkaz natychmiastowej odpowiedzi
#define REPLY_STOP 0xff //rozkaz zakoñczenia wysy³ania cyklicznego
#define SPEED 0x30 // rejestr do odczytu prêdkoœci
#define SET_SPEED 0x31//rejestr do ustawiania prêdkoœci zadanej
#define CURRENT 0x20 //rejestr do odczytu pr¹du
#define TORQUE 0xa8 //rejestr do odczytu momentu obrotowego
#define SET_TORQUE 0x90 //rejestr do ustawienia wartoœci momentu obrotowego
#define STATUS 0x40 //rejestr do odczytu statusu
#define READY 0xe2 //rejestr do odczytu czy urz¹dzenie jest gotowe
#define FRG 0xe8 //rejestr do ustawienia wartoœci FRG
#define BUS_DC 0xeb //rejestr do odczytu napiêcia magistrali
#define MODE 0x51 //rejestr do odczytu trybu i w³¹czania/wy³¹czania sterownika
#define MOTOR_ENABLE 0x00 //w³¹czenie sterownika
#define MOTOR_DISABLE 0x04 //wy³¹czenie sterownika


CanTxMsgTypeDef TxMessage; //struktura przechwouj¹ca ramkê do wys³ania
CanRxMsgTypeDef RxMessage; //struktura przechwouj¹ca ramkê do odebrania
CanRxMsgTypeDef RxMessage2; //do drugiej kolejki
CAN_FilterConfTypeDef RxFilter; //struktura do konfiguracji filtra

struct BCB_CAN_Data{
	uint8_t Status[CAN_DATA_LEN_RX];
	uint8_t Speed[CAN_DATA_LEN_RX];
	uint8_t Current[CAN_DATA_LEN_RX];
	uint8_t Torque[CAN_DATA_LEN_RX];
	uint8_t Ready[CAN_DATA_LEN_RX];
	uint8_t Frg[CAN_DATA_LEN_RX];
	uint8_t BusDC[CAN_DATA_LEN_RX];
	uint8_t Others[CAN_DATA_LEN_RX];
}BCB_CAN_Data_Handler, BCB_CAN_Data_Handler2; //struktury do przechowywania danych ze sterownika
static uint8_t Locked = 0; //flaga do zapewnienia spójnoœci odczytywanych danych

void BCB_Init(CAN_HandleTypeDef *hpcan); //inicjalizuje ramki i filtry
void BCB_Connect(CAN_HandleTypeDef *hpcan); //sprawdza stan sterownika, FRG i go w³¹cza
void BCB_Disconnect(CAN_HandleTypeDef *hpcan); //wy³¹cza sterownik
void BCB_Transmit(CAN_HandleTypeDef *hpcan, uint8_t d1, uint8_t d2, uint8_t d3); //dba o pewnoœc wys³ania ramki
void BCB_ReceiveCallback(CAN_HandleTypeDef *hpcan); //callback od odebrania ramki
void BCB_CyclicDataEnable(CAN_HandleTypeDef *hpcan); //w³¹cza wysy³anie danych cyklicznie ze sterownika
void BCB_CyclicDataDisable(CAN_HandleTypeDef *hpcan);//wy³¹cza wysy³anie danych cyklicznie ze sterownika
void BCB_Lock(); //zapewnia spójnoœc danych do odczytu
void BCB_Unlock(); //funkcja komplementarna do Lock, koñczy procedurê odczytu
uint8_t* BCB_GetSpeed(); //odczyt prêdkoœci
uint8_t* BCB_GetTorque(); //odczyt momentu
uint8_t* BCB_Current(); //odczyt pr¹du
uint8_t* BCB_GetReady(); //odczyt gotowoœci
uint8_t* BCB_GetFRG(); //odczyt FRG
uint8_t* BCB_GetBusDC(); //odczyt napiêcia na magistrali
void BCB_SpeedCommand(CAN_HandleTypeDef *hpcan, uint8_t d1, uint8_t d2); //ustawienie prêdkoœci
void BCB_TorqueCommand(CAN_HandleTypeDef *hpcan, uint8_t d1, uint8_t d2); //ustawienie momentu
void BCB_StopCommand(CAN_HandleTypeDef *hpcan); //zatrzymanie silnika

#endif //BCB_

//This library is used to provide low-level control of Bamocar Motor Controller
//Developed by AGH Racing Electric Team

#ifndef CAN_MC_
#define CAN_MC_

//includes
#include <string.h>
#include "stm32f3xx_hal.h"

//defines
#define CAN_DATA_LEN_TX 	3 		//number of bytes send to Bamocar
#define CAN_DATA_LEN_RX 	6 		//number fo bytes received from Bamcoar, fixed via NDrive
#define CAN_ID_TX 			0x201 	//send frame ID, used in filters
#define CAN_ID_RX 			0x181 	//received frame ID, used in filters
#define DATA_FREQ 			0x32 	//cyclic data frequency, in miliseconds [50]
#define READ 				0x3d 	//value for reading registers
#define REPLY_NOW 			0x00 	//value for immediately reply
#define REPLY_STOP 			0xff 	//value for stop sending cyclic data
#define SPEED 				0x30 	//value of register to read speed
#define SET_SPEED 			0x31	//value of register to write speed
#define CURRENT 			0x20 	//value of register to read speed
#define TORQUE 				0xa8 	//value of register to read speed
#define SET_TORQUE 			0x90 	//value of register to write torque
#define STATUS 				0x40 	//value of register to read status
#define READY 				0xe2 	//value of register to read whether device is ready
#define FRG 				0xe8 	//value of register to set FRG
#define BUS_DC 				0xeb 	//value of register to read bus voltage
#define MODE 				0x51 	//value of register to read status and switch on/off
#define MOTOR_ENABLE 		0x00 	//value for turning on
#define MOTOR_DISABLE 		0x04 	//value for turning off


CanTxMsgTypeDef TxMessage; //structure for trasmitted frame
CanRxMsgTypeDef RxMessage; //structure for received fram
CanRxMsgTypeDef RxMessage2; //for second queue
CAN_FilterConfTypeDef RxFilter; //structure for filter

struct CAN_MC_CAN_Data{
	uint8_t Status[CAN_DATA_LEN_RX];
	uint8_t Speed[CAN_DATA_LEN_RX];
	uint8_t Current[CAN_DATA_LEN_RX];
	uint8_t Torque[CAN_DATA_LEN_RX];
	uint8_t Ready[CAN_DATA_LEN_RX];
	uint8_t Frg[CAN_DATA_LEN_RX];
	uint8_t BusDC[CAN_DATA_LEN_RX];
	uint8_t Others[CAN_DATA_LEN_RX];
}CAN_MC_CAN_Data_Handler, CAN_MC_CAN_Data_Handler2; //structure for data from Bamocar
static uint8_t Locked = 0; //flag for data reading consistency

void CAN_MC_Init(CAN_HandleTypeDef *hpcan); //initialization fo frames and filters
void CAN_MC_Connect(CAN_HandleTypeDef *hpcan); //checks whether device is ready and FRG set
void CAN_MC_Disconnect(CAN_HandleTypeDef *hpcan); //turns drive off
void CAN_MC_Transmit(CAN_HandleTypeDef *hpcan, uint8_t d1, uint8_t d2, uint8_t d3); //main sending function
void CAN_MC_ReceiveCallback(CAN_HandleTypeDef *hpcan); //frame receive callback
void CAN_MC_CyclicDataEnable(CAN_HandleTypeDef *hpcan); //turns on cyclic data sending by Bamocar
void CAN_MC_CyclicDataDisable(CAN_HandleTypeDef *hpcan);//turns off cyclic data sending by Bamcoar
void CAN_MC_Lock(); //handles Locked flag, starts reading data
void CAN_MC_Unlock(); //handles Locked flag, finishes reading data
uint8_t* CAN_MC_GetSpeed(); //read value of speed
uint8_t* CAN_MC_GetTorque(); //read value of torque
uint8_t* CAN_MC_Current(); //read value of current
uint8_t* CAN_MC_GetReady(); //check whether device is ready
uint8_t* CAN_MC_GetFRG(); //read value of FRG
uint8_t* CAN_MC_GetBusDC(); //read value of bus voltage
void CAN_MC_SpeedCommand(CAN_HandleTypeDef *hpcan, uint8_t d1, uint8_t d2); //set speed
void CAN_MC_TorqueCommand(CAN_HandleTypeDef *hpcan, uint8_t d1, uint8_t d2); //set torque
void CAN_MC_StopCommand(CAN_HandleTypeDef *hpcan); //stop motor

#endif //CAN_MC_

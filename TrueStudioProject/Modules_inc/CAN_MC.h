//This library is used to provide low-level control of Bamocar Motor Controller
//Developed by AGH Racing Electric Team

#ifndef CAN_MC_
#define CAN_MC_

//includes
#include <string.h>
#include "can.h"
#include "FIFO.h"

//defines
// CAN configuration parameters
#define CAN_DATA_LEN_TX 	3 		//number of bytes send to Bamocar
#define CAN_DATA_LEN_RX 	6 		//number fo bytes received from Bamcoar, fixed via NDrive
#define CAN_ID_TX 			0x201 	//send frame ID, used in filters
#define CAN_ID_RX 			0x181 	//received frame ID, used in filters

//registers configuration parameters
#define DATA_FREQ 			0x32 	//cyclic data frequency, in miliseconds [50]
#define READ 				0x3d 	//value for reading registers
#define REPLY_NOW 			0x00 	//value for immediately reply
#define REPLY_STOP 			0xff 	//value for stop sending cyclic data

//error status defines
#define CAN_FILTER_ERROR	1		//bit number in CAN_MC_Status which indicate filter initialization error
#define CAN_RX_ERROR		2		//bit number in CAN_MC_Status which indicate frame receive error
#define CAN_TX_ERROR		3		//bit number in CAN_MC_Status which indicate frame transmit error
#define MC_READY			4		//bit number in CAN_MC_Status which indicate that device is not ready error
#define MC_FRG				5		//bit number in CAN_MC_Status which indicate is FRG set error
#define LOCKED				6		//bit number in CAN_MC_Status which indicate whther data are locked or not

//data configuration registers
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
fifo TxBuffer; //buffer for send frames

static struct __CAN_MC_Data{
	uint32_t Status;
	uint16_t Speed;
	uint16_t Current;
	int16_t Torque;
	uint16_t Ready;
	uint16_t Frg;
	uint16_t BusDC;
	uint32_t Others;
}CAN_MC_Data, CAN_MC_DataLocked; //structure for data from Bamocar

static uint8_t CAN_MC_Status; //variable to report status of this library functions

void CAN_MC_Init(void); //initialization fo frames and filters
void CAN_MC_Connect(void); //checks whether device is ready and FRG set
void CAN_MC_Disconnect(void); //turns drive off
void CAN_MC_Transmit(uint8_t d1, uint8_t d2, uint8_t d3); //main sending function
void CAN_MC_ReceiveCallback(void); //frame receive callback
void CAN_MC_TimerCAllback(void); //timer period elapsed callback, used to send frames. Suitable frequency should be 1 kHz.
void CAN_MC_CyclicDataEnable(void); //turns on cyclic data sending by Bamocar
void CAN_MC_CyclicDataDisable(void);//turns off cyclic data sending by Bamcoar
void CAN_MC_Lock(); //handles Locked flag, starts reading data
void CAN_MC_Unlock(); //handles Locked flag, finishes reading data
uint16_t CAN_MC_GetSpeed(); //read value of speed
int16_t CAN_MC_GetTorque(); //read value of torque
uint16_t CAN_MC_GetCurrent(); //read value of current
uint16_t CAN_MC_GetReady(); //check whether device is ready
uint16_t CAN_MC_GetFRG(); //read value of FRG
uint16_t CAN_MC_GetBusDC(); //read value of bus voltage
void CAN_MC_SpeedCommand(uint16_t data); //set speed
void CAN_MC_TorqueCommand(uint16_t data); //set torque
void CAN_MC_CurrentLimitCommand(uint16_t data); //set current limit
void CAN_MC_StopCommand(void); //stop motor

#endif //CAN_MC_

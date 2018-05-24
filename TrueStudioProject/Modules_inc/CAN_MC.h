//This library is used to provide low-level control of Bamocar Motor Controller
//Developed by AGH Racing Electric Team

#ifndef CAN_MC_
#define CAN_MC_

#include <string.h>
#include "can.h"

/*
 * Interface defines
 */
#define CAN_DATA_LEN_TX 	3 		//iloœc bajtów danych
#define CAN_DATA_LEN_RX 	6 		//iloœc bajtów danych odbieranych ze sterownika, zosta³a ustawiona poprzez NDrive
#define CAN_ID_TX 			0x201 	//ID ramki wysy³anej do sterownika, wykorzystywane w filtrach
#define CAN_ID_RX 			0x181 	//ID ramki odebranej ze sterownika, wykorzystywane w filtrach
#define DATA_FREQ 			0x32 	//czêstotliwosc z jak¹ Bamocar bêdzie zwraca³ ramki danych [50ms]
#define TxBufferLength 		0x08	//number of Tx struct frames
#define RxBufferLength		0x01

/*
 * Bamocar register defines
 */
#define REG_READ 				0x3d 	//odczytywanie wartoœci rejestru
#define REG_REPLY_NOW 			0x00 	//rozkaz natychmiastowej odpowiedzi
#define REG_REPLY_STOP 			0xff 	//rozkaz zakoñczenia wysy³ania cyklicznego

#define REG_CUR_LIM			0x46 	//rejestr do odczytu pr¹du
#define REG_TORQUE 			0x90 	//rejestr do odczytu momentu obrotowego
#define REG_BUS_DC			0xeb 	//rejestr do odczytu napiêcia magistrali

/*
 * Error status defines
 * Used for CAN_MC_Status bit modification
 */
#define CAN_MC_INIT_ERROR	0x01
#define CAN_MC_OVERRUN		0x02
#define CAN_MC_RX_ERROR		0x04
#define CAN_MC_FILT_ERROR	0x08
#define CAN_MC_TX_ERROR		0x10

/*
 * Tx&Rx frames status defines
 * Used for CAN_MC_CAN_TxBuffer.Status and DataLocked bit modification and data assignment
 */
#define TX_READY				0x00
#define TX_FRG					0x01
#define TX_ENABLE				0x02
#define TX_CURRENT_LIMIT		0x03
#define TX_TORQUE				0x04
#define TX_VDC					0x05

#define RX_VDC					0x00

/*
 * Data fields
 */
CanRxMsgTypeDef RxMessage1; 		//for CAN_FIFO0 data
CanRxMsgTypeDef RxMessage2; 		//for CAN_FIFO1 data
CAN_FilterConfTypeDef RxFilter; 	//Can filter configuration structure
static uint8_t CAN_MC_Status;		//CAN_MC Error status field - 0 means no error
static uint8_t CAN_MC_Locked;		//Locking object

static struct __CAN_MC_TxBuffer
{
	CanTxMsgTypeDef Buffer[TxBufferLength];
	uint16_t Status;

} CAN_MC_TxBuffer;
static struct __CAN_MC_InData
{
	uint16_t Data[RxBufferLength];
} CAN_MC_InData;
static struct __CAN_MC_InDataLocked
{
	uint16_t Data[RxBufferLength];
	uint8_t Status;
} CAN_MC_InDataLocked;


/*
 * Init and locking functions
 */
void CAN_MC_Init(void); 			//CAN_MC_TxBuffer and filters initialisation
void CAN_MC_Lock(void); 			//provides locking mechanism for data integrity
void CAN_MC_Unlock(void); 			//function complementary to CAN_MC_Lock()


/*
 * Functions setting flags for CAN frames transmitting
 */
void CAN_MC_CyclicDataEnable(void);
void CAN_MC_TorqueCommand(int16_t Torque);
void CAN_MC_CurrentLimitCommand(uint16_t CurrentLimit);
//for future implementation
void CAN_MC_Disconnect(void);
void CAN_MC_CyclicDataDisable(void);
void CAN_MC_StopCommand(void);
void CAN_MC_SpeedCommand(uint16_t Speed);


/*
 * Functions returning data
 */
uint8_t CAN_MC_GetBusVDC(); //odczyt napiêcia na magistrali
//for future implementation
uint8_t CAN_MC_GetSpeed(); //odczyt prêdkoœci
uint8_t CAN_MC_GetTorque(); //odczyt momentu
uint8_t CAN_MC_GetReady(); //odczyt gotowoœci
uint8_t CAN_MC_GetFRG(); //odczyt FRG
uint8_t CAN_MC_Current(); //odczyt pr¹du

/*
 * Functions transmitting & receiving CAN frames
 */
void CAN_MC_ReceiveCallback(void); //callback od odebrania ramki
void CAN_MC_TransmitCallback(void); //callback od wyslania ramki

#endif

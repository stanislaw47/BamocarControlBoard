/*
 * TB_CAN_MC.h
 *
 *  Created on: 22 May 2018
 *      Author: Stanisław Cabała
 */

#ifndef TEST_BENCHES_TB_CAN_MC_H_
#define TEST_BENCHES_TB_CAN_MC_H_


void TestBench1(void){
	// initailization of library CAN_MC
	CAN_MC_Init(&hcan);
	CAN_MC_Connect(&hcan);

	//start a timer
	CAN_MC_TorqueCommand(&hcan, 500);
	//  CAN_MC_SpeedCommand(&hcan, 500);
	HAL_Delay(5000);
	CAN_MC_StopCommand(&hcan);

	//end testbench procedure
	CAN_MC_Disconnect(&hcan);
}

void TestBench2(void){
	// initailization of library CAN_MC
	CAN_MC_Init(&hcan);
	CAN_MC_Connect(&hcan);

	//start a timer
	CAN_MC_CyclicDataEnable(&hcan);
	HAL_Delay(300);
	CAN_MC_CyclicDataDisable(&hcan);

	//end testbench procedure
	CAN_MC_Disconnect(&hcan);
}

#endif /* TEST_BENCHES_TB_CAN_MC_H_ */

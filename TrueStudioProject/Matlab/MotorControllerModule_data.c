/*
 * Sponsored License - for use in support of a program or activity
 * sponsored by MathWorks.  Not for government, commercial or other
 * non-sponsored organizational use.
 *
 * File: MotorControllerModule_data.c
 *
 * Code generated for Simulink model 'MotorControllerModule'.
 *
 * Model version                  : 1.193
 * Simulink Coder version         : 8.13 (R2017b) 24-Jul-2017
 * C/C++ source code generated on : Tue Apr 10 10:17:04 2018
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#include "MotorControllerModule.h"

/* Block parameters (auto storage) */
P rtP = {
  /* Variable: AnSigRange
   * Referenced by: '<S2>/MATLAB Function'
   */
  3.3,

  /* Variable: ImaxEff
   * Referenced by: '<S1>/current reduction'
   */
  240.0,

  /* Variable: A1_DoLim
   * Referenced by:
   *   '<S1>/VoltageCheck'
   *   '<S2>/MATLAB Function'
   */
  0.7F,

  /* Variable: A1_UpLim
   * Referenced by:
   *   '<S1>/VoltageCheck'
   *   '<S2>/MATLAB Function'
   */
  2.3F,

  /* Variable: A2_DoLim
   * Referenced by:
   *   '<S1>/VoltageCheck'
   *   '<S2>/MATLAB Function'
   */
  0.4F,

  /* Variable: A2_UpLim
   * Referenced by:
   *   '<S1>/VoltageCheck'
   *   '<S2>/MATLAB Function'
   */
  1.7F,

  /* Variable: APPS_OffPlausThr
   * Referenced by: '<S1>/PlausibilityCheck'
   */
  25.0F,

  /* Variable: APPS_OnPlausThr
   * Referenced by: '<S1>/PlausibilityCheck'
   */
  5.0F,

  /* Variable: APPS_OnPosThr
   * Referenced by: '<S1>/PlausibilityCheck'
   */
  5.0F,

  /* Variable: BSE_PlausThr
   * Referenced by: '<S1>/PlausibilityCheck'
   */
  1.2F,

  /* Variable: B_DoLim
   * Referenced by: '<S1>/VoltageCheck'
   */
  0.8F,

  /* Variable: B_UpLim
   * Referenced by: '<S1>/VoltageCheck'
   */
  2.5F,

  /* Variable: BrakeVolMotorControllerOnThr
   * Referenced by: '<S1>/TS activation'
   */
  1.1F,

  /* Variable: LimitBufferOutMaxVoltage
   * Referenced by:
   *   '<S1>/Output scaling'
   *   '<S1>/Output scaling CAN'
   */
  10.0F,

  /* Variable: PlausWait
   * Referenced by: '<S1>/TorqueValueGeneration'
   */
  50.0F,

  /* Variable: PosBufferOutMaxVoltage
   * Referenced by:
   *   '<S1>/Output scaling'
   *   '<S1>/Output scaling CAN'
   */
  10.0F,

  /* Variable: PosDiffThreshold
   * Referenced by: '<S1>/PlausibilityCheck'
   */
  10.0F,

  /* Variable: PowerSafetyThr
   * Referenced by: '<S1>/current reduction'
   */
  0.9F,

  /* Variable: PrechargeVolThr
   * Referenced by: '<S1>/TS activation'
   */
  480.0F,

  /* Variable: VolOffsetOff
   * Referenced by: '<S1>/VoltageCheck'
   */
  0.1F,

  /* Variable: VolOffsetOn
   * Referenced by: '<S1>/VoltageCheck'
   */
  0.0F,

  /* Variable: CheckTimeout
   * Referenced by: '<S1>/TS activation'
   */
  200U
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

/*
 * Sponsored License - for use in support of a program or activity
 * sponsored by MathWorks.  Not for government, commercial or other
 * non-sponsored organizational use.
 *
 * File: Motor_data.c
 *
 * Code generated for Simulink model 'Motor'.
 *
 * Model version                  : 1.324
 * Simulink Coder version         : 8.13 (R2017b) 24-Jul-2017
 * C/C++ source code generated on : Tue Jul 10 11:47:41 2018
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objective: RAM efficiency
 * Validation result: Not run
 */

#include "Motor.h"

/* Block parameters (auto storage) */
P rtP = {
  /* Variable: Torque
   * Referenced by: '<S11>/1-D Lookup Table'
   */
  {
    { 0.0, 20.0, 100.0 },

    { 0.0, 0.0, 100.0 }
  },

  /* Variable: A1_scaling
   * Referenced by: '<S2>/1-D Lookup Table'
   */
  {
    { 1384U, 1810U },

    { 0.0F, 100.0F }
  },

  /* Variable: A2_scaling
   * Referenced by: '<S2>/1-D Lookup Table1'
   */
  {
    { 1955U, 2400U },

    { 0.0F, 100.0F }
  },

  /* Variable: ImaxEff
   * Referenced by: '<S10>/current reduction'
   */
  240.0,

  /* Variable: APPS_OffPlausThr
   * Referenced by: '<S1>/PlausibilityCheck'
   */
  25.0F,

  /* Variable: APPS_OnPlausThr
   * Referenced by: '<S1>/PlausibilityCheck'
   */
  5.0F,

  /* Variable: LimitBufferOutMaxVoltage
   * Referenced by:
   *   '<S1>/Output scaling'
   *   '<S1>/Output scaling CAN'
   */
  10.0F,

  /* Variable: PlausWait
   * Referenced by: '<S1>/PlausibilityHandling'
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
   * Referenced by: '<S10>/current reduction'
   */
  0.9F,

  /* Variable: PrechargeVolThr
   * Referenced by: '<S1>/TS activation'
   */
  90.0F,

  /* Variable: A1_DoLim
   * Referenced by: '<S1>/VoltageCheck'
   */
  1384U,

  /* Variable: A1_UpLim
   * Referenced by: '<S1>/VoltageCheck'
   */
  1810U,

  /* Variable: A2_DoLim
   * Referenced by: '<S1>/VoltageCheck'
   */
  1955U,

  /* Variable: A2_UpLim
   * Referenced by: '<S1>/VoltageCheck'
   */
  2400U,

  /* Variable: BSE_PlausThr
   * Referenced by: '<S1>/PlausibilityCheck'
   */
  2320U,

  /* Variable: B_DoLim
   * Referenced by: '<S1>/VoltageCheck'
   */
  2081U,

  /* Variable: B_UpLim
   * Referenced by: '<S1>/VoltageCheck'
   */
  2380U,

  /* Variable: BrakeVolMotorControllerOnThr
   * Referenced by: '<S1>/TS activation'
   */
  2200U,

  /* Variable: CheckTimeout
   * Referenced by: '<S1>/TS activation'
   */
  500U,

  /* Variable: RegBrakingSpeedThr
   * Referenced by: '<S11>/Switch'
   */
  600U,

  /* Variable: VolOffsetOff
   * Referenced by: '<S1>/VoltageCheck'
   */
  300U,

  /* Variable: VolOffsetOn
   * Referenced by: '<S1>/VoltageCheck'
   */
  0U
};

/* Constant parameters (auto storage) */
const ConstP rtConstP = {
  /* Computed Parameter: uDLookupTable_tableData
   * Referenced by: '<S10>/1-D Lookup Table'
   */
  { 0.0F, 700.0F },

  /* Computed Parameter: uDLookupTable_bp01Data
   * Referenced by: '<S10>/1-D Lookup Table'
   */
  { 0U, 21921U }
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

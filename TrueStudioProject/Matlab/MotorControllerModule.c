/*
 * Sponsored License - for use in support of a program or activity
 * sponsored by MathWorks.  Not for government, commercial or other
 * non-sponsored organizational use.
 *
 * File: MotorControllerModule.c
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

/* Named constants for Chart: '<S1>/PlausibilityCheck' */
#define IN_NOK                         ((uint8_T)1U)
#define IN_OK                          ((uint8_T)2U)

/* Named constants for Chart: '<S1>/TS activation' */
#define IN_INITIAL                     ((uint8_T)1U)
#define IN_MOTOR_CONTROLLER_OFF_CHECK  ((uint8_T)2U)
#define IN_MOTOR_CONTROLLER_ON         ((uint8_T)3U)
#define IN_MOTOR_CONTROLLER_ON_CHECK   ((uint8_T)4U)
#define IN_PRECHARGE_ACTIVATION        ((uint8_T)5U)
#define IN_PRECHARGE_CHECK             ((uint8_T)6U)
#define IN_TS_ACTIVE                   ((uint8_T)7U)

/* Named constants for Chart: '<S1>/TorqueValueGeneration' */
#define IN_NOK_Wait                    ((uint8_T)2U)
#define IN_OK_l                        ((uint8_T)3U)

/* Named constants for Chart: '<S1>/VoltageCheck' */
#define IN_A1A2B_NOK                   ((uint8_T)1U)
#define IN_A1A2B_OK                    ((uint8_T)2U)
#define IN_A1A2_NOK                    ((uint8_T)3U)
#define IN_A1B_NOK                     ((uint8_T)4U)
#define IN_A1_NOK                      ((uint8_T)5U)
#define IN_A2B_NOK                     ((uint8_T)6U)
#define IN_A2_NOK                      ((uint8_T)7U)
#define IN_B_NOK                       ((uint8_T)8U)
#define event_A1_NOK                   (0)
#define event_A1_OK                    (1)
#define event_A2_NOK                   (2)
#define event_A2_OK                    (3)
#define event_B_NOK                    (4)
#define event_B_OK                     (5)

/* Block signals and states (auto storage) */
DW rtDW;

/* External inputs (root inport signals with auto storage) */
ExtU rtU;

/* External outputs (root outports fed by signals with auto storage) */
ExtY rtY;

/* Real-time model */
RT_MODEL rtM_;
RT_MODEL *const rtM = &rtM_;
extern real_T rt_roundd_snf(real_T u);

/* Forward declaration for local functions */
static void V(const int32_T *sfEvent);
real_T rt_roundd_snf(real_T u)
{
  real_T y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = u * 0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

/* Function for Chart: '<S1>/VoltageCheck' */
static void V(const int32_T *sfEvent)
{
  switch (rtDW.is_V) {
   case IN_A1A2B_NOK:
    switch (*sfEvent) {
     case event_A2_OK:
      rtDW.is_V = IN_A1B_NOK;
      rtDW.voltage_status = false;
      break;

     case event_B_OK:
      rtDW.is_V = IN_A1A2_NOK;
      rtDW.voltage_status = false;
      break;

     case event_A1_OK:
      rtDW.is_V = IN_A2B_NOK;
      rtDW.voltage_status = false;
      break;
    }
    break;

   case IN_A1A2B_OK:
    switch (*sfEvent) {
     case event_A1_NOK:
      rtDW.is_V = IN_A1_NOK;
      rtDW.voltage_status = false;
      break;

     case event_A2_NOK:
      rtDW.is_V = IN_A2_NOK;
      rtDW.voltage_status = false;
      break;

     case event_B_NOK:
      rtDW.is_V = IN_B_NOK;
      rtDW.voltage_status = false;
      break;
    }
    break;

   case IN_A1A2_NOK:
    switch (*sfEvent) {
     case event_A2_OK:
      rtDW.is_V = IN_A1_NOK;
      rtDW.voltage_status = false;
      break;

     case event_A1_OK:
      rtDW.is_V = IN_A2_NOK;
      rtDW.voltage_status = false;
      break;

     case event_B_NOK:
      rtDW.is_V = IN_A1A2B_NOK;
      rtDW.voltage_status = false;
      break;
    }
    break;

   case IN_A1B_NOK:
    switch (*sfEvent) {
     case event_B_OK:
      rtDW.is_V = IN_A1_NOK;
      rtDW.voltage_status = false;
      break;

     case event_A1_OK:
      rtDW.is_V = IN_B_NOK;
      rtDW.voltage_status = false;
      break;

     case event_A2_NOK:
      rtDW.is_V = IN_A1A2B_NOK;
      rtDW.voltage_status = false;
      break;
    }
    break;

   case IN_A1_NOK:
    switch (*sfEvent) {
     case event_A2_NOK:
      rtDW.is_V = IN_A1A2_NOK;
      rtDW.voltage_status = false;
      break;

     case event_B_NOK:
      rtDW.is_V = IN_A1B_NOK;
      rtDW.voltage_status = false;
      break;

     case event_A1_OK:
      rtDW.is_V = IN_A1A2B_OK;
      rtDW.voltage_status = true;
      break;
    }
    break;

   case IN_A2B_NOK:
    switch (*sfEvent) {
     case event_A1_NOK:
      rtDW.is_V = IN_A1A2B_NOK;
      rtDW.voltage_status = false;
      break;

     case event_B_OK:
      rtDW.is_V = IN_A2_NOK;
      rtDW.voltage_status = false;
      break;

     case event_A2_OK:
      rtDW.is_V = IN_B_NOK;
      rtDW.voltage_status = false;
      break;
    }
    break;

   case IN_A2_NOK:
    switch (*sfEvent) {
     case event_A1_NOK:
      rtDW.is_V = IN_A1A2_NOK;
      rtDW.voltage_status = false;
      break;

     case event_B_NOK:
      rtDW.is_V = IN_A2B_NOK;
      rtDW.voltage_status = false;
      break;

     case event_A2_OK:
      rtDW.is_V = IN_A1A2B_OK;
      rtDW.voltage_status = true;
      break;
    }
    break;

   case IN_B_NOK:
    switch (*sfEvent) {
     case event_A2_NOK:
      rtDW.is_V = IN_A2B_NOK;
      rtDW.voltage_status = false;
      break;

     case event_A1_NOK:
      rtDW.is_V = IN_A1B_NOK;
      rtDW.voltage_status = false;
      break;

     case event_B_OK:
      rtDW.is_V = IN_A1A2B_OK;
      rtDW.voltage_status = true;
      break;
    }
    break;
  }
}

/* Model step function */
void MotorControllerModule_step(void)
{
  real32_T rtb_Saturation1;
  real32_T rtb_Saturation2;
  boolean_T rtb_APPS_PlausStatus;
  boolean_T rtb_BSE_PlausStatus;
  int32_T sfEvent;
  int32_T tmp;
  int32_T tmp_0;
  real_T tmp_1;
  uint16_T tmp_2;
  boolean_T guard1 = false;

  /* MATLAB Function: '<S2>/MATLAB Function' incorporates:
   *  Inport: '<Root>/APPS1'
   *  Inport: '<Root>/APPS2'
   *  Inport: '<Root>/BrakeEncoder'
   */
  tmp_1 = rt_roundd_snf((real_T)rtU.APPS1 * rtP.AnSigRange);
  if (tmp_1 < 65536.0) {
    if (tmp_1 >= 0.0) {
      tmp_2 = (uint16_T)tmp_1;
    } else {
      tmp_2 = 0U;
    }
  } else {
    tmp_2 = MAX_uint16_T;
  }

  tmp_0 = (int32_T)rt_roundd_snf((real_T)tmp_2 / 4096.0);
  tmp_1 = rt_roundd_snf((real_T)rtU.APPS2 * rtP.AnSigRange);
  if (tmp_1 < 65536.0) {
    if (tmp_1 >= 0.0) {
      tmp_2 = (uint16_T)tmp_1;
    } else {
      tmp_2 = 0U;
    }
  } else {
    tmp_2 = MAX_uint16_T;
  }

  tmp = (int32_T)rt_roundd_snf((real_T)tmp_2 / 4096.0);
  tmp_1 = rt_roundd_snf((real_T)rtU.BrakeEncoder * rtP.AnSigRange);
  if (tmp_1 < 65536.0) {
    if (tmp_1 >= 0.0) {
      tmp_2 = (uint16_T)tmp_1;
    } else {
      tmp_2 = 0U;
    }
  } else {
    tmp_2 = MAX_uint16_T;
  }

  tmp_2 = (uint16_T)(int32_T)rt_roundd_snf((real_T)tmp_2 / 4096.0);

  /* Chart: '<S1>/VoltageCheck' incorporates:
   *  MATLAB Function: '<S2>/MATLAB Function'
   */
  sfEvent = -1;
  if (rtDW.is_active_c17_MotorControllerMo == 0U) {
    rtDW.is_active_c17_MotorControllerMo = 1U;
    if (rtDW.is_c17_MotorControllerModule != 1U) {
      rtDW.is_c17_MotorControllerModule = 1U;
      rtDW.voltage_status = false;
    }

    rtDW.is_active_A1 = 1U;
    if (rtDW.is_A1 != IN_NOK) {
      rtDW.is_A1 = IN_NOK;
      sfEvent = event_A1_NOK;
      if (rtDW.is_active_V != 0U) {
        V(&sfEvent);
      }
    }

    rtDW.is_active_A2 = 1U;
    if (rtDW.is_A2 != IN_NOK) {
      rtDW.is_A2 = IN_NOK;
      sfEvent = event_A2_NOK;
      if (rtDW.is_active_V != 0U) {
        V(&sfEvent);
      }
    }

    rtDW.is_active_B = 1U;
    if (rtDW.is_B != IN_NOK) {
      rtDW.is_B = IN_NOK;
      sfEvent = event_B_NOK;
      if (rtDW.is_active_V != 0U) {
        V(&sfEvent);
      }
    }

    rtDW.is_active_V = 1U;
    if (rtDW.is_V != IN_A1A2B_NOK) {
      rtDW.is_V = IN_A1A2B_NOK;
      rtDW.voltage_status = false;
    }
  } else {
    if (rtDW.is_c17_MotorControllerModule == 1U) {
      if (rtDW.is_active_A1 != 0U) {
        switch (rtDW.is_A1) {
         case IN_NOK:
          if (((uint16_T)tmp_0 > rtP.A1_DoLim - rtP.VolOffsetOn) && ((uint16_T)
               tmp_0 < rtP.A1_UpLim + rtP.VolOffsetOn)) {
            rtDW.is_A1 = IN_OK;
            sfEvent = event_A1_OK;
            if (rtDW.is_active_V != 0U) {
              V(&sfEvent);
            }

            sfEvent = -1;
          }
          break;

         case IN_OK:
          if (((uint16_T)tmp_0 < rtP.A1_DoLim - rtP.VolOffsetOff) || ((uint16_T)
               tmp_0 > rtP.A1_UpLim + rtP.VolOffsetOff)) {
            rtDW.is_A1 = IN_NOK;
            sfEvent = event_A1_NOK;
            if (rtDW.is_active_V != 0U) {
              V(&sfEvent);
            }

            sfEvent = -1;
          }
          break;
        }
      }

      if (rtDW.is_active_A2 != 0U) {
        switch (rtDW.is_A2) {
         case IN_NOK:
          if (((uint16_T)tmp > rtP.A2_DoLim - rtP.VolOffsetOn) && ((uint16_T)tmp
               < rtP.A2_UpLim + rtP.VolOffsetOn)) {
            rtDW.is_A2 = IN_OK;
            sfEvent = event_A2_OK;
            if (rtDW.is_active_V != 0U) {
              V(&sfEvent);
            }

            sfEvent = -1;
          }
          break;

         case IN_OK:
          if (((uint16_T)tmp < rtP.A2_DoLim - rtP.VolOffsetOff) || ((uint16_T)
               tmp > rtP.A2_UpLim + rtP.VolOffsetOff)) {
            rtDW.is_A2 = IN_NOK;
            sfEvent = event_A2_NOK;
            if (rtDW.is_active_V != 0U) {
              V(&sfEvent);
            }

            sfEvent = -1;
          }
          break;
        }
      }

      if (rtDW.is_active_B != 0U) {
        switch (rtDW.is_B) {
         case IN_NOK:
          if ((tmp_2 > rtP.B_DoLim - rtP.VolOffsetOn) && (tmp_2 < rtP.B_UpLim +
               rtP.VolOffsetOn)) {
            rtDW.is_B = IN_OK;
            sfEvent = event_B_OK;
            if (rtDW.is_active_V != 0U) {
              V(&sfEvent);
            }

            sfEvent = -1;
          }
          break;

         case IN_OK:
          if ((tmp_2 < rtP.B_DoLim - rtP.VolOffsetOff) || (tmp_2 > rtP.B_UpLim +
               rtP.VolOffsetOff)) {
            rtDW.is_B = IN_NOK;
            sfEvent = event_B_NOK;
            if (rtDW.is_active_V != 0U) {
              V(&sfEvent);
            }

            sfEvent = -1;
          }
          break;
        }
      }

      if (rtDW.is_active_V != 0U) {
        V(&sfEvent);
      }
    }
  }

  /* End of Chart: '<S1>/VoltageCheck' */

  /* MATLAB Function: '<S2>/MATLAB Function' */
  rtb_Saturation1 = ((real32_T)(uint16_T)tmp_0 - rtP.A1_DoLim) / (rtP.A1_UpLim -
    rtP.A1_DoLim) * 100.0F;

  /* Saturate: '<S2>/Saturation1' */
  if (rtb_Saturation1 > 100.0F) {
    rtb_Saturation1 = 100.0F;
  } else {
    if (rtb_Saturation1 < 0.0F) {
      rtb_Saturation1 = 0.0F;
    }
  }

  /* End of Saturate: '<S2>/Saturation1' */

  /* MATLAB Function: '<S2>/MATLAB Function' */
  rtb_Saturation2 = ((real32_T)(uint16_T)tmp - rtP.A2_DoLim) / (rtP.A2_UpLim -
    rtP.A2_DoLim) * 100.0F;

  /* Saturate: '<S2>/Saturation2' */
  if (rtb_Saturation2 > 100.0F) {
    rtb_Saturation2 = 100.0F;
  } else {
    if (rtb_Saturation2 < 0.0F) {
      rtb_Saturation2 = 0.0F;
    }
  }

  /* End of Saturate: '<S2>/Saturation2' */

  /* Chart: '<S1>/PlausibilityCheck' incorporates:
   *  MATLAB Function: '<S2>/MATLAB Function'
   */
  if (rtDW.is_active_c13_MotorControllerMo == 0U) {
    rtDW.is_active_c13_MotorControllerMo = 1U;
    rtDW.is_APPS_PlausibilityCheck_EV2_3 = IN_NOK;
    rtb_APPS_PlausStatus = false;
    rtDW.is_BSE_PlausiblilityCheck_EV2_5 = IN_NOK;
    rtb_BSE_PlausStatus = false;
  } else {
    if (rtDW.is_APPS_PlausibilityCheck_EV2_3 == IN_NOK) {
      rtb_APPS_PlausStatus = false;
      if (fabsf(rtb_Saturation1 - rtb_Saturation2) < rtP.PosDiffThreshold) {
        rtDW.is_APPS_PlausibilityCheck_EV2_3 = IN_OK;
        rtb_APPS_PlausStatus = true;
      }
    } else {
      rtb_APPS_PlausStatus = true;
      if (fabsf(rtb_Saturation1 - rtb_Saturation2) > rtP.PosDiffThreshold) {
        rtDW.is_APPS_PlausibilityCheck_EV2_3 = IN_NOK;
        rtb_APPS_PlausStatus = false;
      }
    }

    if (rtDW.is_BSE_PlausiblilityCheck_EV2_5 == IN_NOK) {
      rtb_BSE_PlausStatus = false;
      if ((rtb_Saturation1 < rtP.APPS_OnPosThr) && (rtb_Saturation2 <
           rtP.APPS_OnPlausThr)) {
        rtDW.is_BSE_PlausiblilityCheck_EV2_5 = IN_OK;
        rtb_BSE_PlausStatus = true;
      }
    } else {
      rtb_BSE_PlausStatus = true;
      if (((rtb_Saturation1 > rtP.APPS_OffPlausThr) || (rtb_Saturation2 >
            rtP.APPS_OffPlausThr)) && (tmp_2 > rtP.BSE_PlausThr)) {
        rtDW.is_BSE_PlausiblilityCheck_EV2_5 = IN_NOK;
        rtb_BSE_PlausStatus = false;
      }
    }
  }

  /* End of Chart: '<S1>/PlausibilityCheck' */

  /* Chart: '<S1>/TorqueValueGeneration' */
  if (rtDW.temporalCounter_i1 < MAX_uint32_T) {
    rtDW.temporalCounter_i1++;
  }

  if (rtDW.is_active_c16_MotorControllerMo == 0U) {
    rtDW.is_active_c16_MotorControllerMo = 1U;
    rtDW.is_c16_MotorControllerModule = IN_NOK;
    rtDW.pos = 0.0F;
  } else {
    guard1 = false;
    switch (rtDW.is_c16_MotorControllerModule) {
     case IN_NOK:
      if (rtDW.voltage_status && rtb_APPS_PlausStatus && rtb_BSE_PlausStatus) {
        rtDW.is_c16_MotorControllerModule = IN_OK_l;
        rtDW.pos = (rtb_Saturation1 + rtb_Saturation2) / 2.0F;
      }
      break;

     case IN_NOK_Wait:
      if (rtDW.temporalCounter_i1 * 50U >= rtP.PlausWait) {
        guard1 = true;
      } else if (rtDW.voltage_status && rtb_APPS_PlausStatus) {
        rtDW.is_c16_MotorControllerModule = IN_OK_l;
        rtDW.pos = (rtb_Saturation1 + rtb_Saturation2) / 2.0F;
      } else if (!rtb_BSE_PlausStatus) {
        guard1 = true;
      } else {
        rtDW.is_c16_MotorControllerModule = IN_NOK_Wait;
        rtDW.temporalCounter_i1 = 0U;
        rtDW.pos = (rtb_Saturation1 + rtb_Saturation2) / 2.0F;
      }
      break;

     default:
      if (!rtb_BSE_PlausStatus) {
        rtDW.is_c16_MotorControllerModule = IN_NOK;
        rtDW.pos = 0.0F;
      } else if ((!rtDW.voltage_status) || (!rtb_APPS_PlausStatus)) {
        rtDW.is_c16_MotorControllerModule = IN_NOK_Wait;
        rtDW.temporalCounter_i1 = 0U;
        rtDW.pos = (rtb_Saturation1 + rtb_Saturation2) / 2.0F;
      } else {
        rtDW.is_c16_MotorControllerModule = IN_OK_l;
        rtDW.pos = (rtb_Saturation1 + rtb_Saturation2) / 2.0F;
      }
      break;
    }

    if (guard1) {
      rtDW.is_c16_MotorControllerModule = IN_NOK;
      rtDW.pos = 0.0F;
    }
  }

  /* End of Chart: '<S1>/TorqueValueGeneration' */

  /* MATLAB Function: '<S1>/MATLAB Function' incorporates:
   *  Inport: '<Root>/Voltage'
   */
  rtb_Saturation1 = 800.0F * (real32_T)rtU.Voltage / 24045.0F;

  /* MATLAB Function: '<S1>/Output scaling' */
  rtb_Saturation2 = roundf(rtDW.pos / 100.0F * 10.0F /
    rtP.PosBufferOutMaxVoltage * 4096.0F);
  if (rtb_Saturation2 < 65536.0F) {
    if (rtb_Saturation2 >= 0.0F) {
      /* Outport: '<Root>/BamocarTorqueOut' */
      rtY.BamocarTorqueOut = (uint16_T)rtb_Saturation2;
    } else {
      /* Outport: '<Root>/BamocarTorqueOut' */
      rtY.BamocarTorqueOut = 0U;
    }
  } else {
    /* Outport: '<Root>/BamocarTorqueOut' */
    rtY.BamocarTorqueOut = MAX_uint16_T;
  }

  /* MATLAB Function: '<S1>/current reduction' */
  rtb_Saturation2 = 80000.0F * rtP.PowerSafetyThr / rtb_Saturation1 / (real32_T)
    rtP.ImaxEff * 100.0F;

  /* Saturate: '<S1>/Saturation' */
  if (rtb_Saturation2 > 100.0F) {
    rtb_Saturation2 = 100.0F;
  } else {
    if (rtb_Saturation2 < 0.0F) {
      rtb_Saturation2 = 0.0F;
    }
  }

  /* End of Saturate: '<S1>/Saturation' */

  /* MATLAB Function: '<S1>/Output scaling' */
  rtb_Saturation2 = roundf(rtb_Saturation2 / 100.0F * 10.0F /
    rtP.LimitBufferOutMaxVoltage * 4096.0F);
  if (rtb_Saturation2 < 65536.0F) {
    if (rtb_Saturation2 >= 0.0F) {
      /* Outport: '<Root>/BamocarTorqueLimit' */
      rtY.BamocarTorqueLimit = (uint16_T)rtb_Saturation2;
    } else {
      /* Outport: '<Root>/BamocarTorqueLimit' */
      rtY.BamocarTorqueLimit = 0U;
    }
  } else {
    /* Outport: '<Root>/BamocarTorqueLimit' */
    rtY.BamocarTorqueLimit = MAX_uint16_T;
  }

  /* MATLAB Function: '<S1>/Output scaling CAN' */
  rtb_Saturation2 = roundf(0.0F / rtP.PosBufferOutMaxVoltage * 4096.0F);
  if (rtb_Saturation2 < 65536.0F) {
    if (rtb_Saturation2 >= 0.0F) {
      /* Outport: '<Root>/BamocarTorqueOut_CAN' */
      rtY.BamocarTorqueOut_CAN = (uint16_T)rtb_Saturation2;
    } else {
      /* Outport: '<Root>/BamocarTorqueOut_CAN' */
      rtY.BamocarTorqueOut_CAN = 0U;
    }
  } else {
    /* Outport: '<Root>/BamocarTorqueOut_CAN' */
    rtY.BamocarTorqueOut_CAN = MAX_uint16_T;
  }

  rtb_Saturation2 = roundf(0.0F / rtP.LimitBufferOutMaxVoltage * 4096.0F);
  if (rtb_Saturation2 < 65536.0F) {
    if (rtb_Saturation2 >= 0.0F) {
      /* Outport: '<Root>/BamocarCurrentLimitCAN' */
      rtY.BamocarCurrentLimitCAN = (uint16_T)rtb_Saturation2;
    } else {
      /* Outport: '<Root>/BamocarCurrentLimitCAN' */
      rtY.BamocarCurrentLimitCAN = 0U;
    }
  } else {
    /* Outport: '<Root>/BamocarCurrentLimitCAN' */
    rtY.BamocarCurrentLimitCAN = MAX_uint16_T;
  }

  /* End of MATLAB Function: '<S1>/Output scaling CAN' */

  /* Chart: '<S1>/TS activation' incorporates:
   *  Inport: '<Root>/RFE'
   *  Inport: '<Root>/START'
   *  MATLAB Function: '<S2>/MATLAB Function'
   */
  if (rtDW.temporalCounter_i1_b < MAX_uint32_T) {
    rtDW.temporalCounter_i1_b++;
  }

  if (rtDW.is_active_c15_MotorControllerMo == 0U) {
    rtDW.is_active_c15_MotorControllerMo = 1U;
    rtDW.is_c15_MotorControllerModule = IN_INITIAL;

    /* Outport: '<Root>/RDY' */
    rtY.RDY = false;

    /* Outport: '<Root>/PRECH' */
    rtY.PRECH = false;
  } else {
    switch (rtDW.is_c15_MotorControllerModule) {
     case IN_INITIAL:
      /* Outport: '<Root>/RDY' */
      rtY.RDY = false;

      /* Outport: '<Root>/PRECH' */
      rtY.PRECH = false;
      if (rtb_Saturation1 > rtP.PrechargeVolThr) {
        rtDW.is_c15_MotorControllerModule = IN_PRECHARGE_CHECK;
        rtDW.temporalCounter_i1_b = 0U;
      }
      break;

     case IN_MOTOR_CONTROLLER_OFF_CHECK:
      if (!rtU.START) {
        rtDW.is_c15_MotorControllerModule = IN_INITIAL;

        /* Outport: '<Root>/RDY' */
        rtY.RDY = false;

        /* Outport: '<Root>/PRECH' */
        rtY.PRECH = false;
      }
      break;

     case IN_MOTOR_CONTROLLER_ON:
      /* Outport: '<Root>/RDY' */
      rtY.RDY = true;
      if (!rtU.RFE) {
        rtDW.is_c15_MotorControllerModule = IN_INITIAL;

        /* Outport: '<Root>/RDY' */
        rtY.RDY = false;

        /* Outport: '<Root>/PRECH' */
        rtY.PRECH = false;
      } else {
        if (!rtU.START) {
          rtDW.is_c15_MotorControllerModule = IN_MOTOR_CONTROLLER_OFF_CHECK;
        }
      }
      break;

     case IN_MOTOR_CONTROLLER_ON_CHECK:
      if ((rtDW.temporalCounter_i1_b * 50U >= rtP.CheckTimeout) && ((tmp_2 >
            rtP.BrakeVolMotorControllerOnThr) && rtU.START)) {
        rtDW.is_c15_MotorControllerModule = IN_MOTOR_CONTROLLER_ON;

        /* Outport: '<Root>/RDY' */
        rtY.RDY = true;
      }
      break;

     case IN_PRECHARGE_ACTIVATION:
      /* Outport: '<Root>/PRECH' */
      rtY.PRECH = true;
      if (rtU.RFE) {
        rtDW.is_c15_MotorControllerModule = IN_TS_ACTIVE;
      }
      break;

     case IN_PRECHARGE_CHECK:
      if ((rtDW.temporalCounter_i1_b * 50U >= rtP.CheckTimeout) &&
          (rtb_Saturation1 > rtP.PrechargeVolThr)) {
        rtDW.is_c15_MotorControllerModule = IN_PRECHARGE_ACTIVATION;

        /* Outport: '<Root>/PRECH' */
        rtY.PRECH = true;
      }
      break;

     default:
      if (!rtU.RFE) {
        rtDW.is_c15_MotorControllerModule = IN_INITIAL;

        /* Outport: '<Root>/RDY' */
        rtY.RDY = false;

        /* Outport: '<Root>/PRECH' */
        rtY.PRECH = false;
      } else {
        if ((tmp_2 > rtP.BrakeVolMotorControllerOnThr) && rtU.START) {
          rtDW.is_c15_MotorControllerModule = IN_MOTOR_CONTROLLER_ON_CHECK;
          rtDW.temporalCounter_i1_b = 0U;
        }
      }
      break;
    }
  }

  /* End of Chart: '<S1>/TS activation' */
}

/* Model initialize function */
void MotorControllerModule_initialize(void)
{
  /* (no initialization code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

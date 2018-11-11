/*
 * Sponsored License - for use in support of a program or activity
 * sponsored by MathWorks.  Not for government, commercial or other
 * non-sponsored organizational use.
 *
 * File: Motor.c
 *
 * Code generated for Simulink model 'Motor'.
 *
 * Model version                  : 1.326
 * Simulink Coder version         : 8.14 (R2018a) 06-Feb-2018
 * C/C++ source code generated on : Sun Sep 23 13:53:11 2018
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objective: RAM efficiency
 * Validation result: Not run
 */

#include "Motor.h"

/* Named constants for Chart: '<S1>/PlausibilityCheck' */
#define IN_NOK                         ((uint8_T)1U)
#define IN_NO_ACTIVE_CHILD             ((uint8_T)0U)
#define IN_OK                          ((uint8_T)2U)

/* Named constants for Chart: '<S1>/PlausibilityHandling' */
#define IN_NOK_Wait                    ((uint8_T)2U)
#define IN_OK_d                        ((uint8_T)3U)

/* Named constants for Chart: '<S1>/TS activation' */
#define IN_ERROR_CAN_ADC               ((uint8_T)1U)
#define IN_ERROR_RFE                   ((uint8_T)2U)
#define IN_INITIAL                     ((uint8_T)1U)
#define IN_MOTOR_CONTROLLER_ACTIVATION ((uint8_T)3U)
#define IN_MOTOR_CONTROLLER_OFF        ((uint8_T)1U)
#define IN_MOTOR_CONTROLLER_OFF_CHECK  ((uint8_T)2U)
#define IN_MOTOR_CONTROLLER_OFF_CHECK_1 ((uint8_T)3U)
#define IN_MOTOR_CONTROLLER_ON         ((uint8_T)4U)
#define IN_MOTOR_CONTROLLER_ON_CHECK   ((uint8_T)5U)
#define IN_MOTOR_CONTROLLER_ON_CHECK1  ((uint8_T)6U)
#define IN_PRECHARGE                   ((uint8_T)4U)
#define IN_PRECHARGE_CHECK             ((uint8_T)2U)
#define IN_PRECHARGE_ON                ((uint8_T)3U)

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

/* Block signals and states (default storage) */
DW rtDW;

/* External inputs (root inport signals with default storage) */
ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
ExtY rtY;

/* Real-time model */
RT_MODEL rtM_;
RT_MODEL *const rtM = &rtM_;
extern real_T rt_roundd_snf(real_T u);
static real32_T look1_iu16lftf_pbinlc(uint16_T u0, const uint16_T bp0[], const
  real32_T table[], uint32_T prevIndex[], uint32_T maxIndex);
static real32_T look1_ifbdtdIf_pbinlc(real32_T u0, const real_T bp0[], const
  real_T table[], uint32_T prevIndex[], uint32_T maxIndex);

/* Forward declaration for local functions */
static void V(const int32_T *sfEvent);
static real32_T look1_iu16lftf_pbinlc(uint16_T u0, const uint16_T bp0[], const
  real32_T table[], uint32_T prevIndex[], uint32_T maxIndex)
{
  real32_T frac;
  uint32_T iRght;
  uint32_T iLeft;
  uint32_T bpIdx;
  uint32_T found;

  /* Lookup 1-D
     Search method: 'binary'
     Use previous index: 'on'
     Interpolation method: 'Linear point-slope'
     Extrapolation method: 'Clip'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  /* Prelookup - Index and Fraction
     Index Search method: 'binary'
     Extrapolation method: 'Clip'
     Use previous index: 'on'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u0 <= bp0[0U]) {
    bpIdx = 0U;
    frac = 0.0F;
  } else if (u0 < bp0[maxIndex]) {
    /* Binary Search using Previous Index */
    bpIdx = prevIndex[0U];
    iLeft = 0U;
    iRght = maxIndex;
    found = 0U;
    while (found == 0U) {
      if (u0 < bp0[bpIdx]) {
        iRght = bpIdx - 1U;
        bpIdx = (iRght + iLeft) >> 1U;
      } else if (u0 < bp0[bpIdx + 1U]) {
        found = 1U;
      } else {
        iLeft = bpIdx + 1U;
        bpIdx = (iRght + iLeft) >> 1U;
      }
    }

    frac = (real32_T)(uint16_T)((uint32_T)u0 - bp0[bpIdx]) / (real32_T)(uint16_T)
      ((uint32_T)bp0[bpIdx + 1U] - bp0[bpIdx]);
  } else {
    bpIdx = maxIndex - 1U;
    frac = 1.0F;
  }

  prevIndex[0U] = bpIdx;

  /* Interpolation 1-D
     Interpolation method: 'Linear point-slope'
     Use last breakpoint for index at or above upper limit: 'off'
     Overflow mode: 'wrapping'
   */
  return (table[bpIdx + 1U] - table[bpIdx]) * frac + table[bpIdx];
}

static real32_T look1_ifbdtdIf_pbinlc(real32_T u0, const real_T bp0[], const
  real_T table[], uint32_T prevIndex[], uint32_T maxIndex)
{
  real_T frac;
  uint32_T iRght;
  uint32_T iLeft;
  uint32_T bpIdx;
  uint32_T found;

  /* Lookup 1-D
     Search method: 'binary'
     Use previous index: 'on'
     Interpolation method: 'Linear point-slope'
     Extrapolation method: 'Clip'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  /* Prelookup - Index and Fraction
     Index Search method: 'binary'
     Extrapolation method: 'Clip'
     Use previous index: 'on'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u0 < bp0[0U]) {
    bpIdx = 0U;
    frac = 0.0;
  } else if (u0 < (real32_T)bp0[maxIndex]) {
    /* Binary Search using Previous Index */
    bpIdx = prevIndex[0U];
    iLeft = 0U;
    iRght = maxIndex;
    found = 0U;
    while (found == 0U) {
      if (u0 < bp0[bpIdx]) {
        iRght = bpIdx - 1U;
        bpIdx = (iRght + iLeft) >> 1U;
      } else if (u0 < bp0[bpIdx + 1U]) {
        found = 1U;
      } else {
        iLeft = bpIdx + 1U;
        bpIdx = (iRght + iLeft) >> 1U;
      }
    }

    frac = (u0 - bp0[bpIdx]) / (bp0[bpIdx + 1U] - bp0[bpIdx]);
  } else {
    bpIdx = maxIndex - 1U;
    frac = 1.0;
  }

  prevIndex[0U] = bpIdx;

  /* Interpolation 1-D
     Interpolation method: 'Linear point-slope'
     Use last breakpoint for index at or above upper limit: 'off'
     Overflow mode: 'wrapping'
   */
  return (real32_T)((table[bpIdx + 1U] - table[bpIdx]) * frac) + (real32_T)
    table[bpIdx];
}

/* Function for Chart: '<S1>/VoltageCheck' */
static void V(const int32_T *sfEvent)
{
  switch (rtDW.is_V) {
   case IN_A1A2B_NOK:
    if (*sfEvent == event_A2_OK) {
      rtDW.is_V = IN_A1B_NOK;

      /* Outport: '<Root>/VolStat' */
      rtY.VolStat = false;
    } else if (*sfEvent == event_B_OK) {
      rtDW.is_V = IN_A1A2_NOK;

      /* Outport: '<Root>/VolStat' */
      rtY.VolStat = false;
    } else {
      if (*sfEvent == event_A1_OK) {
        rtDW.is_V = IN_A2B_NOK;

        /* Outport: '<Root>/VolStat' */
        rtY.VolStat = false;
      }
    }
    break;

   case IN_A1A2B_OK:
    if (*sfEvent == event_A1_NOK) {
      rtDW.is_V = IN_A1_NOK;

      /* Outport: '<Root>/VolStat' */
      rtY.VolStat = false;
    } else if (*sfEvent == event_A2_NOK) {
      rtDW.is_V = IN_A2_NOK;

      /* Outport: '<Root>/VolStat' */
      rtY.VolStat = false;
    } else {
      if (*sfEvent == event_B_NOK) {
        rtDW.is_V = IN_B_NOK;

        /* Outport: '<Root>/VolStat' */
        rtY.VolStat = false;
      }
    }
    break;

   case IN_A1A2_NOK:
    if (*sfEvent == event_A2_OK) {
      rtDW.is_V = IN_A1_NOK;

      /* Outport: '<Root>/VolStat' */
      rtY.VolStat = false;
    } else if (*sfEvent == event_A1_OK) {
      rtDW.is_V = IN_A2_NOK;

      /* Outport: '<Root>/VolStat' */
      rtY.VolStat = false;
    } else {
      if (*sfEvent == event_B_NOK) {
        rtDW.is_V = IN_A1A2B_NOK;

        /* Outport: '<Root>/VolStat' */
        rtY.VolStat = false;
      }
    }
    break;

   case IN_A1B_NOK:
    if (*sfEvent == event_B_OK) {
      rtDW.is_V = IN_A1_NOK;

      /* Outport: '<Root>/VolStat' */
      rtY.VolStat = false;
    } else if (*sfEvent == event_A1_OK) {
      rtDW.is_V = IN_B_NOK;

      /* Outport: '<Root>/VolStat' */
      rtY.VolStat = false;
    } else {
      if (*sfEvent == event_A2_NOK) {
        rtDW.is_V = IN_A1A2B_NOK;

        /* Outport: '<Root>/VolStat' */
        rtY.VolStat = false;
      }
    }
    break;

   case IN_A1_NOK:
    if (*sfEvent == event_A2_NOK) {
      rtDW.is_V = IN_A1A2_NOK;

      /* Outport: '<Root>/VolStat' */
      rtY.VolStat = false;
    } else if (*sfEvent == event_B_NOK) {
      rtDW.is_V = IN_A1B_NOK;

      /* Outport: '<Root>/VolStat' */
      rtY.VolStat = false;
    } else {
      if (*sfEvent == event_A1_OK) {
        rtDW.is_V = IN_A1A2B_OK;

        /* Outport: '<Root>/VolStat' */
        rtY.VolStat = true;
      }
    }
    break;

   case IN_A2B_NOK:
    if (*sfEvent == event_A1_NOK) {
      rtDW.is_V = IN_A1A2B_NOK;

      /* Outport: '<Root>/VolStat' */
      rtY.VolStat = false;
    } else if (*sfEvent == event_B_OK) {
      rtDW.is_V = IN_A2_NOK;

      /* Outport: '<Root>/VolStat' */
      rtY.VolStat = false;
    } else {
      if (*sfEvent == event_A2_OK) {
        rtDW.is_V = IN_B_NOK;

        /* Outport: '<Root>/VolStat' */
        rtY.VolStat = false;
      }
    }
    break;

   case IN_A2_NOK:
    if (*sfEvent == event_A1_NOK) {
      rtDW.is_V = IN_A1A2_NOK;

      /* Outport: '<Root>/VolStat' */
      rtY.VolStat = false;
    } else if (*sfEvent == event_B_NOK) {
      rtDW.is_V = IN_A2B_NOK;

      /* Outport: '<Root>/VolStat' */
      rtY.VolStat = false;
    } else {
      if (*sfEvent == event_A2_OK) {
        rtDW.is_V = IN_A1A2B_OK;

        /* Outport: '<Root>/VolStat' */
        rtY.VolStat = true;
      }
    }
    break;

   case IN_B_NOK:
    if (*sfEvent == event_A2_NOK) {
      rtDW.is_V = IN_A2B_NOK;

      /* Outport: '<Root>/VolStat' */
      rtY.VolStat = false;
    } else if (*sfEvent == event_A1_NOK) {
      rtDW.is_V = IN_A1B_NOK;

      /* Outport: '<Root>/VolStat' */
      rtY.VolStat = false;
    } else {
      if (*sfEvent == event_B_OK) {
        rtDW.is_V = IN_A1A2B_OK;

        /* Outport: '<Root>/VolStat' */
        rtY.VolStat = true;
      }
    }
    break;
  }
}

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

/* Model step function */
void Motor_step(void)
{
  real32_T rtb_uDLookupTable1;
  boolean_T rtb_pos_error;
  real_T rtb_Switch;
  real32_T rtb_uDLookupTable_e;
  boolean_T rtb_APPS_PlausStatus;
  boolean_T rtb_BSE_PlausStatus;
  real32_T rtb_uDLookupTable;
  int32_T sfEvent;
  uint32_T qY;
  real32_T y;
  boolean_T guard1 = false;

  /* Lookup_n-D: '<S2>/1-D Lookup Table' incorporates:
   *  Inport: '<Root>/APPS1'
   */
  rtb_uDLookupTable1 = look1_iu16lftf_pbinlc(rtU.APPS1, rtP.A1_scaling.BP1,
    rtP.A1_scaling.Table, &rtDW.m_bpIndex, 1U);

  /* Saturate: '<S2>/Saturation' */
  if (rtb_uDLookupTable1 > 100.0F) {
    y = 100.0F;
  } else if (rtb_uDLookupTable1 < 0.0F) {
    y = 0.0F;
  } else {
    y = rtb_uDLookupTable1;
  }

  /* Lookup_n-D: '<S2>/1-D Lookup Table1' incorporates:
   *  Inport: '<Root>/APPS2'
   */
  rtb_uDLookupTable1 = look1_iu16lftf_pbinlc(rtU.APPS2, rtP.A2_scaling.BP1,
    rtP.A2_scaling.Table, &rtDW.m_bpIndex_d, 1U);

  /* Saturate: '<S2>/Saturation1' */
  if (rtb_uDLookupTable1 > 100.0F) {
    rtb_uDLookupTable1 = 100.0F;
  } else {
    if (rtb_uDLookupTable1 < 0.0F) {
      rtb_uDLookupTable1 = 0.0F;
    }
  }

  /* Chart: '<S1>/VoltageCheck' incorporates:
   *  Inport: '<Root>/APPS1'
   *  Inport: '<Root>/APPS2'
   *  Inport: '<Root>/BrakeEncoder'
   */
  sfEvent = -1;
  if (rtDW.is_active_c12_Motor == 0U) {
    rtDW.is_active_c12_Motor = 1U;
    if (rtDW.is_c12_Motor != 1) {
      rtDW.is_c12_Motor = 1;

      /* Outport: '<Root>/VolStat' */
      rtY.VolStat = false;
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

      /* Outport: '<Root>/VolStat' */
      rtY.VolStat = false;
    }
  } else {
    if (rtDW.is_c12_Motor == 1) {
      if (rtDW.is_active_A1 != 0U) {
        switch (rtDW.is_A1) {
         case IN_NOK:
          qY = (uint32_T)rtP.A1_DoLim - /*MW:OvSatOk*/ rtP.VolOffsetOn;
          if (qY > rtP.A1_DoLim) {
            qY = 0U;
          }

          if ((rtU.APPS1 > (int32_T)qY) && (rtU.APPS1 < (int32_T)((uint32_T)
                rtP.A1_UpLim + rtP.VolOffsetOn))) {
            rtDW.is_A1 = IN_OK;
            sfEvent = event_A1_OK;
            if (rtDW.is_active_V != 0U) {
              V(&sfEvent);
            }

            sfEvent = -1;
          }
          break;

         case IN_OK:
          qY = (uint32_T)rtP.A1_DoLim - /*MW:OvSatOk*/ rtP.VolOffsetOff;
          if (qY > rtP.A1_DoLim) {
            qY = 0U;
          }

          if ((rtU.APPS1 < (int32_T)qY) || (rtU.APPS1 > (int32_T)((uint32_T)
                rtP.A1_UpLim + rtP.VolOffsetOff))) {
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
          qY = (uint32_T)rtP.A2_DoLim - /*MW:OvSatOk*/ rtP.VolOffsetOn;
          if (qY > rtP.A2_DoLim) {
            qY = 0U;
          }

          if ((rtU.APPS2 > (int32_T)qY) && (rtU.APPS2 < (int32_T)((uint32_T)
                rtP.A2_UpLim + rtP.VolOffsetOn))) {
            rtDW.is_A2 = IN_OK;
            sfEvent = event_A2_OK;
            if (rtDW.is_active_V != 0U) {
              V(&sfEvent);
            }

            sfEvent = -1;
          }
          break;

         case IN_OK:
          qY = (uint32_T)rtP.A2_DoLim - /*MW:OvSatOk*/ rtP.VolOffsetOff;
          if (qY > rtP.A2_DoLim) {
            qY = 0U;
          }

          if ((rtU.APPS2 < (int32_T)qY) || (rtU.APPS2 > (int32_T)((uint32_T)
                rtP.A2_UpLim + rtP.VolOffsetOff))) {
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
          qY = (uint32_T)rtP.B_DoLim - /*MW:OvSatOk*/ rtP.VolOffsetOn;
          if (qY > rtP.B_DoLim) {
            qY = 0U;
          }

          if ((rtU.BrakeEncoder > (int32_T)qY) && (rtU.BrakeEncoder < (int32_T)
               ((uint32_T)rtP.B_UpLim + rtP.VolOffsetOn))) {
            rtDW.is_B = IN_OK;
            sfEvent = event_B_OK;
            if (rtDW.is_active_V != 0U) {
              V(&sfEvent);
            }

            sfEvent = -1;
          }
          break;

         case IN_OK:
          qY = (uint32_T)rtP.B_DoLim - /*MW:OvSatOk*/ rtP.VolOffsetOff;
          if (qY > rtP.B_DoLim) {
            qY = 0U;
          }

          if ((rtU.BrakeEncoder < (int32_T)qY) || (rtU.BrakeEncoder > (int32_T)
               ((uint32_T)rtP.B_UpLim + rtP.VolOffsetOff))) {
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

  /* Chart: '<S1>/PlausibilityCheck' incorporates:
   *  Inport: '<Root>/BrakeEncoder'
   *  Saturate: '<S2>/Saturation'
   *  Saturate: '<S2>/Saturation1'
   */
  if (rtDW.is_active_c7_Motor == 0U) {
    rtDW.is_active_c7_Motor = 1U;
    rtDW.is_APPS_PlausibilityCheck_EV2_3 = IN_NOK;
    rtb_APPS_PlausStatus = false;
    rtDW.is_BSE_PlausiblilityCheck_EV2_5 = IN_NOK;
    rtb_BSE_PlausStatus = false;
  } else {
    if (rtDW.is_APPS_PlausibilityCheck_EV2_3 == IN_NOK) {
      rtb_APPS_PlausStatus = false;
      if (fabsf(y - rtb_uDLookupTable1) < rtP.PosDiffThreshold) {
        rtDW.is_APPS_PlausibilityCheck_EV2_3 = IN_OK;
        rtb_APPS_PlausStatus = true;
      }
    } else {
      rtb_APPS_PlausStatus = true;
      if (fabsf(y - rtb_uDLookupTable1) > rtP.PosDiffThreshold) {
        rtDW.is_APPS_PlausibilityCheck_EV2_3 = IN_NOK;
        rtb_APPS_PlausStatus = false;
      }
    }

    if (rtDW.is_BSE_PlausiblilityCheck_EV2_5 == IN_NOK) {
      rtb_BSE_PlausStatus = false;
      if ((y < rtP.APPS_OnPlausThr) && (rtb_uDLookupTable1 < rtP.APPS_OnPlausThr))
      {
        rtDW.is_BSE_PlausiblilityCheck_EV2_5 = IN_OK;
        rtb_BSE_PlausStatus = true;
      }
    } else {
      rtb_BSE_PlausStatus = true;
      if (((y > rtP.APPS_OffPlausThr) || (rtb_uDLookupTable1 >
            rtP.APPS_OffPlausThr)) && (rtU.BrakeEncoder > rtP.BSE_PlausThr)) {
        rtDW.is_BSE_PlausiblilityCheck_EV2_5 = IN_NOK;
        rtb_BSE_PlausStatus = false;
      }
    }
  }

  /* End of Chart: '<S1>/PlausibilityCheck' */

  /* Chart: '<S1>/PlausibilityHandling' incorporates:
   *  Outport: '<Root>/VolStat'
   */
  if (rtDW.temporalCounter_i1_p < MAX_uint32_T) {
    rtDW.temporalCounter_i1_p++;
  }

  if (rtDW.is_active_c8_Motor == 0U) {
    rtDW.is_active_c8_Motor = 1U;
    rtDW.is_c8_Motor = IN_NOK;
    rtb_pos_error = true;
  } else {
    guard1 = false;
    switch (rtDW.is_c8_Motor) {
     case IN_NOK:
      rtb_pos_error = true;
      if (rtY.VolStat && rtb_APPS_PlausStatus && rtb_BSE_PlausStatus) {
        rtDW.is_c8_Motor = IN_OK_d;
        rtb_pos_error = false;
      }
      break;

     case IN_NOK_Wait:
      rtb_pos_error = false;
      if (rtDW.temporalCounter_i1_p * 50U >= rtP.PlausWait) {
        guard1 = true;
      } else if (rtY.VolStat && rtb_APPS_PlausStatus) {
        rtDW.is_c8_Motor = IN_OK_d;
      } else {
        if (!rtb_BSE_PlausStatus) {
          guard1 = true;
        }
      }
      break;

     default:
      rtb_pos_error = false;
      if (!rtb_BSE_PlausStatus) {
        rtDW.is_c8_Motor = IN_NOK;
        rtb_pos_error = true;
      } else {
        if ((!rtY.VolStat) || (!rtb_APPS_PlausStatus)) {
          rtDW.is_c8_Motor = IN_NOK_Wait;
          rtDW.temporalCounter_i1_p = 0U;
        }
      }
      break;
    }

    if (guard1) {
      rtDW.is_c8_Motor = IN_NOK;
      rtb_pos_error = true;
    }
  }

  /* End of Chart: '<S1>/PlausibilityHandling' */

  /* Lookup_n-D: '<S10>/1-D Lookup Table' incorporates:
   *  Inport: '<Root>/Voltage'
   */
  rtb_uDLookupTable = look1_iu16lftf_pbinlc(rtU.Voltage,
    rtConstP.uDLookupTable_bp01Data, rtConstP.uDLookupTable_tableData,
    &rtDW.m_bpIndex_l, 1U);

  /* Chart: '<S1>/TS activation' incorporates:
   *  Inport: '<Root>/ADC_STAT'
   *  Inport: '<Root>/BrakeEncoder'
   *  Inport: '<Root>/CAN_STAT'
   *  Inport: '<Root>/RFE'
   *  Inport: '<Root>/START'
   */
  if (rtDW.temporalCounter_i1 < MAX_uint32_T) {
    rtDW.temporalCounter_i1++;
  }

  if (rtDW.is_active_c11_Motor == 0U) {
    rtDW.is_active_c11_Motor = 1U;
    rtDW.is_c11_Motor = IN_ERROR_RFE;

    /* Outport: '<Root>/RDY' */
    rtY.RDY = false;

    /* Outport: '<Root>/PRECH' */
    rtY.PRECH = false;
  } else {
    switch (rtDW.is_c11_Motor) {
     case IN_ERROR_CAN_ADC:
      /* Outport: '<Root>/RDY' */
      rtY.RDY = false;
      if (rtU.CAN_STAT || rtU.ADC_STAT) {
        rtDW.is_c11_Motor = IN_MOTOR_CONTROLLER_ACTIVATION;
        rtDW.is_MOTOR_CONTROLLER_ACTIVATION = IN_MOTOR_CONTROLLER_OFF;

        /* Outport: '<Root>/RDY' */
        rtY.RDY = false;
      }
      break;

     case IN_ERROR_RFE:
      /* Outport: '<Root>/RDY' */
      rtY.RDY = false;

      /* Outport: '<Root>/PRECH' */
      rtY.PRECH = false;
      if (rtU.CAN_STAT && rtU.ADC_STAT && rtU.RFE) {
        rtDW.is_c11_Motor = IN_PRECHARGE;
        rtDW.is_PRECHARGE = IN_INITIAL;
      }
      break;

     case IN_MOTOR_CONTROLLER_ACTIVATION:
      if ((!rtU.CAN_STAT) || (!rtU.ADC_STAT)) {
        rtDW.is_MOTOR_CONTROLLER_ACTIVATION = IN_NO_ACTIVE_CHILD;
        rtDW.is_c11_Motor = IN_ERROR_CAN_ADC;

        /* Outport: '<Root>/RDY' */
        rtY.RDY = false;
      } else if (!rtU.RFE) {
        rtDW.is_MOTOR_CONTROLLER_ACTIVATION = IN_NO_ACTIVE_CHILD;
        rtDW.is_c11_Motor = IN_ERROR_RFE;

        /* Outport: '<Root>/RDY' */
        rtY.RDY = false;

        /* Outport: '<Root>/PRECH' */
        rtY.PRECH = false;
      } else {
        switch (rtDW.is_MOTOR_CONTROLLER_ACTIVATION) {
         case IN_MOTOR_CONTROLLER_OFF:
          /* Outport: '<Root>/RDY' */
          rtY.RDY = false;
          if ((rtU.BrakeEncoder > rtP.BrakeVolMotorControllerOnThr) && rtU.START)
          {
            rtDW.is_MOTOR_CONTROLLER_ACTIVATION = IN_MOTOR_CONTROLLER_ON_CHECK;
            rtDW.temporalCounter_i1 = 0U;
          }
          break;

         case IN_MOTOR_CONTROLLER_OFF_CHECK:
          if ((rtDW.temporalCounter_i1 * 50U >= rtP.CheckTimeout) && rtU.START)
          {
            rtDW.is_MOTOR_CONTROLLER_ACTIVATION =
              IN_MOTOR_CONTROLLER_OFF_CHECK_1;
          } else {
            if (!rtU.START) {
              rtDW.is_MOTOR_CONTROLLER_ACTIVATION = IN_MOTOR_CONTROLLER_ON;

              /* Outport: '<Root>/RDY' */
              rtY.RDY = true;
            }
          }
          break;

         case IN_MOTOR_CONTROLLER_OFF_CHECK_1:
          if (!rtU.START) {
            rtDW.is_MOTOR_CONTROLLER_ACTIVATION = IN_MOTOR_CONTROLLER_OFF;

            /* Outport: '<Root>/RDY' */
            rtY.RDY = false;
          }
          break;

         case IN_MOTOR_CONTROLLER_ON:
          /* Outport: '<Root>/RDY' */
          rtY.RDY = true;
          if (rtU.START) {
            rtDW.is_MOTOR_CONTROLLER_ACTIVATION = IN_MOTOR_CONTROLLER_OFF_CHECK;
            rtDW.temporalCounter_i1 = 0U;
          }
          break;

         case IN_MOTOR_CONTROLLER_ON_CHECK:
          if ((rtDW.temporalCounter_i1 * 50U >= rtP.CheckTimeout) &&
              ((rtU.BrakeEncoder > rtP.BrakeVolMotorControllerOnThr) &&
               rtU.START)) {
            rtDW.is_MOTOR_CONTROLLER_ACTIVATION = IN_MOTOR_CONTROLLER_ON_CHECK1;
          } else {
            if (!rtU.START) {
              rtDW.is_MOTOR_CONTROLLER_ACTIVATION = IN_MOTOR_CONTROLLER_OFF;

              /* Outport: '<Root>/RDY' */
              rtY.RDY = false;
            }
          }
          break;

         default:
          if (!rtU.START) {
            rtDW.is_MOTOR_CONTROLLER_ACTIVATION = IN_MOTOR_CONTROLLER_ON;

            /* Outport: '<Root>/RDY' */
            rtY.RDY = true;
          }
          break;
        }
      }
      break;

     default:
      if ((!rtU.CAN_STAT) || (!rtU.ADC_STAT) || (!rtU.RFE)) {
        rtDW.is_PRECHARGE = IN_NO_ACTIVE_CHILD;
        rtDW.is_c11_Motor = IN_ERROR_RFE;

        /* Outport: '<Root>/RDY' */
        rtY.RDY = false;

        /* Outport: '<Root>/PRECH' */
        rtY.PRECH = false;
      } else {
        switch (rtDW.is_PRECHARGE) {
         case IN_INITIAL:
          if (rtb_uDLookupTable > rtP.PrechargeVolThr) {
            rtDW.is_PRECHARGE = IN_PRECHARGE_CHECK;
            rtDW.temporalCounter_i1 = 0U;
          }
          break;

         case IN_PRECHARGE_CHECK:
          if ((rtDW.temporalCounter_i1 * 50U >= rtP.CheckTimeout) &&
              (rtb_uDLookupTable > rtP.PrechargeVolThr)) {
            rtDW.is_PRECHARGE = IN_PRECHARGE_ON;

            /* Outport: '<Root>/PRECH' */
            rtY.PRECH = true;
          }
          break;

         default:
          /* Outport: '<Root>/PRECH' */
          rtY.PRECH = true;
          rtDW.is_PRECHARGE = IN_NO_ACTIVE_CHILD;
          rtDW.is_c11_Motor = IN_MOTOR_CONTROLLER_ACTIVATION;
          rtDW.is_MOTOR_CONTROLLER_ACTIVATION = IN_MOTOR_CONTROLLER_OFF;

          /* Outport: '<Root>/RDY' */
          rtY.RDY = false;
          break;
        }
      }
      break;
    }
  }

  /* End of Chart: '<S1>/TS activation' */

  /* Switch: '<S8>/Switch' incorporates:
   *  Constant: '<S8>/Constant'
   *  Logic: '<S8>/Logical Operator'
   *  Logic: '<S8>/Logical Operator1'
   *  Outport: '<Root>/RDY'
   */
  if ((!rtb_pos_error) && rtY.RDY) {
    /* Lookup_n-D: '<S11>/1-D Lookup Table' incorporates:
     *  Gain: '<S2>/Gain'
     *  Saturate: '<S2>/Saturation'
     *  Saturate: '<S2>/Saturation1'
     *  Sum: '<S2>/Sum'
     */
    rtb_uDLookupTable_e = look1_ifbdtdIf_pbinlc((y + rtb_uDLookupTable1) * 0.5F,
      rtP.Torque.BP1, rtP.Torque.Table, &rtDW.m_bpIndex_dn, 2U);

    /* Switch: '<S12>/Switch2' incorporates:
     *  Constant: '<S11>/Constant'
     *  Inport: '<Root>/speed'
     *  RelationalOperator: '<S12>/LowerRelop1'
     *  Switch: '<S11>/Switch'
     */
    if (rtb_uDLookupTable_e > 100.0F) {
      rtb_uDLookupTable_e = 100.0F;
    } else {
      if (rtU.speed > rtP.RegBrakingSpeedThr) {
        /* Switch: '<S11>/Switch' incorporates:
         *  Constant: '<S11>/Constant1'
         */
        rtb_Switch = -20.0;
      } else {
        /* Switch: '<S11>/Switch' incorporates:
         *  Constant: '<S11>/Constant2'
         */
        rtb_Switch = 0.0;
      }

      /* Switch: '<S12>/Switch' incorporates:
       *  RelationalOperator: '<S12>/UpperRelop'
       */
      if (rtb_uDLookupTable_e < rtb_Switch) {
        rtb_uDLookupTable_e = (real32_T)rtb_Switch;
      }

      /* End of Switch: '<S12>/Switch' */
    }

    /* End of Switch: '<S12>/Switch2' */
    rtb_Switch = rtb_uDLookupTable_e;
  } else {
    rtb_Switch = 0.0;
  }

  /* End of Switch: '<S8>/Switch' */

  /* MATLAB Function: '<S10>/current reduction' */
  rtb_uDLookupTable = 80000.0F * rtP.PowerSafetyThr / rtb_uDLookupTable /
    (real32_T)rtP.ImaxEff * 100.0F;

  /* Saturate: '<S10>/Saturation' */
  if (rtb_uDLookupTable > 100.0F) {
    rtb_uDLookupTable = 100.0F;
  } else {
    if (rtb_uDLookupTable < 0.0F) {
      rtb_uDLookupTable = 0.0F;
    }
  }

  /* End of Saturate: '<S10>/Saturation' */

  /* MATLAB Function: '<S1>/Output scaling' */
  rtb_uDLookupTable_e = roundf((real32_T)(rtb_Switch / 100.0 * 10.0) /
    rtP.PosBufferOutMaxVoltage * 4096.0F);
  if (rtb_uDLookupTable_e < 65536.0F) {
    if (rtb_uDLookupTable_e >= 0.0F) {
      /* Outport: '<Root>/BamocarTorqueOut' */
      rtY.BamocarTorqueOut = (uint16_T)rtb_uDLookupTable_e;
    } else {
      /* Outport: '<Root>/BamocarTorqueOut' */
      rtY.BamocarTorqueOut = 0U;
    }
  } else {
    /* Outport: '<Root>/BamocarTorqueOut' */
    rtY.BamocarTorqueOut = MAX_uint16_T;
  }

  rtb_uDLookupTable_e = roundf(rtb_uDLookupTable / 100.0F * 10.0F /
    rtP.LimitBufferOutMaxVoltage * 4096.0F);
  if (rtb_uDLookupTable_e < 65536.0F) {
    if (rtb_uDLookupTable_e >= 0.0F) {
      /* Outport: '<Root>/BamocarTorqueLimit' */
      rtY.BamocarTorqueLimit = (uint16_T)rtb_uDLookupTable_e;
    } else {
      /* Outport: '<Root>/BamocarTorqueLimit' */
      rtY.BamocarTorqueLimit = 0U;
    }
  } else {
    /* Outport: '<Root>/BamocarTorqueLimit' */
    rtY.BamocarTorqueLimit = MAX_uint16_T;
  }

  /* End of MATLAB Function: '<S1>/Output scaling' */

  /* MATLAB Function: '<S1>/Output scaling CAN' */
  rtb_Switch = rt_roundd_snf(rtb_Switch / 100.0 * 32767.0);
  if (rtb_Switch < 32768.0) {
    /* Outport: '<Root>/BamocarTorqueOut_CAN' */
    rtY.BamocarTorqueOut_CAN = (int16_T)rtb_Switch;
  } else {
    /* Outport: '<Root>/BamocarTorqueOut_CAN' */
    rtY.BamocarTorqueOut_CAN = MAX_int16_T;
  }

  rtb_uDLookupTable_e = roundf(rtb_uDLookupTable);
  if (rtb_uDLookupTable_e < 65536.0F) {
    /* Outport: '<Root>/BamocarCurrentLimitCAN' */
    rtY.BamocarCurrentLimitCAN = (uint16_T)rtb_uDLookupTable_e;
  } else {
    /* Outport: '<Root>/BamocarCurrentLimitCAN' */
    rtY.BamocarCurrentLimitCAN = MAX_uint16_T;
  }

  /* End of MATLAB Function: '<S1>/Output scaling CAN' */

  /* Outport: '<Root>/APPS_PlausStat' */
  rtY.APPS_PlausStat = rtb_APPS_PlausStatus;

  /* Outport: '<Root>/BSE_PlausStat' */
  rtY.BSE_PlausStat = rtb_BSE_PlausStatus;

  /* Outport: '<Root>/pos1' incorporates:
   *  Saturate: '<S2>/Saturation'
   */
  rtY.pos1 = y;

  /* Outport: '<Root>/pos2' incorporates:
   *  Saturate: '<S2>/Saturation1'
   */
  rtY.pos2 = rtb_uDLookupTable1;
}

/* Model initialize function */
void Motor_initialize(void)
{
  /* (no initialization code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

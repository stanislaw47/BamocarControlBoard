/*
 * Sponsored License - for use in support of a program or activity
 * sponsored by MathWorks.  Not for government, commercial or other
 * non-sponsored organizational use.
 *
 * File: Motor.c
 *
 * Code generated for Simulink model 'Motor'.
 *
 * Model version                  : 1.319
 * Simulink Coder version         : 8.13 (R2017b) 24-Jul-2017
 * C/C++ source code generated on : Thu Jun  7 16:26:38 2018
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
#define IN_OK_l                        ((uint8_T)3U)

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

/* Block signals and states (auto storage) */
DW rtDW;

/* External inputs (root inport signals with auto storage) */
ExtU rtU;

/* External outputs (root outports fed by signals with auto storage) */
ExtY rtY;
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
     Interpolation method: 'Linear'
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
     Interpolation method: 'Linear'
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
     Interpolation method: 'Linear'
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
     Interpolation method: 'Linear'
     Use last breakpoint for index at or above upper limit: 'off'
     Overflow mode: 'wrapping'
   */
  return (real32_T)((table[bpIdx + 1U] - table[bpIdx]) * frac) + (real32_T)
    table[bpIdx];
}

/* Function for Chart: '<S1>/VoltageCheck' */
static void V(const int32_T *sfEvent)
{
  /* During 'V': '<S9>:31' */
  switch (rtDW.bitsForTID0.is_V) {
   case IN_A1A2B_NOK:
    /* During 'A1A2B_NOK': '<S9>:33' */
    /* '<S9>:43:1' sf_internal_predicateOutput = ... */
    /* '<S9>:43:1' A2_OK; */
    if (*sfEvent == event_A2_OK) {
      /* Transition: '<S9>:43' */
      rtDW.bitsForTID0.is_V = IN_A1B_NOK;

      /* Outport: '<Root>/VolStat' */
      /* Entry 'A1B_NOK': '<S9>:36' */
      /* '<S9>:36:1' voltage_status=false */
      rtY.VolStat = false;
    } else {
      /* '<S9>:42:1' sf_internal_predicateOutput = ... */
      /* '<S9>:42:1' B_OK; */
      if (*sfEvent == event_B_OK) {
        /* Transition: '<S9>:42' */
        rtDW.bitsForTID0.is_V = IN_A1A2_NOK;

        /* Outport: '<Root>/VolStat' */
        /* Entry 'A1A2_NOK': '<S9>:35' */
        /* '<S9>:35:1' voltage_status=false */
        rtY.VolStat = false;
      } else {
        /* '<S9>:44:1' sf_internal_predicateOutput = ... */
        /* '<S9>:44:1' A1_OK; */
        if (*sfEvent == event_A1_OK) {
          /* Transition: '<S9>:44' */
          rtDW.bitsForTID0.is_V = IN_A2B_NOK;

          /* Outport: '<Root>/VolStat' */
          /* Entry 'A2B_NOK': '<S9>:37' */
          /* '<S9>:37:1' voltage_status=false */
          rtY.VolStat = false;
        }
      }
    }
    break;

   case IN_A1A2B_OK:
    /* During 'A1A2B_OK': '<S9>:41' */
    /* '<S9>:62:1' sf_internal_predicateOutput = ... */
    /* '<S9>:62:1' A1_NOK; */
    if (*sfEvent == event_A1_NOK) {
      /* Transition: '<S9>:62' */
      rtDW.bitsForTID0.is_V = IN_A1_NOK;

      /* Outport: '<Root>/VolStat' */
      /* Entry 'A1_NOK': '<S9>:38' */
      /* '<S9>:38:1' voltage_status=false */
      rtY.VolStat = false;
    } else {
      /* '<S9>:64:1' sf_internal_predicateOutput = ... */
      /* '<S9>:64:1' A2_NOK; */
      if (*sfEvent == event_A2_NOK) {
        /* Transition: '<S9>:64' */
        rtDW.bitsForTID0.is_V = IN_A2_NOK;

        /* Outport: '<Root>/VolStat' */
        /* Entry 'A2_NOK': '<S9>:39' */
        /* '<S9>:39:1' voltage_status=false */
        rtY.VolStat = false;
      } else {
        /* '<S9>:66:1' sf_internal_predicateOutput = ... */
        /* '<S9>:66:1' B_NOK; */
        if (*sfEvent == event_B_NOK) {
          /* Transition: '<S9>:66' */
          rtDW.bitsForTID0.is_V = IN_B_NOK;

          /* Outport: '<Root>/VolStat' */
          /* Entry 'B_NOK': '<S9>:40' */
          /* '<S9>:40:1' voltage_status=false */
          rtY.VolStat = false;
        }
      }
    }
    break;

   case IN_A1A2_NOK:
    /* During 'A1A2_NOK': '<S9>:35' */
    /* '<S9>:45:1' sf_internal_predicateOutput = ... */
    /* '<S9>:45:1' A2_OK; */
    if (*sfEvent == event_A2_OK) {
      /* Transition: '<S9>:45' */
      rtDW.bitsForTID0.is_V = IN_A1_NOK;

      /* Outport: '<Root>/VolStat' */
      /* Entry 'A1_NOK': '<S9>:38' */
      /* '<S9>:38:1' voltage_status=false */
      rtY.VolStat = false;
    } else {
      /* '<S9>:46:1' sf_internal_predicateOutput = ... */
      /* '<S9>:46:1' A1_OK; */
      if (*sfEvent == event_A1_OK) {
        /* Transition: '<S9>:46' */
        rtDW.bitsForTID0.is_V = IN_A2_NOK;

        /* Outport: '<Root>/VolStat' */
        /* Entry 'A2_NOK': '<S9>:39' */
        /* '<S9>:39:1' voltage_status=false */
        rtY.VolStat = false;
      } else {
        /* '<S9>:50:1' sf_internal_predicateOutput = ... */
        /* '<S9>:50:1' B_NOK; */
        if (*sfEvent == event_B_NOK) {
          /* Transition: '<S9>:50' */
          rtDW.bitsForTID0.is_V = IN_A1A2B_NOK;

          /* Outport: '<Root>/VolStat' */
          /* Entry 'A1A2B_NOK': '<S9>:33' */
          /* '<S9>:33:1' voltage_status=false */
          rtY.VolStat = false;
        }
      }
    }
    break;

   case IN_A1B_NOK:
    /* During 'A1B_NOK': '<S9>:36' */
    /* '<S9>:47:1' sf_internal_predicateOutput = ... */
    /* '<S9>:47:1' B_OK; */
    if (*sfEvent == event_B_OK) {
      /* Transition: '<S9>:47' */
      rtDW.bitsForTID0.is_V = IN_A1_NOK;

      /* Outport: '<Root>/VolStat' */
      /* Entry 'A1_NOK': '<S9>:38' */
      /* '<S9>:38:1' voltage_status=false */
      rtY.VolStat = false;
    } else {
      /* '<S9>:48:1' sf_internal_predicateOutput = ... */
      /* '<S9>:48:1' A1_OK; */
      if (*sfEvent == event_A1_OK) {
        /* Transition: '<S9>:48' */
        rtDW.bitsForTID0.is_V = IN_B_NOK;

        /* Outport: '<Root>/VolStat' */
        /* Entry 'B_NOK': '<S9>:40' */
        /* '<S9>:40:1' voltage_status=false */
        rtY.VolStat = false;
      } else {
        /* '<S9>:51:1' sf_internal_predicateOutput = ... */
        /* '<S9>:51:1' A2_NOK; */
        if (*sfEvent == event_A2_NOK) {
          /* Transition: '<S9>:51' */
          rtDW.bitsForTID0.is_V = IN_A1A2B_NOK;

          /* Outport: '<Root>/VolStat' */
          /* Entry 'A1A2B_NOK': '<S9>:33' */
          /* '<S9>:33:1' voltage_status=false */
          rtY.VolStat = false;
        }
      }
    }
    break;

   case IN_A1_NOK:
    /* During 'A1_NOK': '<S9>:38' */
    /* '<S9>:55:1' sf_internal_predicateOutput = ... */
    /* '<S9>:55:1' A2_NOK; */
    if (*sfEvent == event_A2_NOK) {
      /* Transition: '<S9>:55' */
      rtDW.bitsForTID0.is_V = IN_A1A2_NOK;

      /* Outport: '<Root>/VolStat' */
      /* Entry 'A1A2_NOK': '<S9>:35' */
      /* '<S9>:35:1' voltage_status=false */
      rtY.VolStat = false;
    } else {
      /* '<S9>:60:1' sf_internal_predicateOutput = ... */
      /* '<S9>:60:1' B_NOK; */
      if (*sfEvent == event_B_NOK) {
        /* Transition: '<S9>:60' */
        rtDW.bitsForTID0.is_V = IN_A1B_NOK;

        /* Outport: '<Root>/VolStat' */
        /* Entry 'A1B_NOK': '<S9>:36' */
        /* '<S9>:36:1' voltage_status=false */
        rtY.VolStat = false;
      } else {
        /* '<S9>:61:1' sf_internal_predicateOutput = ... */
        /* '<S9>:61:1' A1_OK; */
        if (*sfEvent == event_A1_OK) {
          /* Transition: '<S9>:61' */
          rtDW.bitsForTID0.is_V = IN_A1A2B_OK;

          /* Outport: '<Root>/VolStat' */
          /* Entry 'A1A2B_OK': '<S9>:41' */
          /* '<S9>:41:1' voltage_status=true */
          rtY.VolStat = true;
        }
      }
    }
    break;

   case IN_A2B_NOK:
    /* During 'A2B_NOK': '<S9>:37' */
    /* '<S9>:52:1' sf_internal_predicateOutput = ... */
    /* '<S9>:52:1' A1_NOK; */
    if (*sfEvent == event_A1_NOK) {
      /* Transition: '<S9>:52' */
      rtDW.bitsForTID0.is_V = IN_A1A2B_NOK;

      /* Outport: '<Root>/VolStat' */
      /* Entry 'A1A2B_NOK': '<S9>:33' */
      /* '<S9>:33:1' voltage_status=false */
      rtY.VolStat = false;
    } else {
      /* '<S9>:53:1' sf_internal_predicateOutput = ... */
      /* '<S9>:53:1' B_OK; */
      if (*sfEvent == event_B_OK) {
        /* Transition: '<S9>:53' */
        rtDW.bitsForTID0.is_V = IN_A2_NOK;

        /* Outport: '<Root>/VolStat' */
        /* Entry 'A2_NOK': '<S9>:39' */
        /* '<S9>:39:1' voltage_status=false */
        rtY.VolStat = false;
      } else {
        /* '<S9>:54:1' sf_internal_predicateOutput = ... */
        /* '<S9>:54:1' A2_OK; */
        if (*sfEvent == event_A2_OK) {
          /* Transition: '<S9>:54' */
          rtDW.bitsForTID0.is_V = IN_B_NOK;

          /* Outport: '<Root>/VolStat' */
          /* Entry 'B_NOK': '<S9>:40' */
          /* '<S9>:40:1' voltage_status=false */
          rtY.VolStat = false;
        }
      }
    }
    break;

   case IN_A2_NOK:
    /* During 'A2_NOK': '<S9>:39' */
    /* '<S9>:56:1' sf_internal_predicateOutput = ... */
    /* '<S9>:56:1' A1_NOK; */
    if (*sfEvent == event_A1_NOK) {
      /* Transition: '<S9>:56' */
      rtDW.bitsForTID0.is_V = IN_A1A2_NOK;

      /* Outport: '<Root>/VolStat' */
      /* Entry 'A1A2_NOK': '<S9>:35' */
      /* '<S9>:35:1' voltage_status=false */
      rtY.VolStat = false;
    } else {
      /* '<S9>:57:1' sf_internal_predicateOutput = ... */
      /* '<S9>:57:1' B_NOK; */
      if (*sfEvent == event_B_NOK) {
        /* Transition: '<S9>:57' */
        rtDW.bitsForTID0.is_V = IN_A2B_NOK;

        /* Outport: '<Root>/VolStat' */
        /* Entry 'A2B_NOK': '<S9>:37' */
        /* '<S9>:37:1' voltage_status=false */
        rtY.VolStat = false;
      } else {
        /* '<S9>:63:1' sf_internal_predicateOutput = ... */
        /* '<S9>:63:1' A2_OK; */
        if (*sfEvent == event_A2_OK) {
          /* Transition: '<S9>:63' */
          rtDW.bitsForTID0.is_V = IN_A1A2B_OK;

          /* Outport: '<Root>/VolStat' */
          /* Entry 'A1A2B_OK': '<S9>:41' */
          /* '<S9>:41:1' voltage_status=true */
          rtY.VolStat = true;
        }
      }
    }
    break;

   case IN_B_NOK:
    /* During 'B_NOK': '<S9>:40' */
    /* '<S9>:58:1' sf_internal_predicateOutput = ... */
    /* '<S9>:58:1' A2_NOK; */
    if (*sfEvent == event_A2_NOK) {
      /* Transition: '<S9>:58' */
      rtDW.bitsForTID0.is_V = IN_A2B_NOK;

      /* Outport: '<Root>/VolStat' */
      /* Entry 'A2B_NOK': '<S9>:37' */
      /* '<S9>:37:1' voltage_status=false */
      rtY.VolStat = false;
    } else {
      /* '<S9>:59:1' sf_internal_predicateOutput = ... */
      /* '<S9>:59:1' A1_NOK; */
      if (*sfEvent == event_A1_NOK) {
        /* Transition: '<S9>:59' */
        rtDW.bitsForTID0.is_V = IN_A1B_NOK;

        /* Outport: '<Root>/VolStat' */
        /* Entry 'A1B_NOK': '<S9>:36' */
        /* '<S9>:36:1' voltage_status=false */
        rtY.VolStat = false;
      } else {
        /* '<S9>:65:1' sf_internal_predicateOutput = ... */
        /* '<S9>:65:1' B_OK; */
        if (*sfEvent == event_B_OK) {
          /* Transition: '<S9>:65' */
          rtDW.bitsForTID0.is_V = IN_A1A2B_OK;

          /* Outport: '<Root>/VolStat' */
          /* Entry 'A1A2B_OK': '<S9>:41' */
          /* '<S9>:41:1' voltage_status=true */
          rtY.VolStat = true;
        }
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
  real32_T rtb_Saturation;
  boolean_T rtb_pos_error;
  real_T rtb_Switch;
  int32_T sfEvent;
  real32_T tmp;
  uint32_T qY;
  boolean_T guard1 = false;

  /* Chart: '<S1>/VoltageCheck' incorporates:
   *  Inport: '<Root>/APPS1'
   *  Inport: '<Root>/APPS2'
   *  Inport: '<Root>/BrakeEncoder'
   */
  /* Gateway: Motor Controller Module/VoltageCheck */
  sfEvent = -1;

  /* During: Motor Controller Module/VoltageCheck */
  if (rtDW.bitsForTID0.is_active_c12_Motor == 0U) {
    /* Entry: Motor Controller Module/VoltageCheck */
    rtDW.bitsForTID0.is_active_c12_Motor = 1U;

    /* Entry Internal: Motor Controller Module/VoltageCheck */
    /* Transition: '<S9>:5' */
    if (rtDW.bitsForTID0.is_c12_Motor != 1U) {
      rtDW.bitsForTID0.is_c12_Motor = 1U;

      /* Outport: '<Root>/VolStat' */
      /* Entry 'INIT': '<S9>:4' */
      /* '<S9>:4:1' voltage_status=false */
      rtY.VolStat = false;
    }

    /* Entry Internal 'INIT': '<S9>:4' */
    rtDW.bitsForTID0.is_active_A1 = 1U;

    /* Entry Internal 'A1': '<S9>:7' */
    /* Transition: '<S9>:16' */
    if (rtDW.bitsForTID0.is_A1 != IN_NOK) {
      rtDW.bitsForTID0.is_A1 = IN_NOK;

      /* Entry 'NOK': '<S9>:15' */
      /* '<S9>:15:1' send(A1_NOK,V) */
      sfEvent = event_A1_NOK;
      if (rtDW.bitsForTID0.is_active_V != 0U) {
        V(&sfEvent);
      }
    }

    rtDW.bitsForTID0.is_active_A2 = 1U;

    /* Entry Internal 'A2': '<S9>:9' */
    /* Transition: '<S9>:18' */
    if (rtDW.bitsForTID0.is_A2 != IN_NOK) {
      rtDW.bitsForTID0.is_A2 = IN_NOK;

      /* Entry 'NOK': '<S9>:17' */
      /* '<S9>:17:1' send(A2_NOK,V) */
      sfEvent = event_A2_NOK;
      if (rtDW.bitsForTID0.is_active_V != 0U) {
        V(&sfEvent);
      }
    }

    rtDW.bitsForTID0.is_active_B = 1U;

    /* Entry Internal 'B': '<S9>:10' */
    /* Transition: '<S9>:20' */
    if (rtDW.bitsForTID0.is_B != IN_NOK) {
      rtDW.bitsForTID0.is_B = IN_NOK;

      /* Entry 'NOK': '<S9>:19' */
      /* '<S9>:19:1' send(B_NOK,V) */
      sfEvent = event_B_NOK;
      if (rtDW.bitsForTID0.is_active_V != 0U) {
        V(&sfEvent);
      }
    }

    rtDW.bitsForTID0.is_active_V = 1U;

    /* Entry Internal 'V': '<S9>:31' */
    /* Transition: '<S9>:34' */
    if (rtDW.bitsForTID0.is_V != IN_A1A2B_NOK) {
      rtDW.bitsForTID0.is_V = IN_A1A2B_NOK;

      /* Outport: '<Root>/VolStat' */
      /* Entry 'A1A2B_NOK': '<S9>:33' */
      /* '<S9>:33:1' voltage_status=false */
      rtY.VolStat = false;
    }
  } else {
    if (rtDW.bitsForTID0.is_c12_Motor == 1U) {
      /* During 'INIT': '<S9>:4' */
      if (rtDW.bitsForTID0.is_active_A1 != 0U) {
        /* During 'A1': '<S9>:7' */
        switch (rtDW.bitsForTID0.is_A1) {
         case IN_NOK:
          /* During 'NOK': '<S9>:15' */
          /* '<S9>:27:1' sf_internal_predicateOutput = ... */
          /* '<S9>:27:1' A1 > A1_DoLim-VolOffsetOn & A1 < A1_UpLim+VolOffsetOn; */
          qY = (uint32_T)rtP.A1_DoLim - /*MW:OvSatOk*/ rtP.VolOffsetOn;
          if (qY > rtP.A1_DoLim) {
            qY = 0U;
          }

          if ((rtU.APPS1 > (int32_T)qY) && (rtU.APPS1 < (int32_T)((uint32_T)
                rtP.A1_UpLim + rtP.VolOffsetOn))) {
            /* Transition: '<S9>:27' */
            rtDW.bitsForTID0.is_A1 = IN_OK;

            /* Entry 'OK': '<S9>:22' */
            /* '<S9>:22:1' send(A1_OK,V) */
            sfEvent = event_A1_OK;
            if (rtDW.bitsForTID0.is_active_V != 0U) {
              V(&sfEvent);
            }

            sfEvent = -1;
          }
          break;

         case IN_OK:
          /* During 'OK': '<S9>:22' */
          /* '<S9>:28:1' sf_internal_predicateOutput = ... */
          /* '<S9>:28:1' A1 < A1_DoLim-VolOffsetOff | A1 > A1_UpLim+VolOffsetOff; */
          qY = (uint32_T)rtP.A1_DoLim - /*MW:OvSatOk*/ rtP.VolOffsetOff;
          if (qY > rtP.A1_DoLim) {
            qY = 0U;
          }

          if ((rtU.APPS1 < (int32_T)qY) || (rtU.APPS1 > (int32_T)((uint32_T)
                rtP.A1_UpLim + rtP.VolOffsetOff))) {
            /* Transition: '<S9>:28' */
            rtDW.bitsForTID0.is_A1 = IN_NOK;

            /* Entry 'NOK': '<S9>:15' */
            /* '<S9>:15:1' send(A1_NOK,V) */
            sfEvent = event_A1_NOK;
            if (rtDW.bitsForTID0.is_active_V != 0U) {
              V(&sfEvent);
            }

            sfEvent = -1;
          }
          break;
        }
      }

      if (rtDW.bitsForTID0.is_active_A2 != 0U) {
        /* During 'A2': '<S9>:9' */
        switch (rtDW.bitsForTID0.is_A2) {
         case IN_NOK:
          /* During 'NOK': '<S9>:17' */
          /* '<S9>:26:1' sf_internal_predicateOutput = ... */
          /* '<S9>:26:1' A2>A2_DoLim-VolOffsetOn & A2<A2_UpLim+VolOffsetOn; */
          qY = (uint32_T)rtP.A2_DoLim - /*MW:OvSatOk*/ rtP.VolOffsetOn;
          if (qY > rtP.A2_DoLim) {
            qY = 0U;
          }

          if ((rtU.APPS2 > (int32_T)qY) && (rtU.APPS2 < (int32_T)((uint32_T)
                rtP.A2_UpLim + rtP.VolOffsetOn))) {
            /* Transition: '<S9>:26' */
            rtDW.bitsForTID0.is_A2 = IN_OK;

            /* Entry 'OK': '<S9>:23' */
            /* '<S9>:23:1' send(A2_OK,V) */
            sfEvent = event_A2_OK;
            if (rtDW.bitsForTID0.is_active_V != 0U) {
              V(&sfEvent);
            }

            sfEvent = -1;
          }
          break;

         case IN_OK:
          /* During 'OK': '<S9>:23' */
          /* '<S9>:29:1' sf_internal_predicateOutput = ... */
          /* '<S9>:29:1' A2<A2_DoLim-VolOffsetOff | A2>A2_UpLim+VolOffsetOff; */
          qY = (uint32_T)rtP.A2_DoLim - /*MW:OvSatOk*/ rtP.VolOffsetOff;
          if (qY > rtP.A2_DoLim) {
            qY = 0U;
          }

          if ((rtU.APPS2 < (int32_T)qY) || (rtU.APPS2 > (int32_T)((uint32_T)
                rtP.A2_UpLim + rtP.VolOffsetOff))) {
            /* Transition: '<S9>:29' */
            rtDW.bitsForTID0.is_A2 = IN_NOK;

            /* Entry 'NOK': '<S9>:17' */
            /* '<S9>:17:1' send(A2_NOK,V) */
            sfEvent = event_A2_NOK;
            if (rtDW.bitsForTID0.is_active_V != 0U) {
              V(&sfEvent);
            }

            sfEvent = -1;
          }
          break;
        }
      }

      if (rtDW.bitsForTID0.is_active_B != 0U) {
        /* During 'B': '<S9>:10' */
        switch (rtDW.bitsForTID0.is_B) {
         case IN_NOK:
          /* During 'NOK': '<S9>:19' */
          /* '<S9>:25:1' sf_internal_predicateOutput = ... */
          /* '<S9>:25:1' B>B_DoLim-VolOffsetOn & B<B_UpLim+VolOffsetOn; */
          qY = (uint32_T)rtP.B_DoLim - /*MW:OvSatOk*/ rtP.VolOffsetOn;
          if (qY > rtP.B_DoLim) {
            qY = 0U;
          }

          if ((rtU.BrakeEncoder > (int32_T)qY) && (rtU.BrakeEncoder < (int32_T)
               ((uint32_T)rtP.B_UpLim + rtP.VolOffsetOn))) {
            /* Transition: '<S9>:25' */
            rtDW.bitsForTID0.is_B = IN_OK;

            /* Entry 'OK': '<S9>:24' */
            /* '<S9>:24:1' send(B_OK,V) */
            sfEvent = event_B_OK;
            if (rtDW.bitsForTID0.is_active_V != 0U) {
              V(&sfEvent);
            }

            sfEvent = -1;
          }
          break;

         case IN_OK:
          /* During 'OK': '<S9>:24' */
          /* '<S9>:30:1' sf_internal_predicateOutput = ... */
          /* '<S9>:30:1' B<B_DoLim-VolOffsetOff | B>B_UpLim+VolOffsetOff; */
          qY = (uint32_T)rtP.B_DoLim - /*MW:OvSatOk*/ rtP.VolOffsetOff;
          if (qY > rtP.B_DoLim) {
            qY = 0U;
          }

          if ((rtU.BrakeEncoder < (int32_T)qY) || (rtU.BrakeEncoder > (int32_T)
               ((uint32_T)rtP.B_UpLim + rtP.VolOffsetOff))) {
            /* Transition: '<S9>:30' */
            rtDW.bitsForTID0.is_B = IN_NOK;

            /* Entry 'NOK': '<S9>:19' */
            /* '<S9>:19:1' send(B_NOK,V) */
            sfEvent = event_B_NOK;
            if (rtDW.bitsForTID0.is_active_V != 0U) {
              V(&sfEvent);
            }

            sfEvent = -1;
          }
          break;
        }
      }

      if (rtDW.bitsForTID0.is_active_V != 0U) {
        V(&sfEvent);
      }
    }
  }

  /* End of Chart: '<S1>/VoltageCheck' */

  /* Lookup_n-D: '<S2>/1-D Lookup Table' incorporates:
   *  Inport: '<Root>/APPS1'
   */
  rtb_uDLookupTable1 = look1_iu16lftf_pbinlc(rtU.APPS1, rtP.A1_scaling.BP1,
    rtP.A1_scaling.Table, &rtDW.m_bpIndex, 1U);

  /* Saturate: '<S2>/Saturation' */
  if (rtb_uDLookupTable1 > 100.0F) {
    rtb_Saturation = 100.0F;
  } else if (rtb_uDLookupTable1 < 0.0F) {
    rtb_Saturation = 0.0F;
  } else {
    rtb_Saturation = rtb_uDLookupTable1;
  }

  /* End of Saturate: '<S2>/Saturation' */

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

  /* End of Saturate: '<S2>/Saturation1' */

  /* Chart: '<S1>/PlausibilityCheck' incorporates:
   *  Inport: '<Root>/BrakeEncoder'
   */
  /* Gateway: Motor Controller Module/PlausibilityCheck */
  /* During: Motor Controller Module/PlausibilityCheck */
  if (rtDW.bitsForTID0.is_active_c7_Motor == 0U) {
    /* Entry: Motor Controller Module/PlausibilityCheck */
    rtDW.bitsForTID0.is_active_c7_Motor = 1U;

    /* Entry Internal: Motor Controller Module/PlausibilityCheck */
    /* Transition: '<S5>:13' */
    /* Entry Internal 'INIT': '<S5>:10' */
    /* Entry Internal 'APPS_PlausibilityCheck_EV2_3': '<S5>:11' */
    /* Transition: '<S5>:2' */
    rtDW.bitsForTID0.is_APPS_PlausibilityCheck_EV2_3 = IN_NOK;

    /* Entry 'NOK': '<S5>:1' */
    /* '<S5>:1:1' APPS_PlausStatus=false */
    rtY.APPS_PlausStat = false;

    /* Entry Internal 'BSE_PlausiblilityCheck_EV2_5': '<S5>:12' */
    /* Transition: '<S5>:16' */
    rtDW.bitsForTID0.is_BSE_PlausiblilityCheck_EV2_5 = IN_NOK;

    /* Entry 'NOK': '<S5>:15' */
    /* '<S5>:15:1' BSE_PlausStatus=false */
    rtY.BSE_PlausStat = false;
  } else {
    /* During 'INIT': '<S5>:10' */
    /* During 'APPS_PlausibilityCheck_EV2_3': '<S5>:11' */
    if (rtDW.bitsForTID0.is_APPS_PlausibilityCheck_EV2_3 == IN_NOK) {
      rtY.APPS_PlausStat = false;

      /* During 'NOK': '<S5>:1' */
      /* '<S5>:9:1' sf_internal_predicateOutput = ... */
      /* '<S5>:9:1' abs(pos1-pos2) < PosDiffThreshold; */
      if (fabsf(rtb_Saturation - rtb_uDLookupTable1) < rtP.PosDiffThreshold) {
        /* Transition: '<S5>:9' */
        rtDW.bitsForTID0.is_APPS_PlausibilityCheck_EV2_3 = IN_OK;

        /* Entry 'OK': '<S5>:7' */
        /* '<S5>:7:1' APPS_PlausStatus=true */
        rtY.APPS_PlausStat = true;
      }
    } else {
      rtY.APPS_PlausStat = true;

      /* During 'OK': '<S5>:7' */
      /* '<S5>:8:1' sf_internal_predicateOutput = ... */
      /* '<S5>:8:1' abs(pos1-pos2) > PosDiffThreshold; */
      if (fabsf(rtb_Saturation - rtb_uDLookupTable1) > rtP.PosDiffThreshold) {
        /* Transition: '<S5>:8' */
        rtDW.bitsForTID0.is_APPS_PlausibilityCheck_EV2_3 = IN_NOK;

        /* Entry 'NOK': '<S5>:1' */
        /* '<S5>:1:1' APPS_PlausStatus=false */
        rtY.APPS_PlausStat = false;
      }
    }

    /* During 'BSE_PlausiblilityCheck_EV2_5': '<S5>:12' */
    if (rtDW.bitsForTID0.is_BSE_PlausiblilityCheck_EV2_5 == IN_NOK) {
      rtY.BSE_PlausStat = false;

      /* During 'NOK': '<S5>:15' */
      /* '<S5>:18:1' sf_internal_predicateOutput = ... */
      /* '<S5>:18:1' pos1<APPS_OnPlausThr & pos2 < APPS_OnPlausThr; */
      if ((rtb_Saturation < rtP.APPS_OnPlausThr) && (rtb_uDLookupTable1 <
           rtP.APPS_OnPlausThr)) {
        /* Transition: '<S5>:18' */
        rtDW.bitsForTID0.is_BSE_PlausiblilityCheck_EV2_5 = IN_OK;

        /* Entry 'OK': '<S5>:17' */
        /* '<S5>:17:1' BSE_PlausStatus=true */
        rtY.BSE_PlausStat = true;
      }
    } else {
      rtY.BSE_PlausStat = true;

      /* During 'OK': '<S5>:17' */
      /* '<S5>:19:1' sf_internal_predicateOutput = ... */
      /* '<S5>:19:1' (pos1>APPS_OffPlausThr | pos2>APPS_OffPlausThr) & BSE>BSE_PlausThr; */
      if (((rtb_Saturation > rtP.APPS_OffPlausThr) || (rtb_uDLookupTable1 >
            rtP.APPS_OffPlausThr)) && (rtU.BrakeEncoder > rtP.BSE_PlausThr)) {
        /* Transition: '<S5>:19' */
        rtDW.bitsForTID0.is_BSE_PlausiblilityCheck_EV2_5 = IN_NOK;

        /* Entry 'NOK': '<S5>:15' */
        /* '<S5>:15:1' BSE_PlausStatus=false */
        rtY.BSE_PlausStat = false;
      }
    }
  }

  /* End of Chart: '<S1>/PlausibilityCheck' */

  /* Chart: '<S1>/PlausibilityHandling' incorporates:
   *  Outport: '<Root>/VolStat'
   */
  if (rtDW.temporalCounter_i1_m < MAX_uint32_T) {
    rtDW.temporalCounter_i1_m++;
  }

  /* Gateway: Motor Controller Module/PlausibilityHandling */
  /* During: Motor Controller Module/PlausibilityHandling */
  if (rtDW.bitsForTID0.is_active_c8_Motor == 0U) {
    /* Entry: Motor Controller Module/PlausibilityHandling */
    rtDW.bitsForTID0.is_active_c8_Motor = 1U;

    /* Entry Internal: Motor Controller Module/PlausibilityHandling */
    /* Transition: '<S6>:7' */
    rtDW.bitsForTID0.is_c8_Motor = IN_NOK;

    /* Entry 'NOK': '<S6>:6' */
    /* '<S6>:6:1' pos_error=true */
    rtb_pos_error = true;
  } else {
    guard1 = false;
    switch (rtDW.bitsForTID0.is_c8_Motor) {
     case IN_NOK:
      rtb_pos_error = true;

      /* During 'NOK': '<S6>:6' */
      /* '<S6>:9:1' sf_internal_predicateOutput = ... */
      /* '<S6>:9:1' VolStat==true & APPS_Stat==true & BSE_Stat==true; */
      if (rtY.VolStat && rtY.APPS_PlausStat && rtY.BSE_PlausStat) {
        /* Transition: '<S6>:9' */
        rtDW.bitsForTID0.is_c8_Motor = IN_OK_l;

        /* Entry 'OK': '<S6>:8' */
        /* '<S6>:8:1' pos_error=false */
        rtb_pos_error = false;
      }
      break;

     case IN_NOK_Wait:
      rtb_pos_error = false;

      /* During 'NOK_Wait': '<S6>:13' */
      /* '<S6>:16:1' sf_internal_predicateOutput = ... */
      /* '<S6>:16:1' after(PlausWait,msec); */
      if (rtDW.temporalCounter_i1_m * 50U >= rtP.PlausWait) {
        /* Transition: '<S6>:16' */
        guard1 = true;
      } else {
        /* '<S6>:18:1' sf_internal_predicateOutput = ... */
        /* '<S6>:18:1' VolStat==true & APPS_Stat==true; */
        if (rtY.VolStat && rtY.APPS_PlausStat) {
          /* Transition: '<S6>:18' */
          rtDW.bitsForTID0.is_c8_Motor = IN_OK_l;

          /* Entry 'OK': '<S6>:8' */
          /* '<S6>:8:1' pos_error=false */
        } else {
          /* '<S6>:20:1' sf_internal_predicateOutput = ... */
          /* '<S6>:20:1' BSE_Stat==false; */
          if (!rtY.BSE_PlausStat) {
            /* Transition: '<S6>:20' */
            guard1 = true;
          }
        }
      }
      break;

     default:
      rtb_pos_error = false;

      /* During 'OK': '<S6>:8' */
      /* '<S6>:10:1' sf_internal_predicateOutput = ... */
      /* '<S6>:10:1' BSE_Stat==false; */
      if (!rtY.BSE_PlausStat) {
        /* Transition: '<S6>:10' */
        rtDW.bitsForTID0.is_c8_Motor = IN_NOK;

        /* Entry 'NOK': '<S6>:6' */
        /* '<S6>:6:1' pos_error=true */
        rtb_pos_error = true;
      } else {
        /* '<S6>:14:1' sf_internal_predicateOutput = ... */
        /* '<S6>:14:1' VolStat==false | APPS_Stat==false; */
        if ((!rtY.VolStat) || (!rtY.APPS_PlausStat)) {
          /* Transition: '<S6>:14' */
          rtDW.bitsForTID0.is_c8_Motor = IN_NOK_Wait;
          rtDW.temporalCounter_i1_m = 0U;

          /* Entry 'NOK_Wait': '<S6>:13' */
          /* '<S6>:13:1' pos_error=false */
        }
      }
      break;
    }

    if (guard1) {
      rtDW.bitsForTID0.is_c8_Motor = IN_NOK;

      /* Entry 'NOK': '<S6>:6' */
      /* '<S6>:6:1' pos_error=true */
      rtb_pos_error = true;
    }
  }

  /* End of Chart: '<S1>/PlausibilityHandling' */

  /* Switch: '<S8>/Switch' incorporates:
   *  Constant: '<S8>/Constant'
   */
  if (rtb_pos_error) {
    rtb_Switch = 0.0;
  } else {
    /* Lookup_n-D: '<S11>/1-D Lookup Table' incorporates:
     *  Gain: '<S2>/Gain'
     *  Sum: '<S2>/Sum'
     */
    rtb_uDLookupTable1 = look1_ifbdtdIf_pbinlc((rtb_Saturation +
      rtb_uDLookupTable1) * 0.5F, rtP.Torque.BP1, rtP.Torque.Table,
      &rtDW.m_bpIndex_dn, 2U);

    /* Switch: '<S12>/Switch2' incorporates:
     *  Constant: '<S11>/Constant'
     *  Inport: '<Root>/speed'
     *  RelationalOperator: '<S12>/LowerRelop1'
     *  Switch: '<S11>/Switch'
     */
    if (rtb_uDLookupTable1 > 100.0F) {
      rtb_uDLookupTable1 = 100.0F;
    } else {
      if (rtU.speed > rtP.RegBrakingSpeedThr) {
        /* Switch: '<S11>/Switch' incorporates:
         *  Constant: '<S11>/Constant1'
         */
        sfEvent = -20;
      } else {
        /* Switch: '<S11>/Switch' incorporates:
         *  Constant: '<S11>/Constant2'
         */
        sfEvent = 0;
      }

      /* Switch: '<S12>/Switch' incorporates:
       *  RelationalOperator: '<S12>/UpperRelop'
       */
      if ((real_T)rtb_uDLookupTable1 < sfEvent) {
        rtb_uDLookupTable1 = (real32_T)sfEvent;
      }

      /* End of Switch: '<S12>/Switch' */
    }

    /* End of Switch: '<S12>/Switch2' */
    rtb_Switch = rtb_uDLookupTable1;
  }

  /* End of Switch: '<S8>/Switch' */

  /* Lookup_n-D: '<S10>/1-D Lookup Table' incorporates:
   *  Inport: '<Root>/Voltage'
   */
  rtb_uDLookupTable1 = look1_iu16lftf_pbinlc(rtU.Voltage,
    rtConstP.uDLookupTable_bp01Data, rtConstP.uDLookupTable_tableData,
    &rtDW.m_bpIndex_l, 1U);

  /* MATLAB Function: '<S10>/current reduction' */
  /* MATLAB Function 'Motor Controller Module/current_reduction&voltage_scaling/current reduction': '<S13>:1' */
  /* '<S13>:1:3' limit=single((80000*PowerSafetyThr/voltage)/ImaxEff*100); */
  rtb_Saturation = 80000.0F * rtP.PowerSafetyThr / rtb_uDLookupTable1 /
    (real32_T)rtP.ImaxEff * 100.0F;

  /* Saturate: '<S10>/Saturation' */
  if (rtb_Saturation > 100.0F) {
    rtb_Saturation = 100.0F;
  } else {
    if (rtb_Saturation < 0.0F) {
      rtb_Saturation = 0.0F;
    }
  }

  /* End of Saturate: '<S10>/Saturation' */

  /* MATLAB Function: '<S1>/Output scaling' */
  /* MATLAB Function 'Motor Controller Module/Output scaling': '<S3>:1' */
  /* '<S3>:1:3' pos_out=uint16(pos/100*10/PosBufferOutMaxVoltage*4096); */
  /* '<S3>:1:4' limit_out=uint16(limit/100*10/LimitBufferOutMaxVoltage*4096); */
  tmp = roundf((real32_T)(rtb_Switch / 100.0 * 10.0) /
               rtP.PosBufferOutMaxVoltage * 4096.0F);
  if (tmp < 65536.0F) {
    if (tmp >= 0.0F) {
      /* Outport: '<Root>/BamocarTorqueOut' */
      rtY.BamocarTorqueOut = (uint16_T)tmp;
    } else {
      /* Outport: '<Root>/BamocarTorqueOut' */
      rtY.BamocarTorqueOut = 0U;
    }
  } else {
    /* Outport: '<Root>/BamocarTorqueOut' */
    rtY.BamocarTorqueOut = MAX_uint16_T;
  }

  tmp = roundf(rtb_Saturation / 100.0F * 10.0F / rtP.LimitBufferOutMaxVoltage *
               4096.0F);
  if (tmp < 65536.0F) {
    if (tmp >= 0.0F) {
      /* Outport: '<Root>/BamocarTorqueLimit' */
      rtY.BamocarTorqueLimit = (uint16_T)tmp;
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
  /* MATLAB Function 'Motor Controller Module/Output scaling CAN': '<S4>:1' */
  /* '<S4>:1:3' pos_out=int16(pos/100*32767); */
  /* '<S4>:1:4' limit_out=uint16(limit); */
  rtb_Switch = rt_roundd_snf(rtb_Switch / 100.0 * 32767.0);
  if (rtb_Switch < 32768.0) {
    /* Outport: '<Root>/BamocarTorqueOut_CAN' */
    rtY.BamocarTorqueOut_CAN = (int16_T)rtb_Switch;
  } else {
    /* Outport: '<Root>/BamocarTorqueOut_CAN' */
    rtY.BamocarTorqueOut_CAN = MAX_int16_T;
  }

  tmp = roundf(rtb_Saturation);
  if (tmp < 65536.0F) {
    /* Outport: '<Root>/BamocarCurrentLimitCAN' */
    rtY.BamocarCurrentLimitCAN = (uint16_T)tmp;
  } else {
    /* Outport: '<Root>/BamocarCurrentLimitCAN' */
    rtY.BamocarCurrentLimitCAN = MAX_uint16_T;
  }

  /* End of MATLAB Function: '<S1>/Output scaling CAN' */

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

  /* Gateway: Motor Controller Module/TS activation */
  /* During: Motor Controller Module/TS activation */
  if (rtDW.bitsForTID0.is_active_c11_Motor == 0U) {
    /* Entry: Motor Controller Module/TS activation */
    rtDW.bitsForTID0.is_active_c11_Motor = 1U;

    /* Entry Internal: Motor Controller Module/TS activation */
    /* Transition: '<S7>:60' */
    rtDW.bitsForTID0.is_c11_Motor = IN_ERROR_RFE;

    /* Outport: '<Root>/RDY' */
    /* Entry 'ERROR_RFE': '<S7>:64' */
    /* '<S7>:64:1' RDY=false */
    rtY.RDY = false;

    /* Outport: '<Root>/PRECH' */
    /* '<S7>:64:1' precharge=false */
    rtY.PRECH = false;
  } else {
    switch (rtDW.bitsForTID0.is_c11_Motor) {
     case IN_ERROR_CAN_ADC:
      /* Outport: '<Root>/RDY' */
      rtY.RDY = false;

      /* During 'ERROR_CAN_ADC': '<S7>:65' */
      /* '<S7>:66:1' sf_internal_predicateOutput = ... */
      /* '<S7>:66:1' CAN_ST|ADC_ST; */
      if (rtU.CAN_STAT || rtU.ADC_STAT) {
        /* Transition: '<S7>:66' */
        rtDW.bitsForTID0.is_c11_Motor = IN_MOTOR_CONTROLLER_ACTIVATION;

        /* Entry Internal 'MOTOR_CONTROLLER_ACTIVATION': '<S7>:32' */
        /* Transition: '<S7>:62' */
        rtDW.bitsForTID0.is_MOTOR_CONTROLLER_ACTIVATION =
          IN_MOTOR_CONTROLLER_OFF;

        /* Outport: '<Root>/RDY' */
        /* Entry 'MOTOR_CONTROLLER_OFF': '<S7>:9' */
        /* '<S7>:9:1' RDY=false */
        rtY.RDY = false;
      }
      break;

     case IN_ERROR_RFE:
      /* Outport: '<Root>/RDY' */
      rtY.RDY = false;

      /* Outport: '<Root>/PRECH' */
      rtY.PRECH = false;

      /* During 'ERROR_RFE': '<S7>:64' */
      /* '<S7>:67:1' sf_internal_predicateOutput = ... */
      /* '<S7>:67:1' CAN_ST&ADC_ST&RFE; */
      if (rtU.CAN_STAT && rtU.ADC_STAT && rtU.RFE) {
        /* Transition: '<S7>:67' */
        rtDW.bitsForTID0.is_c11_Motor = IN_PRECHARGE;

        /* Entry Internal 'PRECHARGE': '<S7>:59' */
        /* Transition: '<S7>:69' */
        rtDW.bitsForTID0.is_PRECHARGE = IN_INITIAL;
      }
      break;

     case IN_MOTOR_CONTROLLER_ACTIVATION:
      /* During 'MOTOR_CONTROLLER_ACTIVATION': '<S7>:32' */
      /* '<S7>:58:1' sf_internal_predicateOutput = ... */
      /* '<S7>:58:1' ~CAN_ST|~ADC_ST; */
      if ((!rtU.CAN_STAT) || (!rtU.ADC_STAT)) {
        /* Transition: '<S7>:58' */
        /* Exit Internal 'MOTOR_CONTROLLER_ACTIVATION': '<S7>:32' */
        rtDW.bitsForTID0.is_MOTOR_CONTROLLER_ACTIVATION = IN_NO_ACTIVE_CHILD;
        rtDW.bitsForTID0.is_c11_Motor = IN_ERROR_CAN_ADC;

        /* Outport: '<Root>/RDY' */
        /* Entry 'ERROR_CAN_ADC': '<S7>:65' */
        /* '<S7>:65:1' RDY=false */
        rtY.RDY = false;
      } else {
        switch (rtDW.bitsForTID0.is_MOTOR_CONTROLLER_ACTIVATION) {
         case IN_MOTOR_CONTROLLER_OFF:
          /* Outport: '<Root>/RDY' */
          rtY.RDY = false;

          /* During 'MOTOR_CONTROLLER_OFF': '<S7>:9' */
          /* '<S7>:47:1' sf_internal_predicateOutput = ... */
          /* '<S7>:47:1' brake_vol>BrakeVolMotorControllerOnThr & start; */
          if ((rtU.BrakeEncoder > rtP.BrakeVolMotorControllerOnThr) && rtU.START)
          {
            /* Transition: '<S7>:47' */
            rtDW.bitsForTID0.is_MOTOR_CONTROLLER_ACTIVATION =
              IN_MOTOR_CONTROLLER_ON_CHECK;
            rtDW.temporalCounter_i1 = 0U;
          }
          break;

         case IN_MOTOR_CONTROLLER_OFF_CHECK:
          /* During 'MOTOR_CONTROLLER_OFF_CHECK': '<S7>:25' */
          /* '<S7>:41:1' sf_internal_predicateOutput = ... */
          /* '<S7>:41:1' (after(CheckTimeout,msec)) && (start); */
          if ((rtDW.temporalCounter_i1 * 50U >= rtP.CheckTimeout) && rtU.START)
          {
            /* Transition: '<S7>:41' */
            rtDW.bitsForTID0.is_MOTOR_CONTROLLER_ACTIVATION =
              IN_MOTOR_CONTROLLER_OFF_CHECK_1;
          } else {
            /* '<S7>:52:1' sf_internal_predicateOutput = ... */
            /* '<S7>:52:1' ~start; */
            if (!rtU.START) {
              /* Transition: '<S7>:52' */
              rtDW.bitsForTID0.is_MOTOR_CONTROLLER_ACTIVATION =
                IN_MOTOR_CONTROLLER_ON;

              /* Outport: '<Root>/RDY' */
              /* Entry 'MOTOR_CONTROLLER_ON': '<S7>:13' */
              /* '<S7>:13:1' RDY=true */
              rtY.RDY = true;
            }
          }
          break;

         case IN_MOTOR_CONTROLLER_OFF_CHECK_1:
          /* During 'MOTOR_CONTROLLER_OFF_CHECK_1': '<S7>:40' */
          /* '<S7>:49:1' sf_internal_predicateOutput = ... */
          /* '<S7>:49:1' ~start; */
          if (!rtU.START) {
            /* Transition: '<S7>:49' */
            rtDW.bitsForTID0.is_MOTOR_CONTROLLER_ACTIVATION =
              IN_MOTOR_CONTROLLER_OFF;

            /* Outport: '<Root>/RDY' */
            /* Entry 'MOTOR_CONTROLLER_OFF': '<S7>:9' */
            /* '<S7>:9:1' RDY=false */
            rtY.RDY = false;
          }
          break;

         case IN_MOTOR_CONTROLLER_ON:
          /* Outport: '<Root>/RDY' */
          rtY.RDY = true;

          /* During 'MOTOR_CONTROLLER_ON': '<S7>:13' */
          /* '<S7>:26:1' sf_internal_predicateOutput = ... */
          /* '<S7>:26:1' start; */
          if (rtU.START) {
            /* Transition: '<S7>:26' */
            rtDW.bitsForTID0.is_MOTOR_CONTROLLER_ACTIVATION =
              IN_MOTOR_CONTROLLER_OFF_CHECK;
            rtDW.temporalCounter_i1 = 0U;
          }
          break;

         case IN_MOTOR_CONTROLLER_ON_CHECK:
          /* During 'MOTOR_CONTROLLER_ON_CHECK': '<S7>:46' */
          /* '<S7>:48:1' sf_internal_predicateOutput = ... */
          /* '<S7>:48:1' (after(CheckTimeout,msec)) && (brake_vol>BrakeVolMotorControllerOnThr & start); */
          if ((rtDW.temporalCounter_i1 * 50U >= rtP.CheckTimeout) &&
              ((rtU.BrakeEncoder > rtP.BrakeVolMotorControllerOnThr) &&
               rtU.START)) {
            /* Transition: '<S7>:48' */
            rtDW.bitsForTID0.is_MOTOR_CONTROLLER_ACTIVATION =
              IN_MOTOR_CONTROLLER_ON_CHECK1;
          } else {
            /* '<S7>:50:1' sf_internal_predicateOutput = ... */
            /* '<S7>:50:1' ~start; */
            if (!rtU.START) {
              /* Transition: '<S7>:50' */
              rtDW.bitsForTID0.is_MOTOR_CONTROLLER_ACTIVATION =
                IN_MOTOR_CONTROLLER_OFF;

              /* Outport: '<Root>/RDY' */
              /* Entry 'MOTOR_CONTROLLER_OFF': '<S7>:9' */
              /* '<S7>:9:1' RDY=false */
              rtY.RDY = false;
            }
          }
          break;

         default:
          /* During 'MOTOR_CONTROLLER_ON_CHECK1': '<S7>:21' */
          /* '<S7>:23:1' sf_internal_predicateOutput = ... */
          /* '<S7>:23:1' ~start; */
          if (!rtU.START) {
            /* Transition: '<S7>:23' */
            rtDW.bitsForTID0.is_MOTOR_CONTROLLER_ACTIVATION =
              IN_MOTOR_CONTROLLER_ON;

            /* Outport: '<Root>/RDY' */
            /* Entry 'MOTOR_CONTROLLER_ON': '<S7>:13' */
            /* '<S7>:13:1' RDY=true */
            rtY.RDY = true;
          }
          break;
        }
      }
      break;

     default:
      /* During 'PRECHARGE': '<S7>:59' */
      /* '<S7>:68:1' sf_internal_predicateOutput = ... */
      /* '<S7>:68:1' ~CAN_ST | ~ADC_ST | ~RFE; */
      if ((!rtU.CAN_STAT) || (!rtU.ADC_STAT) || (!rtU.RFE)) {
        /* Transition: '<S7>:68' */
        /* Exit Internal 'PRECHARGE': '<S7>:59' */
        rtDW.bitsForTID0.is_PRECHARGE = IN_NO_ACTIVE_CHILD;
        rtDW.bitsForTID0.is_c11_Motor = IN_ERROR_RFE;

        /* Outport: '<Root>/RDY' */
        /* Entry 'ERROR_RFE': '<S7>:64' */
        /* '<S7>:64:1' RDY=false */
        rtY.RDY = false;

        /* Outport: '<Root>/PRECH' */
        /* '<S7>:64:1' precharge=false */
        rtY.PRECH = false;
      } else {
        switch (rtDW.bitsForTID0.is_PRECHARGE) {
         case IN_INITIAL:
          /* During 'INITIAL': '<S7>:1' */
          /* '<S7>:8:1' sf_internal_predicateOutput = ... */
          /* '<S7>:8:1' voltage>PrechargeVolThr; */
          if (rtb_uDLookupTable1 > rtP.PrechargeVolThr) {
            /* Transition: '<S7>:8' */
            rtDW.bitsForTID0.is_PRECHARGE = IN_PRECHARGE_CHECK;
            rtDW.temporalCounter_i1 = 0U;
          }
          break;

         case IN_PRECHARGE_CHECK:
          /* During 'PRECHARGE_CHECK': '<S7>:7' */
          /* '<S7>:10:1' sf_internal_predicateOutput = ... */
          /* '<S7>:10:1' (after(CheckTimeout,msec)) && (voltage>PrechargeVolThr); */
          if ((rtDW.temporalCounter_i1 * 50U >= rtP.CheckTimeout) &&
              (rtb_uDLookupTable1 > rtP.PrechargeVolThr)) {
            /* Transition: '<S7>:10' */
            rtDW.bitsForTID0.is_PRECHARGE = IN_PRECHARGE_ON;

            /* Outport: '<Root>/PRECH' */
            /* Entry 'PRECHARGE_ON': '<S7>:61' */
            /* '<S7>:61:1' precharge=true */
            rtY.PRECH = true;
          }
          break;

         default:
          /* Outport: '<Root>/PRECH' */
          rtY.PRECH = true;

          /* During 'PRECHARGE_ON': '<S7>:61' */
          /* Transition: '<S7>:63' */
          rtDW.bitsForTID0.is_PRECHARGE = IN_NO_ACTIVE_CHILD;
          rtDW.bitsForTID0.is_c11_Motor = IN_MOTOR_CONTROLLER_ACTIVATION;

          /* Entry Internal 'MOTOR_CONTROLLER_ACTIVATION': '<S7>:32' */
          /* Transition: '<S7>:62' */
          rtDW.bitsForTID0.is_MOTOR_CONTROLLER_ACTIVATION =
            IN_MOTOR_CONTROLLER_OFF;

          /* Outport: '<Root>/RDY' */
          /* Entry 'MOTOR_CONTROLLER_OFF': '<S7>:9' */
          /* '<S7>:9:1' RDY=false */
          rtY.RDY = false;
          break;
        }
      }
      break;
    }
  }

  /* End of Chart: '<S1>/TS activation' */
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

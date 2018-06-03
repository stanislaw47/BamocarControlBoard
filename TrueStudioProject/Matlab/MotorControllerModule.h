/*
 * Sponsored License - for use in support of a program or activity
 * sponsored by MathWorks.  Not for government, commercial or other
 * non-sponsored organizational use.
 *
 * File: MotorControllerModule.h
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

#ifndef RTW_HEADER_MotorControllerModule_h_
#define RTW_HEADER_MotorControllerModule_h_
#include "rtwtypes.h"
#include <math.h>
#ifndef MotorControllerModule_COMMON_INCLUDES_
# define MotorControllerModule_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* MotorControllerModule_COMMON_INCLUDES_ */

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

/* Block signals and states (auto storage) for system '<Root>' */
typedef struct {
  real32_T pos;                        /* '<S1>/TorqueValueGeneration' */
  uint32_T temporalCounter_i1;         /* '<S1>/TorqueValueGeneration' */
  uint32_T temporalCounter_i1_b;       /* '<S1>/TS activation' */
  uint8_T is_active_c17_MotorControllerMo;/* '<S1>/VoltageCheck' */
  uint8_T is_c17_MotorControllerModule;/* '<S1>/VoltageCheck' */
  uint8_T is_A1;                       /* '<S1>/VoltageCheck' */
  uint8_T is_active_A1;                /* '<S1>/VoltageCheck' */
  uint8_T is_A2;                       /* '<S1>/VoltageCheck' */
  uint8_T is_active_A2;                /* '<S1>/VoltageCheck' */
  uint8_T is_B;                        /* '<S1>/VoltageCheck' */
  uint8_T is_active_B;                 /* '<S1>/VoltageCheck' */
  uint8_T is_V;                        /* '<S1>/VoltageCheck' */
  uint8_T is_active_V;                 /* '<S1>/VoltageCheck' */
  uint8_T is_active_c16_MotorControllerMo;/* '<S1>/TorqueValueGeneration' */
  uint8_T is_c16_MotorControllerModule;/* '<S1>/TorqueValueGeneration' */
  uint8_T is_active_c15_MotorControllerMo;/* '<S1>/TS activation' */
  uint8_T is_c15_MotorControllerModule;/* '<S1>/TS activation' */
  uint8_T is_active_c13_MotorControllerMo;/* '<S1>/PlausibilityCheck' */
  uint8_T is_APPS_PlausibilityCheck_EV2_3;/* '<S1>/PlausibilityCheck' */
  uint8_T is_BSE_PlausiblilityCheck_EV2_5;/* '<S1>/PlausibilityCheck' */
  boolean_T voltage_status;            /* '<S1>/VoltageCheck' */
} DW;

/* External inputs (root inport signals with auto storage) */
typedef struct {
  uint16_T APPS1;                      /* '<Root>/APPS1' */
  uint16_T APPS2;                      /* '<Root>/APPS2' */
  uint16_T BrakeEncoder;               /* '<Root>/BrakeEncoder' */
  uint16_T Voltage;                    /* '<Root>/Voltage' */
  boolean_T RFE;                       /* '<Root>/RFE' */
  boolean_T START;                     /* '<Root>/START' */
} ExtU;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  uint16_T BamocarTorqueOut;           /* '<Root>/BamocarTorqueOut' */
  uint16_T BamocarTorqueLimit;         /* '<Root>/BamocarTorqueLimit' */
  uint16_T BamocarTorqueOut_CAN;       /* '<Root>/BamocarTorqueOut_CAN' */
  uint16_T BamocarCurrentLimitCAN;     /* '<Root>/BamocarCurrentLimitCAN' */
  boolean_T RDY;                       /* '<Root>/RDY' */
  boolean_T PRECH;                     /* '<Root>/PRECH' */
} ExtY;

/* Parameters (auto storage) */
struct P_ {
  real_T AnSigRange;                   /* Variable: AnSigRange
                                        * Referenced by: '<S2>/MATLAB Function'
                                        */
  real_T ImaxEff;                      /* Variable: ImaxEff
                                        * Referenced by: '<S1>/current reduction'
                                        */
  real32_T A1_DoLim;                   /* Variable: A1_DoLim
                                        * Referenced by:
                                        *   '<S1>/VoltageCheck'
                                        *   '<S2>/MATLAB Function'
                                        */
  real32_T A1_UpLim;                   /* Variable: A1_UpLim
                                        * Referenced by:
                                        *   '<S1>/VoltageCheck'
                                        *   '<S2>/MATLAB Function'
                                        */
  real32_T A2_DoLim;                   /* Variable: A2_DoLim
                                        * Referenced by:
                                        *   '<S1>/VoltageCheck'
                                        *   '<S2>/MATLAB Function'
                                        */
  real32_T A2_UpLim;                   /* Variable: A2_UpLim
                                        * Referenced by:
                                        *   '<S1>/VoltageCheck'
                                        *   '<S2>/MATLAB Function'
                                        */
  real32_T APPS_OffPlausThr;           /* Variable: APPS_OffPlausThr
                                        * Referenced by: '<S1>/PlausibilityCheck'
                                        */
  real32_T APPS_OnPlausThr;            /* Variable: APPS_OnPlausThr
                                        * Referenced by: '<S1>/PlausibilityCheck'
                                        */
  real32_T APPS_OnPosThr;              /* Variable: APPS_OnPosThr
                                        * Referenced by: '<S1>/PlausibilityCheck'
                                        */
  real32_T BSE_PlausThr;               /* Variable: BSE_PlausThr
                                        * Referenced by: '<S1>/PlausibilityCheck'
                                        */
  real32_T B_DoLim;                    /* Variable: B_DoLim
                                        * Referenced by: '<S1>/VoltageCheck'
                                        */
  real32_T B_UpLim;                    /* Variable: B_UpLim
                                        * Referenced by: '<S1>/VoltageCheck'
                                        */
  real32_T BrakeVolMotorControllerOnThr;/* Variable: BrakeVolMotorControllerOnThr
                                         * Referenced by: '<S1>/TS activation'
                                         */
  real32_T LimitBufferOutMaxVoltage;   /* Variable: LimitBufferOutMaxVoltage
                                        * Referenced by:
                                        *   '<S1>/Output scaling'
                                        *   '<S1>/Output scaling CAN'
                                        */
  real32_T PlausWait;                  /* Variable: PlausWait
                                        * Referenced by: '<S1>/TorqueValueGeneration'
                                        */
  real32_T PosBufferOutMaxVoltage;     /* Variable: PosBufferOutMaxVoltage
                                        * Referenced by:
                                        *   '<S1>/Output scaling'
                                        *   '<S1>/Output scaling CAN'
                                        */
  real32_T PosDiffThreshold;           /* Variable: PosDiffThreshold
                                        * Referenced by: '<S1>/PlausibilityCheck'
                                        */
  real32_T PowerSafetyThr;             /* Variable: PowerSafetyThr
                                        * Referenced by: '<S1>/current reduction'
                                        */
  real32_T PrechargeVolThr;            /* Variable: PrechargeVolThr
                                        * Referenced by: '<S1>/TS activation'
                                        */
  real32_T VolOffsetOff;               /* Variable: VolOffsetOff
                                        * Referenced by: '<S1>/VoltageCheck'
                                        */
  real32_T VolOffsetOn;                /* Variable: VolOffsetOn
                                        * Referenced by: '<S1>/VoltageCheck'
                                        */
  uint16_T CheckTimeout;               /* Variable: CheckTimeout
                                        * Referenced by: '<S1>/TS activation'
                                        */
};

/* Parameters (auto storage) */
typedef struct P_ P;

/* Real-time Model Data Structure */
struct tag_RTM {
  const char_T * volatile errorStatus;
};

/* Block parameters (auto storage) */
extern P rtP;

/* Block signals and states (auto storage) */
extern DW rtDW;

/* External inputs (root inport signals with auto storage) */
extern ExtU rtU;

/* External outputs (root outports fed by signals with auto storage) */
extern ExtY rtY;

/* Model entry point functions */
extern void MotorControllerModule_initialize(void);
extern void MotorControllerModule_step(void)  __attribute__((section(".ccmram")));

/* Real-time Model object */
extern RT_MODEL *const rtM;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S1>/Data Type Conversion' : Eliminate redundant data type conversion
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Note that this particular code originates from a subsystem build,
 * and has its own system numbers different from the parent model.
 * Refer to the system hierarchy for this subsystem below, and use the
 * MATLAB hilite_system command to trace the generated code back
 * to the parent model.  For example,
 *
 * hilite_system('motor_controller_module_simulation/MotorControllerModule')    - opens subsystem motor_controller_module_simulation/MotorControllerModule
 * hilite_system('motor_controller_module_simulation/MotorControllerModule/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'motor_controller_module_simulation'
 * '<S1>'   : 'motor_controller_module_simulation/MotorControllerModule'
 * '<S2>'   : 'motor_controller_module_simulation/MotorControllerModule/Input Scaling'
 * '<S3>'   : 'motor_controller_module_simulation/MotorControllerModule/MATLAB Function'
 * '<S4>'   : 'motor_controller_module_simulation/MotorControllerModule/Output scaling'
 * '<S5>'   : 'motor_controller_module_simulation/MotorControllerModule/Output scaling CAN'
 * '<S6>'   : 'motor_controller_module_simulation/MotorControllerModule/PlausibilityCheck'
 * '<S7>'   : 'motor_controller_module_simulation/MotorControllerModule/TS activation'
 * '<S8>'   : 'motor_controller_module_simulation/MotorControllerModule/TorqueValueGeneration'
 * '<S9>'   : 'motor_controller_module_simulation/MotorControllerModule/VoltageCheck'
 * '<S10>'  : 'motor_controller_module_simulation/MotorControllerModule/current reduction'
 * '<S11>'  : 'motor_controller_module_simulation/MotorControllerModule/Input Scaling/MATLAB Function'
 */
#endif                                 /* RTW_HEADER_MotorControllerModule_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

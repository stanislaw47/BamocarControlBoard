/*
 * Sponsored License - for use in support of a program or activity
 * sponsored by MathWorks.  Not for government, commercial or other
 * non-sponsored organizational use.
 *
 * File: Motor.h
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

#ifndef RTW_HEADER_Motor_h_
#define RTW_HEADER_Motor_h_
#include "rtwtypes.h"
#include <math.h>
#ifndef Motor_COMMON_INCLUDES_
# define Motor_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* Motor_COMMON_INCLUDES_ */

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

#ifndef DEFINED_TYPEDEF_FOR_A1_scalingData_
#define DEFINED_TYPEDEF_FOR_A1_scalingData_

typedef struct {
  uint16_T BP1[2];
  real32_T Table[2];
} A1_scalingData;

#endif

#ifndef DEFINED_TYPEDEF_FOR_A2_scalingData_
#define DEFINED_TYPEDEF_FOR_A2_scalingData_

typedef struct {
  uint16_T BP1[2];
  real32_T Table[2];
} A2_scalingData;

#endif

#ifndef DEFINED_TYPEDEF_FOR_TorqueScalingData_
#define DEFINED_TYPEDEF_FOR_TorqueScalingData_

typedef struct {
  real_T BP1[3];
  real_T Table[3];
} TorqueScalingData;

#endif

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  uint32_T m_bpIndex;                  /* '<S2>/1-D Lookup Table' */
  uint32_T m_bpIndex_d;                /* '<S2>/1-D Lookup Table1' */
  uint32_T m_bpIndex_l;                /* '<S10>/1-D Lookup Table' */
  uint32_T m_bpIndex_dn;               /* '<S11>/1-D Lookup Table' */
  uint32_T temporalCounter_i1;         /* '<S1>/TS activation' */
  uint32_T temporalCounter_i1_p;       /* '<S1>/PlausibilityHandling' */
  uint8_T is_active_c12_Motor;         /* '<S1>/VoltageCheck' */
  uint8_T is_c12_Motor;                /* '<S1>/VoltageCheck' */
  uint8_T is_A1;                       /* '<S1>/VoltageCheck' */
  uint8_T is_active_A1;                /* '<S1>/VoltageCheck' */
  uint8_T is_A2;                       /* '<S1>/VoltageCheck' */
  uint8_T is_active_A2;                /* '<S1>/VoltageCheck' */
  uint8_T is_B;                        /* '<S1>/VoltageCheck' */
  uint8_T is_active_B;                 /* '<S1>/VoltageCheck' */
  uint8_T is_V;                        /* '<S1>/VoltageCheck' */
  uint8_T is_active_V;                 /* '<S1>/VoltageCheck' */
  uint8_T is_active_c11_Motor;         /* '<S1>/TS activation' */
  uint8_T is_c11_Motor;                /* '<S1>/TS activation' */
  uint8_T is_PRECHARGE;                /* '<S1>/TS activation' */
  uint8_T is_MOTOR_CONTROLLER_ACTIVATION;/* '<S1>/TS activation' */
  uint8_T is_active_c8_Motor;          /* '<S1>/PlausibilityHandling' */
  uint8_T is_c8_Motor;                 /* '<S1>/PlausibilityHandling' */
  uint8_T is_active_c7_Motor;          /* '<S1>/PlausibilityCheck' */
  uint8_T is_APPS_PlausibilityCheck_EV2_3;/* '<S1>/PlausibilityCheck' */
  uint8_T is_BSE_PlausiblilityCheck_EV2_5;/* '<S1>/PlausibilityCheck' */
} DW;

/* Constant parameters (default storage) */
typedef struct {
  /* Computed Parameter: uDLookupTable_tableData
   * Referenced by: '<S10>/1-D Lookup Table'
   */
  real32_T uDLookupTable_tableData[2];

  /* Computed Parameter: uDLookupTable_bp01Data
   * Referenced by: '<S10>/1-D Lookup Table'
   */
  uint16_T uDLookupTable_bp01Data[2];
} ConstP;

/* External inputs (root inport signals with default storage) */
typedef struct {
  uint16_T APPS1;                      /* '<Root>/APPS1' */
  uint16_T APPS2;                      /* '<Root>/APPS2' */
  uint16_T BrakeEncoder;               /* '<Root>/BrakeEncoder' */
  uint16_T Voltage;                    /* '<Root>/Voltage' */
  boolean_T RFE;                       /* '<Root>/RFE' */
  boolean_T START;                     /* '<Root>/START' */
  boolean_T CAN_STAT;                  /* '<Root>/CAN_STAT' */
  boolean_T ADC_STAT;                  /* '<Root>/ADC_STAT' */
  uint16_T speed;                      /* '<Root>/speed' */
} ExtU;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  uint16_T BamocarTorqueOut;           /* '<Root>/BamocarTorqueOut' */
  uint16_T BamocarTorqueLimit;         /* '<Root>/BamocarTorqueLimit' */
  int16_T BamocarTorqueOut_CAN;        /* '<Root>/BamocarTorqueOut_CAN' */
  uint16_T BamocarCurrentLimitCAN;     /* '<Root>/BamocarCurrentLimitCAN' */
  boolean_T RDY;                       /* '<Root>/RDY' */
  boolean_T PRECH;                     /* '<Root>/PRECH' */
  boolean_T VolStat;                   /* '<Root>/VolStat' */
  boolean_T APPS_PlausStat;            /* '<Root>/APPS_PlausStat' */
  boolean_T BSE_PlausStat;             /* '<Root>/BSE_PlausStat' */
  real32_T pos1;                       /* '<Root>/pos1' */
  real32_T pos2;                       /* '<Root>/pos2' */
} ExtY;

/* Parameters (default storage) */
struct P_ {
  TorqueScalingData Torque;            /* Variable: Torque
                                        * Referenced by: '<S11>/1-D Lookup Table'
                                        */
  A1_scalingData A1_scaling;           /* Variable: A1_scaling
                                        * Referenced by: '<S2>/1-D Lookup Table'
                                        */
  A2_scalingData A2_scaling;           /* Variable: A2_scaling
                                        * Referenced by: '<S2>/1-D Lookup Table1'
                                        */
  real_T ImaxEff;                      /* Variable: ImaxEff
                                        * Referenced by: '<S10>/current reduction'
                                        */
  real32_T APPS_OffPlausThr;           /* Variable: APPS_OffPlausThr
                                        * Referenced by: '<S1>/PlausibilityCheck'
                                        */
  real32_T APPS_OnPlausThr;            /* Variable: APPS_OnPlausThr
                                        * Referenced by: '<S1>/PlausibilityCheck'
                                        */
  real32_T LimitBufferOutMaxVoltage;   /* Variable: LimitBufferOutMaxVoltage
                                        * Referenced by:
                                        *   '<S1>/Output scaling'
                                        *   '<S1>/Output scaling CAN'
                                        */
  real32_T PlausWait;                  /* Variable: PlausWait
                                        * Referenced by: '<S1>/PlausibilityHandling'
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
                                        * Referenced by: '<S10>/current reduction'
                                        */
  real32_T PrechargeVolThr;            /* Variable: PrechargeVolThr
                                        * Referenced by: '<S1>/TS activation'
                                        */
  uint16_T A1_DoLim;                   /* Variable: A1_DoLim
                                        * Referenced by: '<S1>/VoltageCheck'
                                        */
  uint16_T A1_UpLim;                   /* Variable: A1_UpLim
                                        * Referenced by: '<S1>/VoltageCheck'
                                        */
  uint16_T A2_DoLim;                   /* Variable: A2_DoLim
                                        * Referenced by: '<S1>/VoltageCheck'
                                        */
  uint16_T A2_UpLim;                   /* Variable: A2_UpLim
                                        * Referenced by: '<S1>/VoltageCheck'
                                        */
  uint16_T BSE_PlausThr;               /* Variable: BSE_PlausThr
                                        * Referenced by: '<S1>/PlausibilityCheck'
                                        */
  uint16_T B_DoLim;                    /* Variable: B_DoLim
                                        * Referenced by: '<S1>/VoltageCheck'
                                        */
  uint16_T B_UpLim;                    /* Variable: B_UpLim
                                        * Referenced by: '<S1>/VoltageCheck'
                                        */
  uint16_T BrakeVolMotorControllerOnThr;/* Variable: BrakeVolMotorControllerOnThr
                                         * Referenced by: '<S1>/TS activation'
                                         */
  uint16_T CheckTimeout;               /* Variable: CheckTimeout
                                        * Referenced by: '<S1>/TS activation'
                                        */
  uint16_T RegBrakingSpeedThr;         /* Variable: RegBrakingSpeedThr
                                        * Referenced by: '<S11>/Switch'
                                        */
  uint16_T VolOffsetOff;               /* Variable: VolOffsetOff
                                        * Referenced by: '<S1>/VoltageCheck'
                                        */
  uint16_T VolOffsetOn;                /* Variable: VolOffsetOn
                                        * Referenced by: '<S1>/VoltageCheck'
                                        */
};

/* Parameters (default storage) */
typedef struct P_ P;

/* Real-time Model Data Structure */
struct tag_RTM {
  const char_T * volatile errorStatus;
};

/* Block parameters (default storage) */
extern P rtP;

/* Block signals and states (default storage) */
extern DW rtDW;

/* External inputs (root inport signals with default storage) */
extern ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY rtY;

/* Constant parameters (default storage) */
extern const ConstP rtConstP;

/* Model entry point functions */
extern void Motor_initialize(void);
extern void Motor_step(void);

/* Real-time Model object */
extern RT_MODEL *const rtM;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S12>/Data Type Duplicate' : Unused code path elimination
 * Block '<S12>/Data Type Propagation' : Unused code path elimination
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
 * hilite_system('motor_controller_module_simulation/Motor Controller Module')    - opens subsystem motor_controller_module_simulation/Motor Controller Module
 * hilite_system('motor_controller_module_simulation/Motor Controller Module/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'motor_controller_module_simulation'
 * '<S1>'   : 'motor_controller_module_simulation/Motor Controller Module'
 * '<S2>'   : 'motor_controller_module_simulation/Motor Controller Module/Input Scaling'
 * '<S3>'   : 'motor_controller_module_simulation/Motor Controller Module/Output scaling'
 * '<S4>'   : 'motor_controller_module_simulation/Motor Controller Module/Output scaling CAN'
 * '<S5>'   : 'motor_controller_module_simulation/Motor Controller Module/PlausibilityCheck'
 * '<S6>'   : 'motor_controller_module_simulation/Motor Controller Module/PlausibilityHandling'
 * '<S7>'   : 'motor_controller_module_simulation/Motor Controller Module/TS activation'
 * '<S8>'   : 'motor_controller_module_simulation/Motor Controller Module/TorqueValueGeneration'
 * '<S9>'   : 'motor_controller_module_simulation/Motor Controller Module/VoltageCheck'
 * '<S10>'  : 'motor_controller_module_simulation/Motor Controller Module/current_reduction&voltage_scaling'
 * '<S11>'  : 'motor_controller_module_simulation/Motor Controller Module/TorqueValueGeneration/regenerative braking'
 * '<S12>'  : 'motor_controller_module_simulation/Motor Controller Module/TorqueValueGeneration/regenerative braking/Saturation Dynamic'
 * '<S13>'  : 'motor_controller_module_simulation/Motor Controller Module/current_reduction&voltage_scaling/current reduction'
 */

/*-
 * Requirements for '<Root>': Motor
 */
#endif                                 /* RTW_HEADER_Motor_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

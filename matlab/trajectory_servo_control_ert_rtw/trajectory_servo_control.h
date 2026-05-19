/*
 * File: trajectory_servo_control.h
 *
 * Code generated for Simulink model 'trajectory_servo_control'.
 *
 * Model version                  : 1.4
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Mon May 18 10:21:15 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef trajectory_servo_control_h_
#define trajectory_servo_control_h_
#ifndef trajectory_servo_control_COMMON_INCLUDES_
#define trajectory_servo_control_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_extmode.h"
#include "sysran_types.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "MW_arduino_digitalio.h"
#include "MW_ServoWriteRead.h"
#endif                           /* trajectory_servo_control_COMMON_INCLUDES_ */

#include "trajectory_servo_control_types.h"
#include <stddef.h>

/* Macros for accessing real-time model data structure */
#ifndef rtmGetFinalTime
#define rtmGetFinalTime(rtm)           ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetRTWExtModeInfo
#define rtmGetRTWExtModeInfo(rtm)      ((rtm)->extModeInfo)
#endif

#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmStepTask
#define rtmStepTask(rtm, idx)          ((rtm)->Timing.TaskCounters.TID[(idx)] == 0)
#endif

#ifndef rtmGetStopRequested
#define rtmGetStopRequested(rtm)       ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
#define rtmSetStopRequested(rtm, val)  ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
#define rtmGetStopRequestedPtr(rtm)    (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
#define rtmGetT(rtm)                   ((rtm)->Timing.taskTime0)
#endif

#ifndef rtmGetTFinal
#define rtmGetTFinal(rtm)              ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                (&(rtm)->Timing.taskTime0)
#endif

#ifndef rtmTaskCounter
#define rtmTaskCounter(rtm, idx)       ((rtm)->Timing.TaskCounters.TID[(idx)])
#endif

/* Block states (default storage) for system '<Root>' */
typedef struct {
  codertarget_arduinobase_block_T obj; /* '<Root>/Digital Output1' */
  codertarget_arduinobase_block_T obj_m;/* '<Root>/Digital Output' */
  codertarget_arduinobase_inter_T obj_j;/* '<Root>/Standard Servo Write4' */
  codertarget_arduinobase_inter_T obj_i;/* '<Root>/Standard Servo Write3' */
  codertarget_arduinobase_inter_T obj_l;/* '<Root>/Standard Servo Write2' */
  codertarget_arduinobase_inter_T obj_jv;/* '<Root>/Standard Servo Write1' */
  codertarget_arduinobase_inter_T obj_p;/* '<Root>/Standard Servo Write' */
  real_T last_angle;                   /* '<Root>/MATLAB Function' */
  int32_T count;                       /* '<Root>/MATLAB Function' */
  int32_T target;                      /* '<Root>/MATLAB Function' */
  uint16_T Output_DSTATE;              /* '<S10>/Output' */
  uint16_T Output_DSTATE_n;            /* '<S13>/Output' */
  uint16_T Output_DSTATE_b;            /* '<S16>/Output' */
  uint16_T Output_DSTATE_f;            /* '<S7>/Output' */
  uint16_T Output_DSTATE_g;            /* '<S19>/Output' */
  boolean_T pulse_phase;               /* '<Root>/MATLAB Function' */
} DW_trajectory_servo_control_T;

/* Parameters (default storage) */
struct P_trajectory_servo_control_T_ {
  real_T pj1[8];                       /* Variable: pj1
                                        * Referenced by: '<S6>/Lookup'
                                        */
  real_T pj2[8];                       /* Variable: pj2
                                        * Referenced by: '<S2>/Lookup'
                                        */
  real_T pj3[8];                       /* Variable: pj3
                                        * Referenced by: '<S3>/Lookup'
                                        */
  real_T pj4[8];                       /* Variable: pj4
                                        * Referenced by: '<S4>/Lookup'
                                        */
  real_T pj5[8];                       /* Variable: pj5
                                        * Referenced by: '<S5>/Lookup'
                                        */
  real_T RepeatingSequenceInterpolated1_[8];
                              /* Mask Parameter: RepeatingSequenceInterpolated1_
                               * Referenced by: '<S3>/Lookup'
                               */
  real_T RepeatingSequenceInterpolated2_[8];
                              /* Mask Parameter: RepeatingSequenceInterpolated2_
                               * Referenced by: '<S4>/Lookup'
                               */
  real_T RepeatingSequenceInterpolated3_[8];
                              /* Mask Parameter: RepeatingSequenceInterpolated3_
                               * Referenced by: '<S5>/Lookup'
                               */
  real_T RepeatingSequenceInterpolated_T[8];
                              /* Mask Parameter: RepeatingSequenceInterpolated_T
                               * Referenced by: '<S2>/Lookup'
                               */
  real_T RepeatingSequenceInterpolated4_[8];
                              /* Mask Parameter: RepeatingSequenceInterpolated4_
                               * Referenced by: '<S6>/Lookup'
                               */
  uint16_T WrapToZero_Threshold;       /* Mask Parameter: WrapToZero_Threshold
                                        * Referenced by: '<S12>/FixPt Switch'
                                        */
  uint16_T WrapToZero_Threshold_e;     /* Mask Parameter: WrapToZero_Threshold_e
                                        * Referenced by: '<S15>/FixPt Switch'
                                        */
  uint16_T WrapToZero_Threshold_j;     /* Mask Parameter: WrapToZero_Threshold_j
                                        * Referenced by: '<S18>/FixPt Switch'
                                        */
  uint16_T WrapToZero_Threshold_c;     /* Mask Parameter: WrapToZero_Threshold_c
                                        * Referenced by: '<S9>/FixPt Switch'
                                        */
  uint16_T WrapToZero_Threshold_ch;   /* Mask Parameter: WrapToZero_Threshold_ch
                                       * Referenced by: '<S21>/FixPt Switch'
                                       */
  real_T SampleTimeMath_WtEt;         /* Computed Parameter: SampleTimeMath_WtEt
                                       * Referenced by: '<S3>/Sample Time Math'
                                       */
  real_T AddConstant_Bias;             /* Expression: 85
                                        * Referenced by: '<Root>/Add Constant'
                                        */
  real_T SampleTimeMath_WtEt_i;     /* Computed Parameter: SampleTimeMath_WtEt_i
                                     * Referenced by: '<S4>/Sample Time Math'
                                     */
  real_T AddConstant1_Bias;            /* Expression: -180
                                        * Referenced by: '<Root>/Add Constant1'
                                        */
  real_T SampleTimeMath_WtEt_c;     /* Computed Parameter: SampleTimeMath_WtEt_c
                                     * Referenced by: '<S5>/Sample Time Math'
                                     */
  real_T AddConstant3_Bias;            /* Expression: -42.3
                                        * Referenced by: '<Root>/Add Constant3'
                                        */
  real_T SampleTimeMath_WtEt_l;     /* Computed Parameter: SampleTimeMath_WtEt_l
                                     * Referenced by: '<S2>/Sample Time Math'
                                     */
  real_T AddConstant4_Bias;            /* Expression: 85
                                        * Referenced by: '<Root>/Add Constant4'
                                        */
  real_T Constant_Value;               /* Expression: 41.8128505727844
                                        * Referenced by: '<Root>/Constant'
                                        */
  real_T SampleTimeMath_WtEt_lo;   /* Computed Parameter: SampleTimeMath_WtEt_lo
                                    * Referenced by: '<S6>/Sample Time Math'
                                    */
  uint16_T Constant_Value_h;           /* Computed Parameter: Constant_Value_h
                                        * Referenced by: '<S9>/Constant'
                                        */
  uint16_T Constant_Value_l;           /* Computed Parameter: Constant_Value_l
                                        * Referenced by: '<S12>/Constant'
                                        */
  uint16_T Constant_Value_e;           /* Computed Parameter: Constant_Value_e
                                        * Referenced by: '<S15>/Constant'
                                        */
  uint16_T Constant_Value_a;           /* Computed Parameter: Constant_Value_a
                                        * Referenced by: '<S18>/Constant'
                                        */
  uint16_T Constant_Value_n;           /* Computed Parameter: Constant_Value_n
                                        * Referenced by: '<S21>/Constant'
                                        */
  uint16_T Output_InitialCondition;
                                  /* Computed Parameter: Output_InitialCondition
                                   * Referenced by: '<S10>/Output'
                                   */
  uint16_T FixPtConstant_Value;       /* Computed Parameter: FixPtConstant_Value
                                       * Referenced by: '<S11>/FixPt Constant'
                                       */
  uint16_T Output_InitialCondition_g;
                                /* Computed Parameter: Output_InitialCondition_g
                                 * Referenced by: '<S13>/Output'
                                 */
  uint16_T FixPtConstant_Value_m;   /* Computed Parameter: FixPtConstant_Value_m
                                     * Referenced by: '<S14>/FixPt Constant'
                                     */
  uint16_T Output_InitialCondition_l;
                                /* Computed Parameter: Output_InitialCondition_l
                                 * Referenced by: '<S16>/Output'
                                 */
  uint16_T FixPtConstant_Value_a;   /* Computed Parameter: FixPtConstant_Value_a
                                     * Referenced by: '<S17>/FixPt Constant'
                                     */
  uint16_T Output_InitialCondition_p;
                                /* Computed Parameter: Output_InitialCondition_p
                                 * Referenced by: '<S7>/Output'
                                 */
  uint16_T FixPtConstant_Value_c;   /* Computed Parameter: FixPtConstant_Value_c
                                     * Referenced by: '<S8>/FixPt Constant'
                                     */
  uint16_T Output_InitialCondition_b;
                                /* Computed Parameter: Output_InitialCondition_b
                                 * Referenced by: '<S19>/Output'
                                 */
  uint16_T FixPtConstant_Value_b;   /* Computed Parameter: FixPtConstant_Value_b
                                     * Referenced by: '<S20>/FixPt Constant'
                                     */
};

/* Real-time Model Data Structure */
struct tag_RTM_trajectory_servo_cont_T {
  const char_T *errorStatus;
  RTWExtModeInfo *extModeInfo;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    uint32_T checksums[4];
  } Sizes;

  /*
   * SpecialInfo:
   * The following substructure contains special information
   * related to other components that are dependent on RTW.
   */
  struct {
    const void *mappingInfo;
  } SpecialInfo;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    time_T taskTime0;
    uint32_T clockTick0;
    time_T stepSize0;
    uint32_T clockTick1;
    struct {
      uint8_T TID[2];
    } TaskCounters;

    time_T tFinal;
    boolean_T stopRequestedFlag;
  } Timing;
};

/* Block parameters (default storage) */
extern P_trajectory_servo_control_T trajectory_servo_control_P;

/* Block states (default storage) */
extern DW_trajectory_servo_control_T trajectory_servo_control_DW;

/* External function called from main */
extern void trajectory_servo_control_SetEventsForThisBaseStep(boolean_T
  *eventFlags);

/* Model entry point functions */
extern void trajectory_servo_control_initialize(void);
extern void trajectory_servo_control_step0(void);
extern void trajectory_servo_control_step1(void);
extern void trajectory_servo_control_step(int_T tid);
extern void trajectory_servo_control_terminate(void);

/* Real-time Model object */
extern RT_MODEL_trajectory_servo_con_T *const trajectory_servo_control_M;
extern volatile boolean_T stopRequested;
extern volatile boolean_T runModel;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S2>/Data Type Propagation' : Unused code path elimination
 * Block '<S7>/Data Type Propagation' : Unused code path elimination
 * Block '<S8>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S9>/FixPt Data Type Duplicate1' : Unused code path elimination
 * Block '<S3>/Data Type Propagation' : Unused code path elimination
 * Block '<S10>/Data Type Propagation' : Unused code path elimination
 * Block '<S11>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S12>/FixPt Data Type Duplicate1' : Unused code path elimination
 * Block '<S4>/Data Type Propagation' : Unused code path elimination
 * Block '<S13>/Data Type Propagation' : Unused code path elimination
 * Block '<S14>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S15>/FixPt Data Type Duplicate1' : Unused code path elimination
 * Block '<S5>/Data Type Propagation' : Unused code path elimination
 * Block '<S16>/Data Type Propagation' : Unused code path elimination
 * Block '<S17>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S18>/FixPt Data Type Duplicate1' : Unused code path elimination
 * Block '<S6>/Data Type Propagation' : Unused code path elimination
 * Block '<S19>/Data Type Propagation' : Unused code path elimination
 * Block '<S20>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S21>/FixPt Data Type Duplicate1' : Unused code path elimination
 * Block '<S2>/Output' : Eliminate redundant signal conversion block
 * Block '<S3>/Output' : Eliminate redundant signal conversion block
 * Block '<S4>/Output' : Eliminate redundant signal conversion block
 * Block '<S5>/Output' : Eliminate redundant signal conversion block
 * Block '<S6>/Output' : Eliminate redundant signal conversion block
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'trajectory_servo_control'
 * '<S1>'   : 'trajectory_servo_control/MATLAB Function'
 * '<S2>'   : 'trajectory_servo_control/Repeating Sequence Interpolated'
 * '<S3>'   : 'trajectory_servo_control/Repeating Sequence Interpolated1'
 * '<S4>'   : 'trajectory_servo_control/Repeating Sequence Interpolated2'
 * '<S5>'   : 'trajectory_servo_control/Repeating Sequence Interpolated3'
 * '<S6>'   : 'trajectory_servo_control/Repeating Sequence Interpolated4'
 * '<S7>'   : 'trajectory_servo_control/Repeating Sequence Interpolated/LimitedCounter'
 * '<S8>'   : 'trajectory_servo_control/Repeating Sequence Interpolated/LimitedCounter/Increment Real World'
 * '<S9>'   : 'trajectory_servo_control/Repeating Sequence Interpolated/LimitedCounter/Wrap To Zero'
 * '<S10>'  : 'trajectory_servo_control/Repeating Sequence Interpolated1/LimitedCounter'
 * '<S11>'  : 'trajectory_servo_control/Repeating Sequence Interpolated1/LimitedCounter/Increment Real World'
 * '<S12>'  : 'trajectory_servo_control/Repeating Sequence Interpolated1/LimitedCounter/Wrap To Zero'
 * '<S13>'  : 'trajectory_servo_control/Repeating Sequence Interpolated2/LimitedCounter'
 * '<S14>'  : 'trajectory_servo_control/Repeating Sequence Interpolated2/LimitedCounter/Increment Real World'
 * '<S15>'  : 'trajectory_servo_control/Repeating Sequence Interpolated2/LimitedCounter/Wrap To Zero'
 * '<S16>'  : 'trajectory_servo_control/Repeating Sequence Interpolated3/LimitedCounter'
 * '<S17>'  : 'trajectory_servo_control/Repeating Sequence Interpolated3/LimitedCounter/Increment Real World'
 * '<S18>'  : 'trajectory_servo_control/Repeating Sequence Interpolated3/LimitedCounter/Wrap To Zero'
 * '<S19>'  : 'trajectory_servo_control/Repeating Sequence Interpolated4/LimitedCounter'
 * '<S20>'  : 'trajectory_servo_control/Repeating Sequence Interpolated4/LimitedCounter/Increment Real World'
 * '<S21>'  : 'trajectory_servo_control/Repeating Sequence Interpolated4/LimitedCounter/Wrap To Zero'
 */
#endif                                 /* trajectory_servo_control_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

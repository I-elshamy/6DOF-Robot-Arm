/*
 * File: untitled_restored_from_autosave.h
 *
 * Code generated for Simulink model 'untitled_restored_from_autosave'.
 *
 * Model version                  : 1.2
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Sun May 17 17:58:31 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef untitled_restored_from_autosave_h_
#define untitled_restored_from_autosave_h_
#ifndef untitled_restored_from_autosave_COMMON_INCLUDES_
#define untitled_restored_from_autosave_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_extmode.h"
#include "sysran_types.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "MW_ServoWriteRead.h"
#endif                    /* untitled_restored_from_autosave_COMMON_INCLUDES_ */

#include "untitled_restored_from_autosave_types.h"
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

#define untitled_restored_from_autosave_M (untitled_restored_from_autos_M)

/* Block states (default storage) for system '<Root>' */
typedef struct {
  codertarget_arduinobase_inter_T obj; /* '<Root>/Standard Servo Write3' */
  codertarget_arduinobase_inter_T obj_l;/* '<Root>/Standard Servo Write2' */
  codertarget_arduinobase_inter_T obj_i;/* '<Root>/Standard Servo Write1' */
  codertarget_arduinobase_inter_T obj_lh;/* '<Root>/Standard Servo Write' */
  uint16_T Output_DSTATE;              /* '<S5>/Output' */
  uint16_T Output_DSTATE_j;            /* '<S8>/Output' */
  uint16_T Output_DSTATE_jp;           /* '<S11>/Output' */
  uint16_T Output_DSTATE_l;            /* '<S14>/Output' */
} DW_untitled_restored_from_aut_T;

/* Parameters (default storage) */
struct P_untitled_restored_from_auto_T_ {
  real_T Dj2[7];                       /* Variable: Dj2
                                        * Referenced by: '<S2>/Lookup'
                                        */
  real_T Dj3[7];                       /* Variable: Dj3
                                        * Referenced by: '<S3>/Lookup'
                                        */
  real_T Dj4[7];                       /* Variable: Dj4
                                        * Referenced by: '<S4>/Lookup'
                                        */
  real_T Dj5[7];                       /* Variable: Dj5
                                        * Referenced by: '<S1>/Lookup'
                                        */
  real_T RepeatingSequenceInterpolated_T[7];
                              /* Mask Parameter: RepeatingSequenceInterpolated_T
                               * Referenced by: '<S1>/Lookup'
                               */
  real_T RepeatingSequenceInterpolated1_[7];
                              /* Mask Parameter: RepeatingSequenceInterpolated1_
                               * Referenced by: '<S2>/Lookup'
                               */
  real_T RepeatingSequenceInterpolated2_[7];
                              /* Mask Parameter: RepeatingSequenceInterpolated2_
                               * Referenced by: '<S3>/Lookup'
                               */
  real_T RepeatingSequenceInterpolated3_[7];
                              /* Mask Parameter: RepeatingSequenceInterpolated3_
                               * Referenced by: '<S4>/Lookup'
                               */
  uint16_T WrapToZero_Threshold;       /* Mask Parameter: WrapToZero_Threshold
                                        * Referenced by: '<S7>/FixPt Switch'
                                        */
  uint16_T WrapToZero_Threshold_g;     /* Mask Parameter: WrapToZero_Threshold_g
                                        * Referenced by: '<S10>/FixPt Switch'
                                        */
  uint16_T WrapToZero_Threshold_o;     /* Mask Parameter: WrapToZero_Threshold_o
                                        * Referenced by: '<S13>/FixPt Switch'
                                        */
  uint16_T WrapToZero_Threshold_i;     /* Mask Parameter: WrapToZero_Threshold_i
                                        * Referenced by: '<S16>/FixPt Switch'
                                        */
  real_T SampleTimeMath_WtEt;         /* Computed Parameter: SampleTimeMath_WtEt
                                       * Referenced by: '<S1>/Sample Time Math'
                                       */
  real_T AddConstant_Bias;             /* Expression: -45
                                        * Referenced by: '<Root>/Add Constant'
                                        */
  real_T SampleTimeMath_WtEt_d;     /* Computed Parameter: SampleTimeMath_WtEt_d
                                     * Referenced by: '<S2>/Sample Time Math'
                                     */
  real_T AddConstant1_Bias;            /* Expression: 60
                                        * Referenced by: '<Root>/Add Constant1'
                                        */
  real_T SampleTimeMath_WtEt_k;     /* Computed Parameter: SampleTimeMath_WtEt_k
                                     * Referenced by: '<S3>/Sample Time Math'
                                     */
  real_T AddConstant2_Bias;            /* Expression: 200
                                        * Referenced by: '<Root>/Add Constant2'
                                        */
  real_T SampleTimeMath_WtEt_h;     /* Computed Parameter: SampleTimeMath_WtEt_h
                                     * Referenced by: '<S4>/Sample Time Math'
                                     */
  real_T AddConstant3_Bias;            /* Expression: 45
                                        * Referenced by: '<Root>/Add Constant3'
                                        */
  uint16_T Constant_Value;             /* Computed Parameter: Constant_Value
                                        * Referenced by: '<S7>/Constant'
                                        */
  uint16_T Constant_Value_i;           /* Computed Parameter: Constant_Value_i
                                        * Referenced by: '<S10>/Constant'
                                        */
  uint16_T Constant_Value_n;           /* Computed Parameter: Constant_Value_n
                                        * Referenced by: '<S13>/Constant'
                                        */
  uint16_T Constant_Value_a;           /* Computed Parameter: Constant_Value_a
                                        * Referenced by: '<S16>/Constant'
                                        */
  uint16_T Output_InitialCondition;
                                  /* Computed Parameter: Output_InitialCondition
                                   * Referenced by: '<S5>/Output'
                                   */
  uint16_T FixPtConstant_Value;       /* Computed Parameter: FixPtConstant_Value
                                       * Referenced by: '<S6>/FixPt Constant'
                                       */
  uint16_T Output_InitialCondition_j;
                                /* Computed Parameter: Output_InitialCondition_j
                                 * Referenced by: '<S8>/Output'
                                 */
  uint16_T FixPtConstant_Value_a;   /* Computed Parameter: FixPtConstant_Value_a
                                     * Referenced by: '<S9>/FixPt Constant'
                                     */
  uint16_T Output_InitialCondition_a;
                                /* Computed Parameter: Output_InitialCondition_a
                                 * Referenced by: '<S11>/Output'
                                 */
  uint16_T FixPtConstant_Value_k;   /* Computed Parameter: FixPtConstant_Value_k
                                     * Referenced by: '<S12>/FixPt Constant'
                                     */
  uint16_T Output_InitialCondition_i;
                                /* Computed Parameter: Output_InitialCondition_i
                                 * Referenced by: '<S14>/Output'
                                 */
  uint16_T FixPtConstant_Value_h;   /* Computed Parameter: FixPtConstant_Value_h
                                     * Referenced by: '<S15>/FixPt Constant'
                                     */
};

/* Real-time Model Data Structure */
struct tag_RTM_untitled_restored_fro_T {
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
    time_T tFinal;
    boolean_T stopRequestedFlag;
  } Timing;
};

/* Block parameters (default storage) */
extern P_untitled_restored_from_auto_T untitled_restored_from_autosa_P;

/* Block states (default storage) */
extern DW_untitled_restored_from_aut_T untitled_restored_from_autos_DW;

/* Model entry point functions */
extern void untitled_restored_from_autosave_initialize(void);
extern void untitled_restored_from_autosave_step(void);
extern void untitled_restored_from_autosave_terminate(void);

/* Real-time Model object */
extern RT_MODEL_untitled_restored_fr_T *const untitled_restored_from_autos_M;
extern volatile boolean_T stopRequested;
extern volatile boolean_T runModel;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S1>/Data Type Propagation' : Unused code path elimination
 * Block '<S5>/Data Type Propagation' : Unused code path elimination
 * Block '<S6>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S7>/FixPt Data Type Duplicate1' : Unused code path elimination
 * Block '<S2>/Data Type Propagation' : Unused code path elimination
 * Block '<S8>/Data Type Propagation' : Unused code path elimination
 * Block '<S9>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S10>/FixPt Data Type Duplicate1' : Unused code path elimination
 * Block '<S3>/Data Type Propagation' : Unused code path elimination
 * Block '<S11>/Data Type Propagation' : Unused code path elimination
 * Block '<S12>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S13>/FixPt Data Type Duplicate1' : Unused code path elimination
 * Block '<S4>/Data Type Propagation' : Unused code path elimination
 * Block '<S14>/Data Type Propagation' : Unused code path elimination
 * Block '<S15>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S16>/FixPt Data Type Duplicate1' : Unused code path elimination
 * Block '<S1>/Output' : Eliminate redundant signal conversion block
 * Block '<S2>/Output' : Eliminate redundant signal conversion block
 * Block '<S3>/Output' : Eliminate redundant signal conversion block
 * Block '<S4>/Output' : Eliminate redundant signal conversion block
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
 * '<Root>' : 'untitled_restored_from_autosave'
 * '<S1>'   : 'untitled_restored_from_autosave/Repeating Sequence Interpolated'
 * '<S2>'   : 'untitled_restored_from_autosave/Repeating Sequence Interpolated1'
 * '<S3>'   : 'untitled_restored_from_autosave/Repeating Sequence Interpolated2'
 * '<S4>'   : 'untitled_restored_from_autosave/Repeating Sequence Interpolated3'
 * '<S5>'   : 'untitled_restored_from_autosave/Repeating Sequence Interpolated/LimitedCounter'
 * '<S6>'   : 'untitled_restored_from_autosave/Repeating Sequence Interpolated/LimitedCounter/Increment Real World'
 * '<S7>'   : 'untitled_restored_from_autosave/Repeating Sequence Interpolated/LimitedCounter/Wrap To Zero'
 * '<S8>'   : 'untitled_restored_from_autosave/Repeating Sequence Interpolated1/LimitedCounter'
 * '<S9>'   : 'untitled_restored_from_autosave/Repeating Sequence Interpolated1/LimitedCounter/Increment Real World'
 * '<S10>'  : 'untitled_restored_from_autosave/Repeating Sequence Interpolated1/LimitedCounter/Wrap To Zero'
 * '<S11>'  : 'untitled_restored_from_autosave/Repeating Sequence Interpolated2/LimitedCounter'
 * '<S12>'  : 'untitled_restored_from_autosave/Repeating Sequence Interpolated2/LimitedCounter/Increment Real World'
 * '<S13>'  : 'untitled_restored_from_autosave/Repeating Sequence Interpolated2/LimitedCounter/Wrap To Zero'
 * '<S14>'  : 'untitled_restored_from_autosave/Repeating Sequence Interpolated3/LimitedCounter'
 * '<S15>'  : 'untitled_restored_from_autosave/Repeating Sequence Interpolated3/LimitedCounter/Increment Real World'
 * '<S16>'  : 'untitled_restored_from_autosave/Repeating Sequence Interpolated3/LimitedCounter/Wrap To Zero'
 */
#endif                                 /* untitled_restored_from_autosave_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

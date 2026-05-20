/*
 * File: trajectory_servo_control.c
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

#include "trajectory_servo_control.h"
#include "trajectory_servo_control_private.h"
#include <math.h>
#include "rtwtypes.h"

/* Block states (default storage) */
DW_trajectory_servo_control_T trajectory_servo_control_DW;

/* Real-time model */
static RT_MODEL_trajectory_servo_con_T trajectory_servo_control_M_;
RT_MODEL_trajectory_servo_con_T *const trajectory_servo_control_M =
  &trajectory_servo_control_M_;
static void rate_monotonic_scheduler(void);
real_T look1_binlcpw(real_T u0, const real_T bp0[], const real_T table[],
                     uint32_T maxIndex)
{
  real_T frac;
  real_T yL_0d0;
  uint32_T bpIdx;
  uint32_T iLeft;
  uint32_T iRght;

  /* Column-major Lookup 1-D
     Search method: 'binary'
     Use previous index: 'off'
     Interpolation method: 'Linear point-slope'
     Extrapolation method: 'Clip'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  /* Prelookup - Index and Fraction
     Index Search method: 'binary'
     Extrapolation method: 'Clip'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u0 <= bp0[0U]) {
    iLeft = 0U;
    frac = 0.0;
  } else if (u0 < bp0[maxIndex]) {
    /* Binary Search */
    bpIdx = maxIndex >> 1U;
    iLeft = 0U;
    iRght = maxIndex;
    while (iRght - iLeft > 1U) {
      if (u0 < bp0[bpIdx]) {
        iRght = bpIdx;
      } else {
        iLeft = bpIdx;
      }

      bpIdx = (iRght + iLeft) >> 1U;
    }

    frac = (u0 - bp0[iLeft]) / (bp0[iLeft + 1U] - bp0[iLeft]);
  } else {
    iLeft = maxIndex - 1U;
    frac = 1.0;
  }

  /* Column-major Interpolation 1-D
     Interpolation method: 'Linear point-slope'
     Use last breakpoint for index at or above upper limit: 'off'
     Overflow mode: 'portable wrapping'
   */
  yL_0d0 = table[iLeft];
  return (table[iLeft + 1U] - yL_0d0) * frac + yL_0d0;
}

/*
 * Set which subrates need to run this base step (base rate always runs).
 * This function must be called prior to calling the model step function
 * in order to remember which rates need to run this base step.  The
 * buffering of events allows for overlapping preemption.
 */
void trajectory_servo_control_SetEventsForThisBaseStep(boolean_T *eventFlags)
{
  /* Task runs when its counter is zero, computed via rtmStepTask macro */
  eventFlags[1] = ((boolean_T)rtmStepTask(trajectory_servo_control_M, 1));
}

/*
 *         This function updates active task flag for each subrate
 *         and rate transition flags for tasks that exchange data.
 *         The function assumes rate-monotonic multitasking scheduler.
 *         The function must be called at model base rate so that
 *         the generated code self-manages all its subrates and rate
 *         transition flags.
 */
static void rate_monotonic_scheduler(void)
{
  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (trajectory_servo_control_M->Timing.TaskCounters.TID[1])++;
  if ((trajectory_servo_control_M->Timing.TaskCounters.TID[1]) > 1) {/* Sample time: [0.01s, 0.0s] */
    trajectory_servo_control_M->Timing.TaskCounters.TID[1] = 0;
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

/* Model step function for TID0 */
void trajectory_servo_control_step0(void) /* Sample time: [0.005s, 0.0s] */
{
  {                                    /* Sample time: [0.005s, 0.0s] */
    rate_monotonic_scheduler();
  }

  /* Update absolute time */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   */
  trajectory_servo_control_M->Timing.taskTime0 =
    ((time_T)(++trajectory_servo_control_M->Timing.clockTick0)) *
    trajectory_servo_control_M->Timing.stepSize0;
}

/* Model step function for TID1 */
void trajectory_servo_control_step1(void) /* Sample time: [0.01s, 0.0s] */
{
  real_T rtb_AddConstant;
  real_T rtb_Lookup;
  uint16_T rtb_FixPtSum1;
  uint8_T tmp;
  boolean_T step;

  /* Bias: '<Root>/Add Constant' incorporates:
   *  DataTypeConversion: '<S3>/Data Type Conversion'
   *  Lookup_n-D: '<S3>/Lookup'
   *  SampleTimeMath: '<S3>/Sample Time Math'
   *  UnitDelay: '<S10>/Output'
   *
   * About '<S3>/Sample Time Math':
   *  y = u * K where K = ( w * Ts )
   *   */
  rtb_AddConstant = look1_binlcpw((real_T)
    trajectory_servo_control_DW.Output_DSTATE *
    trajectory_servo_control_P.SampleTimeMath_WtEt,
    trajectory_servo_control_P.RepeatingSequenceInterpolated1_,
    trajectory_servo_control_P.pj3, 7U) +
    trajectory_servo_control_P.AddConstant_Bias;

  /* MATLABSystem: '<Root>/Standard Servo Write1' */
  if (rtb_AddConstant < 0.0) {
    tmp = 0U;
  } else if (rtb_AddConstant > 180.0) {
    tmp = 180U;
  } else {
    rtb_AddConstant = rt_roundd_snf(rtb_AddConstant);
    if (rtb_AddConstant < 256.0) {
      tmp = (uint8_T)rtb_AddConstant;
    } else {
      tmp = MAX_uint8_T;
    }
  }

  MW_servoWrite(1, tmp);

  /* End of MATLABSystem: '<Root>/Standard Servo Write1' */

  /* Sum: '<S11>/FixPt Sum1' incorporates:
   *  Constant: '<S11>/FixPt Constant'
   *  UnitDelay: '<S10>/Output'
   */
  rtb_FixPtSum1 = (uint16_T)((uint32_T)trajectory_servo_control_DW.Output_DSTATE
    + trajectory_servo_control_P.FixPtConstant_Value);

  /* Switch: '<S12>/FixPt Switch' incorporates:
   *  Constant: '<S12>/Constant'
   *  UnitDelay: '<S10>/Output'
   */
  if (rtb_FixPtSum1 > trajectory_servo_control_P.WrapToZero_Threshold) {
    trajectory_servo_control_DW.Output_DSTATE =
      trajectory_servo_control_P.Constant_Value_l;
  } else {
    trajectory_servo_control_DW.Output_DSTATE = rtb_FixPtSum1;
  }

  /* End of Switch: '<S12>/FixPt Switch' */

  /* Bias: '<Root>/Add Constant1' incorporates:
   *  DataTypeConversion: '<S4>/Data Type Conversion'
   *  Lookup_n-D: '<S4>/Lookup'
   *  SampleTimeMath: '<S4>/Sample Time Math'
   *  UnitDelay: '<S13>/Output'
   *
   * About '<S4>/Sample Time Math':
   *  y = u * K where K = ( w * Ts )
   *   */
  rtb_AddConstant = look1_binlcpw((real_T)
    trajectory_servo_control_DW.Output_DSTATE_n *
    trajectory_servo_control_P.SampleTimeMath_WtEt_i,
    trajectory_servo_control_P.RepeatingSequenceInterpolated2_,
    trajectory_servo_control_P.pj4, 7U) +
    trajectory_servo_control_P.AddConstant1_Bias;

  /* MATLABSystem: '<Root>/Standard Servo Write2' */
  if (rtb_AddConstant < 0.0) {
    tmp = 0U;
  } else if (rtb_AddConstant > 180.0) {
    tmp = 180U;
  } else {
    rtb_AddConstant = rt_roundd_snf(rtb_AddConstant);
    if (rtb_AddConstant < 256.0) {
      tmp = (uint8_T)rtb_AddConstant;
    } else {
      tmp = MAX_uint8_T;
    }
  }

  MW_servoWrite(2, tmp);

  /* End of MATLABSystem: '<Root>/Standard Servo Write2' */

  /* Sum: '<S14>/FixPt Sum1' incorporates:
   *  Constant: '<S14>/FixPt Constant'
   *  UnitDelay: '<S13>/Output'
   */
  rtb_FixPtSum1 = (uint16_T)((uint32_T)
    trajectory_servo_control_DW.Output_DSTATE_n +
    trajectory_servo_control_P.FixPtConstant_Value_m);

  /* Switch: '<S15>/FixPt Switch' incorporates:
   *  Constant: '<S15>/Constant'
   *  UnitDelay: '<S13>/Output'
   */
  if (rtb_FixPtSum1 > trajectory_servo_control_P.WrapToZero_Threshold_e) {
    trajectory_servo_control_DW.Output_DSTATE_n =
      trajectory_servo_control_P.Constant_Value_e;
  } else {
    trajectory_servo_control_DW.Output_DSTATE_n = rtb_FixPtSum1;
  }

  /* End of Switch: '<S15>/FixPt Switch' */

  /* Bias: '<Root>/Add Constant3' incorporates:
   *  DataTypeConversion: '<S5>/Data Type Conversion'
   *  Lookup_n-D: '<S5>/Lookup'
   *  SampleTimeMath: '<S5>/Sample Time Math'
   *  UnitDelay: '<S16>/Output'
   *
   * About '<S5>/Sample Time Math':
   *  y = u * K where K = ( w * Ts )
   *   */
  rtb_AddConstant = look1_binlcpw((real_T)
    trajectory_servo_control_DW.Output_DSTATE_b *
    trajectory_servo_control_P.SampleTimeMath_WtEt_c,
    trajectory_servo_control_P.RepeatingSequenceInterpolated3_,
    trajectory_servo_control_P.pj5, 7U) +
    trajectory_servo_control_P.AddConstant3_Bias;

  /* MATLABSystem: '<Root>/Standard Servo Write4' */
  if (rtb_AddConstant < 0.0) {
    tmp = 0U;
  } else if (rtb_AddConstant > 180.0) {
    tmp = 180U;
  } else {
    rtb_AddConstant = rt_roundd_snf(rtb_AddConstant);
    if (rtb_AddConstant < 256.0) {
      tmp = (uint8_T)rtb_AddConstant;
    } else {
      tmp = MAX_uint8_T;
    }
  }

  MW_servoWrite(4, tmp);

  /* End of MATLABSystem: '<Root>/Standard Servo Write4' */

  /* Sum: '<S17>/FixPt Sum1' incorporates:
   *  Constant: '<S17>/FixPt Constant'
   *  UnitDelay: '<S16>/Output'
   */
  rtb_FixPtSum1 = (uint16_T)((uint32_T)
    trajectory_servo_control_DW.Output_DSTATE_b +
    trajectory_servo_control_P.FixPtConstant_Value_a);

  /* Switch: '<S18>/FixPt Switch' incorporates:
   *  Constant: '<S18>/Constant'
   *  UnitDelay: '<S16>/Output'
   */
  if (rtb_FixPtSum1 > trajectory_servo_control_P.WrapToZero_Threshold_j) {
    trajectory_servo_control_DW.Output_DSTATE_b =
      trajectory_servo_control_P.Constant_Value_a;
  } else {
    trajectory_servo_control_DW.Output_DSTATE_b = rtb_FixPtSum1;
  }

  /* End of Switch: '<S18>/FixPt Switch' */

  /* Bias: '<Root>/Add Constant4' incorporates:
   *  DataTypeConversion: '<S2>/Data Type Conversion'
   *  Lookup_n-D: '<S2>/Lookup'
   *  SampleTimeMath: '<S2>/Sample Time Math'
   *  UnitDelay: '<S7>/Output'
   *
   * About '<S2>/Sample Time Math':
   *  y = u * K where K = ( w * Ts )
   *   */
  rtb_AddConstant = look1_binlcpw((real_T)
    trajectory_servo_control_DW.Output_DSTATE_f *
    trajectory_servo_control_P.SampleTimeMath_WtEt_l,
    trajectory_servo_control_P.RepeatingSequenceInterpolated_T,
    trajectory_servo_control_P.pj2, 7U) +
    trajectory_servo_control_P.AddConstant4_Bias;

  /* MATLABSystem: '<Root>/Standard Servo Write' */
  if (rtb_AddConstant < 0.0) {
    tmp = 0U;
  } else if (rtb_AddConstant > 180.0) {
    tmp = 180U;
  } else {
    rtb_AddConstant = rt_roundd_snf(rtb_AddConstant);
    if (rtb_AddConstant < 256.0) {
      tmp = (uint8_T)rtb_AddConstant;
    } else {
      tmp = MAX_uint8_T;
    }
  }

  MW_servoWrite(0, tmp);

  /* End of MATLABSystem: '<Root>/Standard Servo Write' */

  /* Sum: '<S8>/FixPt Sum1' incorporates:
   *  Constant: '<S8>/FixPt Constant'
   *  UnitDelay: '<S7>/Output'
   */
  rtb_FixPtSum1 = (uint16_T)((uint32_T)
    trajectory_servo_control_DW.Output_DSTATE_f +
    trajectory_servo_control_P.FixPtConstant_Value_c);

  /* Switch: '<S9>/FixPt Switch' incorporates:
   *  Constant: '<S9>/Constant'
   *  UnitDelay: '<S7>/Output'
   */
  if (rtb_FixPtSum1 > trajectory_servo_control_P.WrapToZero_Threshold_c) {
    trajectory_servo_control_DW.Output_DSTATE_f =
      trajectory_servo_control_P.Constant_Value_h;
  } else {
    trajectory_servo_control_DW.Output_DSTATE_f = rtb_FixPtSum1;
  }

  /* End of Switch: '<S9>/FixPt Switch' */

  /* MATLABSystem: '<Root>/Standard Servo Write3' incorporates:
   *  Constant: '<Root>/Constant'
   */
  if (trajectory_servo_control_P.Constant_Value < 0.0) {
    tmp = 0U;
  } else if (trajectory_servo_control_P.Constant_Value > 180.0) {
    tmp = 180U;
  } else {
    rtb_AddConstant = rt_roundd_snf(trajectory_servo_control_P.Constant_Value);
    if (rtb_AddConstant < 256.0) {
      if (rtb_AddConstant >= 0.0) {
        tmp = (uint8_T)rtb_AddConstant;
      } else {
        tmp = 0U;
      }
    } else {
      tmp = MAX_uint8_T;
    }
  }

  MW_servoWrite(3, tmp);

  /* End of MATLABSystem: '<Root>/Standard Servo Write3' */

  /* Lookup_n-D: '<S6>/Lookup' incorporates:
   *  DataTypeConversion: '<S6>/Data Type Conversion'
   *  SampleTimeMath: '<S6>/Sample Time Math'
   *  UnitDelay: '<S19>/Output'
   *
   * About '<S6>/Sample Time Math':
   *  y = u * K where K = ( w * Ts )
   *   */
  rtb_Lookup = look1_binlcpw((real_T)trajectory_servo_control_DW.Output_DSTATE_g
    * trajectory_servo_control_P.SampleTimeMath_WtEt_lo,
    trajectory_servo_control_P.RepeatingSequenceInterpolated4_,
    trajectory_servo_control_P.pj1, 7U);

  /* MATLAB Function: '<Root>/MATLAB Function' */
  if (rtb_Lookup != trajectory_servo_control_DW.last_angle) {
    rtb_AddConstant = rt_roundd_snf(fabs(rtb_Lookup) * 200.0 / 360.0);
    if (rtb_AddConstant < 2.147483648E+9) {
      trajectory_servo_control_DW.target = (int32_T)rtb_AddConstant;
    } else {
      trajectory_servo_control_DW.target = MAX_int32_T;
    }

    trajectory_servo_control_DW.count = 0;
    trajectory_servo_control_DW.last_angle = rtb_Lookup;
    trajectory_servo_control_DW.pulse_phase = false;
  }

  if (trajectory_servo_control_DW.count < trajectory_servo_control_DW.target) {
    if (!trajectory_servo_control_DW.pulse_phase) {
      step = true;
      trajectory_servo_control_DW.pulse_phase = true;
    } else {
      step = false;
      trajectory_servo_control_DW.pulse_phase = false;
      trajectory_servo_control_DW.count++;
    }
  } else {
    step = false;
    trajectory_servo_control_DW.pulse_phase = false;
  }

  /* MATLABSystem: '<Root>/Digital Output' */
  writeDigitalPin(18, (uint8_T)step);

  /* MATLABSystem: '<Root>/Digital Output1' incorporates:
   *  MATLAB Function: '<Root>/MATLAB Function'
   */
  writeDigitalPin(19, (uint8_T)(rtb_Lookup >= 0.0));

  /* Sum: '<S20>/FixPt Sum1' incorporates:
   *  Constant: '<S20>/FixPt Constant'
   *  UnitDelay: '<S19>/Output'
   */
  rtb_FixPtSum1 = (uint16_T)((uint32_T)
    trajectory_servo_control_DW.Output_DSTATE_g +
    trajectory_servo_control_P.FixPtConstant_Value_b);

  /* Switch: '<S21>/FixPt Switch' incorporates:
   *  Constant: '<S21>/Constant'
   *  UnitDelay: '<S19>/Output'
   */
  if (rtb_FixPtSum1 > trajectory_servo_control_P.WrapToZero_Threshold_ch) {
    trajectory_servo_control_DW.Output_DSTATE_g =
      trajectory_servo_control_P.Constant_Value_n;
  } else {
    trajectory_servo_control_DW.Output_DSTATE_g = rtb_FixPtSum1;
  }

  /* End of Switch: '<S21>/FixPt Switch' */

  /* Update absolute time */
  /* The "clockTick1" counts the number of times the code of this task has
   * been executed. The resolution of this integer timer is 0.01, which is the step size
   * of the task. Size of "clockTick1" ensures timer will not overflow during the
   * application lifespan selected.
   */
  trajectory_servo_control_M->Timing.clockTick1++;
}

/* Use this function only if you need to maintain compatibility with an existing static main program. */
void trajectory_servo_control_step(int_T tid)
{
  switch (tid) {
   case 0 :
    trajectory_servo_control_step0();
    break;

   case 1 :
    trajectory_servo_control_step1();
    break;

   default :
    /* do nothing */
    break;
  }
}

/* Model initialize function */
void trajectory_servo_control_initialize(void)
{
  /* Registration code */
  rtmSetTFinal(trajectory_servo_control_M, -1);
  trajectory_servo_control_M->Timing.stepSize0 = 0.005;

  /* External mode info */
  trajectory_servo_control_M->Sizes.checksums[0] = (3766620791U);
  trajectory_servo_control_M->Sizes.checksums[1] = (4251520533U);
  trajectory_servo_control_M->Sizes.checksums[2] = (3249879758U);
  trajectory_servo_control_M->Sizes.checksums[3] = (3354783421U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[14];
    trajectory_servo_control_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    systemRan[2] = &rtAlwaysEnabled;
    systemRan[3] = &rtAlwaysEnabled;
    systemRan[4] = &rtAlwaysEnabled;
    systemRan[5] = &rtAlwaysEnabled;
    systemRan[6] = &rtAlwaysEnabled;
    systemRan[7] = &rtAlwaysEnabled;
    systemRan[8] = &rtAlwaysEnabled;
    systemRan[9] = &rtAlwaysEnabled;
    systemRan[10] = &rtAlwaysEnabled;
    systemRan[11] = &rtAlwaysEnabled;
    systemRan[12] = &rtAlwaysEnabled;
    systemRan[13] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(trajectory_servo_control_M->extModeInfo,
      &trajectory_servo_control_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(trajectory_servo_control_M->extModeInfo,
                        trajectory_servo_control_M->Sizes.checksums);
    rteiSetTPtr(trajectory_servo_control_M->extModeInfo, rtmGetTPtr
                (trajectory_servo_control_M));
  }

  /* InitializeConditions for UnitDelay: '<S10>/Output' */
  trajectory_servo_control_DW.Output_DSTATE =
    trajectory_servo_control_P.Output_InitialCondition;

  /* InitializeConditions for UnitDelay: '<S13>/Output' */
  trajectory_servo_control_DW.Output_DSTATE_n =
    trajectory_servo_control_P.Output_InitialCondition_g;

  /* InitializeConditions for UnitDelay: '<S16>/Output' */
  trajectory_servo_control_DW.Output_DSTATE_b =
    trajectory_servo_control_P.Output_InitialCondition_l;

  /* InitializeConditions for UnitDelay: '<S7>/Output' */
  trajectory_servo_control_DW.Output_DSTATE_f =
    trajectory_servo_control_P.Output_InitialCondition_p;

  /* InitializeConditions for UnitDelay: '<S19>/Output' */
  trajectory_servo_control_DW.Output_DSTATE_g =
    trajectory_servo_control_P.Output_InitialCondition_b;

  /* Start for MATLABSystem: '<Root>/Standard Servo Write1' */
  trajectory_servo_control_DW.obj_jv.matlabCodegenIsDeleted = false;
  trajectory_servo_control_DW.obj_jv.isInitialized = 1;
  MW_servoAttach(1, 12);
  trajectory_servo_control_DW.obj_jv.isSetupComplete = true;

  /* Start for MATLABSystem: '<Root>/Standard Servo Write2' */
  trajectory_servo_control_DW.obj_l.matlabCodegenIsDeleted = false;
  trajectory_servo_control_DW.obj_l.isInitialized = 1;
  MW_servoAttach(2, 14);
  trajectory_servo_control_DW.obj_l.isSetupComplete = true;

  /* Start for MATLABSystem: '<Root>/Standard Servo Write4' */
  trajectory_servo_control_DW.obj_j.matlabCodegenIsDeleted = false;
  trajectory_servo_control_DW.obj_j.isInitialized = 1;
  MW_servoAttach(4, 27);
  trajectory_servo_control_DW.obj_j.isSetupComplete = true;

  /* Start for MATLABSystem: '<Root>/Standard Servo Write' */
  trajectory_servo_control_DW.obj_p.matlabCodegenIsDeleted = false;
  trajectory_servo_control_DW.obj_p.isInitialized = 1;
  MW_servoAttach(0, 13);
  trajectory_servo_control_DW.obj_p.isSetupComplete = true;

  /* Start for MATLABSystem: '<Root>/Standard Servo Write3' */
  trajectory_servo_control_DW.obj_i.matlabCodegenIsDeleted = false;
  trajectory_servo_control_DW.obj_i.isInitialized = 1;
  MW_servoAttach(3, 26);
  trajectory_servo_control_DW.obj_i.isSetupComplete = true;

  /* Start for MATLABSystem: '<Root>/Digital Output' */
  trajectory_servo_control_DW.obj_m.matlabCodegenIsDeleted = false;
  trajectory_servo_control_DW.obj_m.isInitialized = 1;
  digitalIOSetup(18, 1);
  trajectory_servo_control_DW.obj_m.isSetupComplete = true;

  /* Start for MATLABSystem: '<Root>/Digital Output1' */
  trajectory_servo_control_DW.obj.matlabCodegenIsDeleted = false;
  trajectory_servo_control_DW.obj.isInitialized = 1;
  digitalIOSetup(19, 1);
  trajectory_servo_control_DW.obj.isSetupComplete = true;
}

/* Model terminate function */
void trajectory_servo_control_terminate(void)
{
  /* Terminate for MATLABSystem: '<Root>/Standard Servo Write1' */
  if (!trajectory_servo_control_DW.obj_jv.matlabCodegenIsDeleted) {
    trajectory_servo_control_DW.obj_jv.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<Root>/Standard Servo Write1' */

  /* Terminate for MATLABSystem: '<Root>/Standard Servo Write2' */
  if (!trajectory_servo_control_DW.obj_l.matlabCodegenIsDeleted) {
    trajectory_servo_control_DW.obj_l.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<Root>/Standard Servo Write2' */

  /* Terminate for MATLABSystem: '<Root>/Standard Servo Write4' */
  if (!trajectory_servo_control_DW.obj_j.matlabCodegenIsDeleted) {
    trajectory_servo_control_DW.obj_j.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<Root>/Standard Servo Write4' */

  /* Terminate for MATLABSystem: '<Root>/Standard Servo Write' */
  if (!trajectory_servo_control_DW.obj_p.matlabCodegenIsDeleted) {
    trajectory_servo_control_DW.obj_p.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<Root>/Standard Servo Write' */

  /* Terminate for MATLABSystem: '<Root>/Standard Servo Write3' */
  if (!trajectory_servo_control_DW.obj_i.matlabCodegenIsDeleted) {
    trajectory_servo_control_DW.obj_i.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<Root>/Standard Servo Write3' */

  /* Terminate for MATLABSystem: '<Root>/Digital Output' */
  if (!trajectory_servo_control_DW.obj_m.matlabCodegenIsDeleted) {
    trajectory_servo_control_DW.obj_m.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<Root>/Digital Output' */

  /* Terminate for MATLABSystem: '<Root>/Digital Output1' */
  if (!trajectory_servo_control_DW.obj.matlabCodegenIsDeleted) {
    trajectory_servo_control_DW.obj.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<Root>/Digital Output1' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

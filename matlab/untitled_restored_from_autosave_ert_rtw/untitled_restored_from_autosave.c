/*
 * File: untitled_restored_from_autosave.c
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

#include "untitled_restored_from_autosave.h"
#include "untitled_restored_from_autosave_private.h"
#include "rtwtypes.h"
#include <math.h>

/* Block states (default storage) */
DW_untitled_restored_from_aut_T untitled_restored_from_autos_DW;

/* Real-time model */
static RT_MODEL_untitled_restored_fr_T untitled_restored_from_autos_M_;
RT_MODEL_untitled_restored_fr_T *const untitled_restored_from_autos_M =
  &untitled_restored_from_autos_M_;
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
void untitled_restored_from_autosave_step(void)
{
  real_T rtb_AddConstant;
  uint16_T rtb_FixPtSum1;
  uint8_T tmp;

  /* Bias: '<Root>/Add Constant' incorporates:
   *  DataTypeConversion: '<S1>/Data Type Conversion'
   *  Lookup_n-D: '<S1>/Lookup'
   *  SampleTimeMath: '<S1>/Sample Time Math'
   *  UnitDelay: '<S5>/Output'
   *
   * About '<S1>/Sample Time Math':
   *  y = u * K where K = ( w * Ts )
   *   */
  rtb_AddConstant = look1_binlcpw((real_T)
    untitled_restored_from_autos_DW.Output_DSTATE *
    untitled_restored_from_autosa_P.SampleTimeMath_WtEt,
    untitled_restored_from_autosa_P.RepeatingSequenceInterpolated_T,
    untitled_restored_from_autosa_P.Dj5, 6U) +
    untitled_restored_from_autosa_P.AddConstant_Bias;

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

  /* Sum: '<S6>/FixPt Sum1' incorporates:
   *  Constant: '<S6>/FixPt Constant'
   *  UnitDelay: '<S5>/Output'
   */
  rtb_FixPtSum1 = (uint16_T)((uint32_T)
    untitled_restored_from_autos_DW.Output_DSTATE +
    untitled_restored_from_autosa_P.FixPtConstant_Value);

  /* Switch: '<S7>/FixPt Switch' incorporates:
   *  Constant: '<S7>/Constant'
   *  UnitDelay: '<S5>/Output'
   */
  if (rtb_FixPtSum1 > untitled_restored_from_autosa_P.WrapToZero_Threshold) {
    untitled_restored_from_autos_DW.Output_DSTATE =
      untitled_restored_from_autosa_P.Constant_Value;
  } else {
    untitled_restored_from_autos_DW.Output_DSTATE = rtb_FixPtSum1;
  }

  /* End of Switch: '<S7>/FixPt Switch' */

  /* Bias: '<Root>/Add Constant1' incorporates:
   *  DataTypeConversion: '<S2>/Data Type Conversion'
   *  Lookup_n-D: '<S2>/Lookup'
   *  SampleTimeMath: '<S2>/Sample Time Math'
   *  UnitDelay: '<S8>/Output'
   *
   * About '<S2>/Sample Time Math':
   *  y = u * K where K = ( w * Ts )
   *   */
  rtb_AddConstant = look1_binlcpw((real_T)
    untitled_restored_from_autos_DW.Output_DSTATE_j *
    untitled_restored_from_autosa_P.SampleTimeMath_WtEt_d,
    untitled_restored_from_autosa_P.RepeatingSequenceInterpolated1_,
    untitled_restored_from_autosa_P.Dj2, 6U) +
    untitled_restored_from_autosa_P.AddConstant1_Bias;

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

  /* Sum: '<S9>/FixPt Sum1' incorporates:
   *  Constant: '<S9>/FixPt Constant'
   *  UnitDelay: '<S8>/Output'
   */
  rtb_FixPtSum1 = (uint16_T)((uint32_T)
    untitled_restored_from_autos_DW.Output_DSTATE_j +
    untitled_restored_from_autosa_P.FixPtConstant_Value_a);

  /* Switch: '<S10>/FixPt Switch' incorporates:
   *  Constant: '<S10>/Constant'
   *  UnitDelay: '<S8>/Output'
   */
  if (rtb_FixPtSum1 > untitled_restored_from_autosa_P.WrapToZero_Threshold_g) {
    untitled_restored_from_autos_DW.Output_DSTATE_j =
      untitled_restored_from_autosa_P.Constant_Value_i;
  } else {
    untitled_restored_from_autos_DW.Output_DSTATE_j = rtb_FixPtSum1;
  }

  /* End of Switch: '<S10>/FixPt Switch' */

  /* Bias: '<Root>/Add Constant2' incorporates:
   *  DataTypeConversion: '<S3>/Data Type Conversion'
   *  Lookup_n-D: '<S3>/Lookup'
   *  SampleTimeMath: '<S3>/Sample Time Math'
   *  UnitDelay: '<S11>/Output'
   *
   * About '<S3>/Sample Time Math':
   *  y = u * K where K = ( w * Ts )
   *   */
  rtb_AddConstant = look1_binlcpw((real_T)
    untitled_restored_from_autos_DW.Output_DSTATE_jp *
    untitled_restored_from_autosa_P.SampleTimeMath_WtEt_k,
    untitled_restored_from_autosa_P.RepeatingSequenceInterpolated2_,
    untitled_restored_from_autosa_P.Dj3, 6U) +
    untitled_restored_from_autosa_P.AddConstant2_Bias;

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

  /* Sum: '<S12>/FixPt Sum1' incorporates:
   *  Constant: '<S12>/FixPt Constant'
   *  UnitDelay: '<S11>/Output'
   */
  rtb_FixPtSum1 = (uint16_T)((uint32_T)
    untitled_restored_from_autos_DW.Output_DSTATE_jp +
    untitled_restored_from_autosa_P.FixPtConstant_Value_k);

  /* Switch: '<S13>/FixPt Switch' incorporates:
   *  Constant: '<S13>/Constant'
   *  UnitDelay: '<S11>/Output'
   */
  if (rtb_FixPtSum1 > untitled_restored_from_autosa_P.WrapToZero_Threshold_o) {
    untitled_restored_from_autos_DW.Output_DSTATE_jp =
      untitled_restored_from_autosa_P.Constant_Value_n;
  } else {
    untitled_restored_from_autos_DW.Output_DSTATE_jp = rtb_FixPtSum1;
  }

  /* End of Switch: '<S13>/FixPt Switch' */

  /* Bias: '<Root>/Add Constant3' incorporates:
   *  DataTypeConversion: '<S4>/Data Type Conversion'
   *  Lookup_n-D: '<S4>/Lookup'
   *  SampleTimeMath: '<S4>/Sample Time Math'
   *  UnitDelay: '<S14>/Output'
   *
   * About '<S4>/Sample Time Math':
   *  y = u * K where K = ( w * Ts )
   *   */
  rtb_AddConstant = look1_binlcpw((real_T)
    untitled_restored_from_autos_DW.Output_DSTATE_l *
    untitled_restored_from_autosa_P.SampleTimeMath_WtEt_h,
    untitled_restored_from_autosa_P.RepeatingSequenceInterpolated3_,
    untitled_restored_from_autosa_P.Dj4, 6U) +
    untitled_restored_from_autosa_P.AddConstant3_Bias;

  /* MATLABSystem: '<Root>/Standard Servo Write3' */
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

  MW_servoWrite(3, tmp);

  /* End of MATLABSystem: '<Root>/Standard Servo Write3' */

  /* Sum: '<S15>/FixPt Sum1' incorporates:
   *  Constant: '<S15>/FixPt Constant'
   *  UnitDelay: '<S14>/Output'
   */
  rtb_FixPtSum1 = (uint16_T)((uint32_T)
    untitled_restored_from_autos_DW.Output_DSTATE_l +
    untitled_restored_from_autosa_P.FixPtConstant_Value_h);

  /* Switch: '<S16>/FixPt Switch' incorporates:
   *  Constant: '<S16>/Constant'
   *  UnitDelay: '<S14>/Output'
   */
  if (rtb_FixPtSum1 > untitled_restored_from_autosa_P.WrapToZero_Threshold_i) {
    untitled_restored_from_autos_DW.Output_DSTATE_l =
      untitled_restored_from_autosa_P.Constant_Value_a;
  } else {
    untitled_restored_from_autos_DW.Output_DSTATE_l = rtb_FixPtSum1;
  }

  /* End of Switch: '<S16>/FixPt Switch' */

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   */
  untitled_restored_from_autos_M->Timing.taskTime0 =
    ((time_T)(++untitled_restored_from_autos_M->Timing.clockTick0)) *
    untitled_restored_from_autos_M->Timing.stepSize0;
}

/* Model initialize function */
void untitled_restored_from_autosave_initialize(void)
{
  /* Registration code */
  rtmSetTFinal(untitled_restored_from_autos_M, 15.0);
  untitled_restored_from_autos_M->Timing.stepSize0 = 0.01;

  /* External mode info */
  untitled_restored_from_autos_M->Sizes.checksums[0] = (1836750143U);
  untitled_restored_from_autos_M->Sizes.checksums[1] = (2628087798U);
  untitled_restored_from_autos_M->Sizes.checksums[2] = (4034321253U);
  untitled_restored_from_autos_M->Sizes.checksums[3] = (2895890460U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[9];
    untitled_restored_from_autos_M->extModeInfo = (&rt_ExtModeInfo);
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
    rteiSetModelMappingInfoPtr(untitled_restored_from_autos_M->extModeInfo,
      &untitled_restored_from_autos_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(untitled_restored_from_autos_M->extModeInfo,
                        untitled_restored_from_autos_M->Sizes.checksums);
    rteiSetTPtr(untitled_restored_from_autos_M->extModeInfo, rtmGetTPtr
                (untitled_restored_from_autos_M));
  }

  /* InitializeConditions for UnitDelay: '<S5>/Output' */
  untitled_restored_from_autos_DW.Output_DSTATE =
    untitled_restored_from_autosa_P.Output_InitialCondition;

  /* InitializeConditions for UnitDelay: '<S8>/Output' */
  untitled_restored_from_autos_DW.Output_DSTATE_j =
    untitled_restored_from_autosa_P.Output_InitialCondition_j;

  /* InitializeConditions for UnitDelay: '<S11>/Output' */
  untitled_restored_from_autos_DW.Output_DSTATE_jp =
    untitled_restored_from_autosa_P.Output_InitialCondition_a;

  /* InitializeConditions for UnitDelay: '<S14>/Output' */
  untitled_restored_from_autos_DW.Output_DSTATE_l =
    untitled_restored_from_autosa_P.Output_InitialCondition_i;

  /* Start for MATLABSystem: '<Root>/Standard Servo Write' */
  untitled_restored_from_autos_DW.obj_lh.matlabCodegenIsDeleted = false;
  untitled_restored_from_autos_DW.obj_lh.isInitialized = 1;
  MW_servoAttach(0, 12);
  untitled_restored_from_autos_DW.obj_lh.isSetupComplete = true;

  /* Start for MATLABSystem: '<Root>/Standard Servo Write1' */
  untitled_restored_from_autos_DW.obj_i.matlabCodegenIsDeleted = false;
  untitled_restored_from_autos_DW.obj_i.isInitialized = 1;
  MW_servoAttach(1, 13);
  untitled_restored_from_autos_DW.obj_i.isSetupComplete = true;

  /* Start for MATLABSystem: '<Root>/Standard Servo Write2' */
  untitled_restored_from_autos_DW.obj_l.matlabCodegenIsDeleted = false;
  untitled_restored_from_autos_DW.obj_l.isInitialized = 1;
  MW_servoAttach(2, 27);
  untitled_restored_from_autos_DW.obj_l.isSetupComplete = true;

  /* Start for MATLABSystem: '<Root>/Standard Servo Write3' */
  untitled_restored_from_autos_DW.obj.matlabCodegenIsDeleted = false;
  untitled_restored_from_autos_DW.obj.isInitialized = 1;
  MW_servoAttach(3, 14);
  untitled_restored_from_autos_DW.obj.isSetupComplete = true;
}

/* Model terminate function */
void untitled_restored_from_autosave_terminate(void)
{
  /* Terminate for MATLABSystem: '<Root>/Standard Servo Write' */
  if (!untitled_restored_from_autos_DW.obj_lh.matlabCodegenIsDeleted) {
    untitled_restored_from_autos_DW.obj_lh.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<Root>/Standard Servo Write' */

  /* Terminate for MATLABSystem: '<Root>/Standard Servo Write1' */
  if (!untitled_restored_from_autos_DW.obj_i.matlabCodegenIsDeleted) {
    untitled_restored_from_autos_DW.obj_i.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<Root>/Standard Servo Write1' */

  /* Terminate for MATLABSystem: '<Root>/Standard Servo Write2' */
  if (!untitled_restored_from_autos_DW.obj_l.matlabCodegenIsDeleted) {
    untitled_restored_from_autos_DW.obj_l.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<Root>/Standard Servo Write2' */

  /* Terminate for MATLABSystem: '<Root>/Standard Servo Write3' */
  if (!untitled_restored_from_autos_DW.obj.matlabCodegenIsDeleted) {
    untitled_restored_from_autos_DW.obj.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<Root>/Standard Servo Write3' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

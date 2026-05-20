/*
 * File: untitled_restored_from_autosave_data.c
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

/* Block parameters (default storage) */
P_untitled_restored_from_auto_T untitled_restored_from_autosa_P = {
  /* Variable: Dj2
   * Referenced by: '<S2>/Lookup'
   */
  { -0.7368, -18.68, -37.85, -30.67, -24.4, -18.68, -0.7368 },

  /* Variable: Dj3
   * Referenced by: '<S3>/Lookup'
   */
  { -90.0, -90.0, -90.0, -86.64, -79.5, -90.0, -90.0 },

  /* Variable: Dj4
   * Referenced by: '<S4>/Lookup'
   */
  { 180.0, 180.0, 180.0, 178.5, 175.4, 180.0, 180.0 },

  /* Variable: Dj5
   * Referenced by: '<S1>/Lookup'
   */
  { 131.7, 101.6, 85.51, 135.0, 135.0, 101.6, 131.7 },

  /* Mask Parameter: RepeatingSequenceInterpolated_T
   * Referenced by: '<S1>/Lookup'
   */
  { 0.0, 2.0, 4.0, 6.0, 8.0, 10.0, 12.0 },

  /* Mask Parameter: RepeatingSequenceInterpolated1_
   * Referenced by: '<S2>/Lookup'
   */
  { 0.0, 2.0, 4.0, 6.0, 8.0, 10.0, 12.0 },

  /* Mask Parameter: RepeatingSequenceInterpolated2_
   * Referenced by: '<S3>/Lookup'
   */
  { 0.0, 2.0, 4.0, 6.0, 8.0, 10.0, 12.0 },

  /* Mask Parameter: RepeatingSequenceInterpolated3_
   * Referenced by: '<S4>/Lookup'
   */
  { 0.0, 2.0, 4.0, 6.0, 8.0, 10.0, 12.0 },

  /* Mask Parameter: WrapToZero_Threshold
   * Referenced by: '<S7>/FixPt Switch'
   */
  1200U,

  /* Mask Parameter: WrapToZero_Threshold_g
   * Referenced by: '<S10>/FixPt Switch'
   */
  1200U,

  /* Mask Parameter: WrapToZero_Threshold_o
   * Referenced by: '<S13>/FixPt Switch'
   */
  1200U,

  /* Mask Parameter: WrapToZero_Threshold_i
   * Referenced by: '<S16>/FixPt Switch'
   */
  1200U,

  /* Computed Parameter: SampleTimeMath_WtEt
   * Referenced by: '<S1>/Sample Time Math'
   */
  0.01,

  /* Expression: -45
   * Referenced by: '<Root>/Add Constant'
   */
  -45.0,

  /* Computed Parameter: SampleTimeMath_WtEt_d
   * Referenced by: '<S2>/Sample Time Math'
   */
  0.01,

  /* Expression: 60
   * Referenced by: '<Root>/Add Constant1'
   */
  60.0,

  /* Computed Parameter: SampleTimeMath_WtEt_k
   * Referenced by: '<S3>/Sample Time Math'
   */
  0.01,

  /* Expression: 200
   * Referenced by: '<Root>/Add Constant2'
   */
  200.0,

  /* Computed Parameter: SampleTimeMath_WtEt_h
   * Referenced by: '<S4>/Sample Time Math'
   */
  0.01,

  /* Expression: 45
   * Referenced by: '<Root>/Add Constant3'
   */
  45.0,

  /* Computed Parameter: Constant_Value
   * Referenced by: '<S7>/Constant'
   */
  0U,

  /* Computed Parameter: Constant_Value_i
   * Referenced by: '<S10>/Constant'
   */
  0U,

  /* Computed Parameter: Constant_Value_n
   * Referenced by: '<S13>/Constant'
   */
  0U,

  /* Computed Parameter: Constant_Value_a
   * Referenced by: '<S16>/Constant'
   */
  0U,

  /* Computed Parameter: Output_InitialCondition
   * Referenced by: '<S5>/Output'
   */
  0U,

  /* Computed Parameter: FixPtConstant_Value
   * Referenced by: '<S6>/FixPt Constant'
   */
  1U,

  /* Computed Parameter: Output_InitialCondition_j
   * Referenced by: '<S8>/Output'
   */
  0U,

  /* Computed Parameter: FixPtConstant_Value_a
   * Referenced by: '<S9>/FixPt Constant'
   */
  1U,

  /* Computed Parameter: Output_InitialCondition_a
   * Referenced by: '<S11>/Output'
   */
  0U,

  /* Computed Parameter: FixPtConstant_Value_k
   * Referenced by: '<S12>/FixPt Constant'
   */
  1U,

  /* Computed Parameter: Output_InitialCondition_i
   * Referenced by: '<S14>/Output'
   */
  0U,

  /* Computed Parameter: FixPtConstant_Value_h
   * Referenced by: '<S15>/FixPt Constant'
   */
  1U
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

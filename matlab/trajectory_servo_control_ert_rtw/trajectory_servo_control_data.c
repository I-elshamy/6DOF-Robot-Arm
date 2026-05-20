/*
 * File: trajectory_servo_control_data.c
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

/* Block parameters (default storage) */
P_trajectory_servo_control_T trajectory_servo_control_P = {
  /* Variable: pj1
   * Referenced by: '<S6>/Lookup'
   */
  { 60.24, 64.08, 49.34, 71.22, 129.1, 138.0, 150.3, 165.4 },

  /* Variable: pj2
   * Referenced by: '<S2>/Lookup'
   */
  { -18.68, -0.7368, -1.352, -1.29, -22.21, -9.108, -1.665, -0.8548 },

  /* Variable: pj3
   * Referenced by: '<S3>/Lookup'
   */
  { -90.0, -90.0, -90.0, -90.0, -69.96, -82.95, -89.44, -90.0 },

  /* Variable: pj4
   * Referenced by: '<S4>/Lookup'
   */
  { 180.0, 180.0, 180.0, 180.0, 169.0, 175.7, 179.7, 180.0 },

  /* Variable: pj5
   * Referenced by: '<S5>/Lookup'
   */
  { 101.6, 131.7, 86.55, 89.44, 135.0, 135.0, 135.0, 135.0 },

  /* Mask Parameter: RepeatingSequenceInterpolated1_
   * Referenced by: '<S3>/Lookup'
   */
  { 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0 },

  /* Mask Parameter: RepeatingSequenceInterpolated2_
   * Referenced by: '<S4>/Lookup'
   */
  { 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0 },

  /* Mask Parameter: RepeatingSequenceInterpolated3_
   * Referenced by: '<S5>/Lookup'
   */
  { 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0 },

  /* Mask Parameter: RepeatingSequenceInterpolated_T
   * Referenced by: '<S2>/Lookup'
   */
  { 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0 },

  /* Mask Parameter: RepeatingSequenceInterpolated4_
   * Referenced by: '<S6>/Lookup'
   */
  { 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0 },

  /* Mask Parameter: WrapToZero_Threshold
   * Referenced by: '<S12>/FixPt Switch'
   */
  700U,

  /* Mask Parameter: WrapToZero_Threshold_e
   * Referenced by: '<S15>/FixPt Switch'
   */
  700U,

  /* Mask Parameter: WrapToZero_Threshold_j
   * Referenced by: '<S18>/FixPt Switch'
   */
  700U,

  /* Mask Parameter: WrapToZero_Threshold_c
   * Referenced by: '<S9>/FixPt Switch'
   */
  700U,

  /* Mask Parameter: WrapToZero_Threshold_ch
   * Referenced by: '<S21>/FixPt Switch'
   */
  700U,

  /* Computed Parameter: SampleTimeMath_WtEt
   * Referenced by: '<S3>/Sample Time Math'
   */
  0.01,

  /* Expression: 85
   * Referenced by: '<Root>/Add Constant'
   */
  85.0,

  /* Computed Parameter: SampleTimeMath_WtEt_i
   * Referenced by: '<S4>/Sample Time Math'
   */
  0.01,

  /* Expression: -180
   * Referenced by: '<Root>/Add Constant1'
   */
  -180.0,

  /* Computed Parameter: SampleTimeMath_WtEt_c
   * Referenced by: '<S5>/Sample Time Math'
   */
  0.01,

  /* Expression: -42.3
   * Referenced by: '<Root>/Add Constant3'
   */
  -42.3,

  /* Computed Parameter: SampleTimeMath_WtEt_l
   * Referenced by: '<S2>/Sample Time Math'
   */
  0.01,

  /* Expression: 85
   * Referenced by: '<Root>/Add Constant4'
   */
  85.0,

  /* Expression: 41.8128505727844
   * Referenced by: '<Root>/Constant'
   */
  41.8128505727844,

  /* Computed Parameter: SampleTimeMath_WtEt_lo
   * Referenced by: '<S6>/Sample Time Math'
   */
  0.01,

  /* Computed Parameter: Constant_Value_h
   * Referenced by: '<S9>/Constant'
   */
  0U,

  /* Computed Parameter: Constant_Value_l
   * Referenced by: '<S12>/Constant'
   */
  0U,

  /* Computed Parameter: Constant_Value_e
   * Referenced by: '<S15>/Constant'
   */
  0U,

  /* Computed Parameter: Constant_Value_a
   * Referenced by: '<S18>/Constant'
   */
  0U,

  /* Computed Parameter: Constant_Value_n
   * Referenced by: '<S21>/Constant'
   */
  0U,

  /* Computed Parameter: Output_InitialCondition
   * Referenced by: '<S10>/Output'
   */
  0U,

  /* Computed Parameter: FixPtConstant_Value
   * Referenced by: '<S11>/FixPt Constant'
   */
  1U,

  /* Computed Parameter: Output_InitialCondition_g
   * Referenced by: '<S13>/Output'
   */
  0U,

  /* Computed Parameter: FixPtConstant_Value_m
   * Referenced by: '<S14>/FixPt Constant'
   */
  1U,

  /* Computed Parameter: Output_InitialCondition_l
   * Referenced by: '<S16>/Output'
   */
  0U,

  /* Computed Parameter: FixPtConstant_Value_a
   * Referenced by: '<S17>/FixPt Constant'
   */
  1U,

  /* Computed Parameter: Output_InitialCondition_p
   * Referenced by: '<S7>/Output'
   */
  0U,

  /* Computed Parameter: FixPtConstant_Value_c
   * Referenced by: '<S8>/FixPt Constant'
   */
  1U,

  /* Computed Parameter: Output_InitialCondition_b
   * Referenced by: '<S19>/Output'
   */
  0U,

  /* Computed Parameter: FixPtConstant_Value_b
   * Referenced by: '<S20>/FixPt Constant'
   */
  1U
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

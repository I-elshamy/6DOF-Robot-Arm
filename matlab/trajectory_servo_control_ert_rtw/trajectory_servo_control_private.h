/*
 * File: trajectory_servo_control_private.h
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

#ifndef trajectory_servo_control_private_h_
#define trajectory_servo_control_private_h_
#include "rtwtypes.h"
#include "multiword_types.h"
#include "trajectory_servo_control_types.h"
#include "trajectory_servo_control.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"

/* Private macros used by the generated code to access rtModel */
#ifndef rtmSetTFinal
#define rtmSetTFinal(rtm, val)         ((rtm)->Timing.tFinal = (val))
#endif

extern real_T rt_roundd_snf(real_T u);
extern real_T look1_binlcpw(real_T u0, const real_T bp0[], const real_T table[],
  uint32_T maxIndex);

#endif                                 /* trajectory_servo_control_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

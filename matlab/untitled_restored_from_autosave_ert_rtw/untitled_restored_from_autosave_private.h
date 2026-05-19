/*
 * File: untitled_restored_from_autosave_private.h
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

#ifndef untitled_restored_from_autosave_private_h_
#define untitled_restored_from_autosave_private_h_
#include "rtwtypes.h"
#include "multiword_types.h"
#include "untitled_restored_from_autosave_types.h"
#include "untitled_restored_from_autosave.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"

/* Private macros used by the generated code to access rtModel */
#ifndef rtmSetTFinal
#define rtmSetTFinal(rtm, val)         ((rtm)->Timing.tFinal = (val))
#endif

extern real_T rt_roundd_snf(real_T u);
extern real_T look1_binlcpw(real_T u0, const real_T bp0[], const real_T table[],
  uint32_T maxIndex);

#endif                          /* untitled_restored_from_autosave_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

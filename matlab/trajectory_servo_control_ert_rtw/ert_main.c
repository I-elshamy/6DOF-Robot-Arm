/*
 * File: ert_main.c
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

#include <stdio.h>
#include <stdlib.h>
#include "trajectory_servo_control.h"
#include "trajectory_servo_control_private.h"
#include "rtwtypes.h"
#include "limits.h"
#include "ext_mode.h"
#include "MW_ArduinoHWInit.h"
#include "mw_freertos.h"
#define UNUSED(x)                      x = x
#define NAMELEN                        16

/* Function prototype declaration*/
void exitFcn(int sig);
void *terminateTask(void *arg);
void *baseRateTask(void *arg);
void *subrateTask(void *arg);
volatile boolean_T stopRequested = false;
volatile boolean_T runModel = true;
extmodeErrorCode_T errorCode;
SemaphoreHandle_t stopSem;
SemaphoreHandle_t baserateTaskSem;
SemaphoreHandle_t subrateTaskSem[1];
int taskId[1];
mw_thread_t schedulerThread;
mw_thread_t baseRateThread;
void *threadJoinStatus;
int terminatingmodel = 0;
mw_thread_t subRateThread[1];
int subratePriority[1];
extmodeSimulationTime_T getCurrentTaskTime(int tid)
{
  extmodeSimulationTime_T currentTime = 0;
  switch (tid) {
   case 1:
    currentTime = (extmodeSimulationTime_T)
      ((trajectory_servo_control_M->Timing.clockTick1) * 0.01);
    break;
  }

  return currentTime;
}

void *subrateTask(void *arg)
{
  int tid = *((int *) arg);
  int subRateId;
  subRateId = tid + 1;
  while (runModel) {
    mw_osSemaphoreWaitEver(&subrateTaskSem[tid]);
    if (terminatingmodel)
      break;

#ifdef MW_RTOS_DEBUG

    printf(" -subrate task %d semaphore received\n", subRateId);

#endif

    extmodeSimulationTime_T currentTime = getCurrentTaskTime(subRateId);
    trajectory_servo_control_step(subRateId);

    /* Get model outputs here */

    /* Trigger External Mode event */
    extmodeEvent(subRateId, currentTime);
  }

  mw_osThreadExit((void *)0);
  return NULL;
}

void *baseRateTask(void *arg)
{
  runModel = (rtmGetErrorStatus(trajectory_servo_control_M) == (NULL));
  while (runModel) {
    mw_osSemaphoreWaitEver(&baserateTaskSem);

#ifdef MW_RTOS_DEBUG

    printf("*base rate task semaphore received\n");
    fflush(stdout);

#endif

    if (rtmStepTask(trajectory_servo_control_M, 1)
        ) {
      mw_osSemaphoreRelease(&subrateTaskSem[0]);
    }

    extmodeSimulationTime_T currentTime = (extmodeSimulationTime_T)
      trajectory_servo_control_M->Timing.taskTime0;

    /* Run External Mode background activities */
    errorCode = extmodeBackgroundRun();
    if (errorCode != EXTMODE_SUCCESS) {
      /* Code to handle External Mode background task errors
         may be added here */
    }

    trajectory_servo_control_step(0);

    /* Get model outputs here */

    /* Trigger External Mode event */
    extmodeEvent(0, currentTime);
    stopRequested = !((rtmGetErrorStatus(trajectory_servo_control_M) == (NULL)));
    runModel = !stopRequested && !extmodeSimulationComplete() &&
      !extmodeStopRequested();
  }

  terminateTask(arg);
  mw_osThreadExit((void *)0);
  return NULL;
}

void exitFcn(int sig)
{
  UNUSED(sig);
  rtmSetErrorStatus(trajectory_servo_control_M, "stopping the model");
}

void *terminateTask(void *arg)
{
  UNUSED(arg);
  terminatingmodel = 1;

  {
    int i;

    /* Signal all periodic tasks to complete */
    for (i=0; i<1; i++) {
      CHECK_STATUS(mw_osSemaphoreRelease(&subrateTaskSem[i]), 0,
                   "mw_osSemaphoreRelease");
      CHECK_STATUS(mw_osSemaphoreDelete(&subrateTaskSem[i]), 0,
                   "mw_osSemaphoreDelete");
    }

    /* Wait for all periodic tasks to complete */
    for (i=0; i<1; i++) {
      CHECK_STATUS(mw_osThreadJoin(subRateThread[i], &threadJoinStatus), 0,
                   "mw_osThreadJoin");
    }

    runModel = 0;
  }

  /* Terminate model */
  trajectory_servo_control_terminate();
  extmodeReset();
  mw_osSemaphoreRelease(&stopSem);
  return NULL;
}

int app_main(int argc, char **argv)
{
  subratePriority[0] = 15;
  init();
  MW_Arduino_Init();
  rtmSetErrorStatus(trajectory_servo_control_M, 0);

  /* Parse External Mode command line arguments */
  errorCode = extmodeParseArgs(argc, (const char_T **)argv);
  if (errorCode != EXTMODE_SUCCESS) {
    return (errorCode);
  }

  /* Initialize model */
  trajectory_servo_control_initialize();

  /* External Mode initialization */
  errorCode = extmodeInit(trajectory_servo_control_M->extModeInfo, &rtmGetTFinal
    (trajectory_servo_control_M));
  if (errorCode != EXTMODE_SUCCESS) {
    /* Code to handle External Mode initialization errors
       may be added here */
  }

  if (errorCode == EXTMODE_SUCCESS) {
    /* Wait until a Start or Stop Request has been received from the Host */
    extmodeWaitForHostRequest(EXTMODE_WAIT_FOREVER);
    if (extmodeStopRequested()) {
      rtmSetStopRequested(trajectory_servo_control_M, true);
    }
  }

  /* Call RTOS Initialization function */
  mw_RTOSInit(0.005, 1);

  /* Wait for stop semaphore */
  mw_osSemaphoreWaitEver(&stopSem);

#if (MW_NUMBER_TIMER_DRIVEN_TASKS > 0)

  {
    int i;
    for (i=0; i < MW_NUMBER_TIMER_DRIVEN_TASKS; i++) {
      CHECK_STATUS(mw_osSemaphoreDelete(&timerTaskSem[i]), 0,
                   "mw_osSemaphoreDelete");
    }
  }

#endif

  return 0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

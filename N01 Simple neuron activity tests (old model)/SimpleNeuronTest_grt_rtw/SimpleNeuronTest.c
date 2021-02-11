/*
 * SimpleNeuronTest.c
 *
 * Code generation for model "SimpleNeuronTest".
 *
 * Model version              : 1.2
 * Simulink Coder version : 8.7 (R2014b) 08-Sep-2014
 * C source code generated on : Sun Jun 19 11:51:14 2016
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#include "SimpleNeuronTest.h"
#include "SimpleNeuronTest_private.h"

/* Block signals (auto storage) */
B_SimpleNeuronTest_T SimpleNeuronTest_B;

/* Continuous states */
X_SimpleNeuronTest_T SimpleNeuronTest_X;

/* Block states (auto storage) */
DW_SimpleNeuronTest_T SimpleNeuronTest_DW;

/* Real-time model */
RT_MODEL_SimpleNeuronTest_T SimpleNeuronTest_M_;
RT_MODEL_SimpleNeuronTest_T *const SimpleNeuronTest_M = &SimpleNeuronTest_M_;

/*
 * Time delay interpolation routine
 *
 * The linear interpolation is performed using the formula:
 *
 *          (t2 - tMinusDelay)         (tMinusDelay - t1)
 * u(t)  =  ----------------- * u1  +  ------------------- * u2
 *              (t2 - t1)                  (t2 - t1)
 */
real_T rt_TDelayInterpolate(
  real_T tMinusDelay,                  /* tMinusDelay = currentSimTime - delay */
  real_T tStart,
  real_T *tBuf,
  real_T *uBuf,
  int_T bufSz,
  int_T *lastIdx,
  int_T oldestIdx,
  int_T newIdx,
  real_T initOutput,
  boolean_T discrete,
  boolean_T minorStepAndTAtLastMajorOutput)
{
  int_T i;
  real_T yout, t1, t2, u1, u2;

  /*
   * If there is only one data point in the buffer, this data point must be
   * the t= 0 and tMinusDelay > t0, it ask for something unknown. The best
   * guess if initial output as well
   */
  if ((newIdx == 0) && (oldestIdx ==0 ) && (tMinusDelay > tStart))
    return initOutput;

  /*
   * If tMinusDelay is less than zero, should output initial value
   */
  if (tMinusDelay <= tStart)
    return initOutput;

  /* For fixed buffer extrapolation:
   * if tMinusDelay is small than the time at oldestIdx, if discrete, output
   * tailptr value,  else use tailptr and tailptr+1 value to extrapolate
   * It is also for fixed buffer. Note: The same condition can happen for transport delay block where
   * use tStart and and t[tail] other than using t[tail] and t[tail+1].
   * See below
   */
  if ((tMinusDelay <= tBuf[oldestIdx] ) ) {
    if (discrete) {
      return(uBuf[oldestIdx]);
    } else {
      int_T tempIdx= oldestIdx + 1;
      if (oldestIdx == bufSz-1)
        tempIdx = 0;
      t1= tBuf[oldestIdx];
      t2= tBuf[tempIdx];
      u1= uBuf[oldestIdx];
      u2= uBuf[tempIdx];
      if (t2 == t1) {
        if (tMinusDelay >= t2) {
          yout = u2;
        } else {
          yout = u1;
        }
      } else {
        real_T f1 = (t2-tMinusDelay) / (t2-t1);
        real_T f2 = 1.0 - f1;

        /*
         * Use Lagrange's interpolation formula.  Exact outputs at t1, t2.
         */
        yout = f1*u1 + f2*u2;
      }

      return yout;
    }
  }

  /*
   * When block does not have direct feedthrough, we use the table of
   * values to extrapolate off the end of the table for delays that are less
   * than 0 (less then step size).  This is not completely accurate.  The
   * chain of events is as follows for a given time t.  Major output - look
   * in table.  Update - add entry to table.  Now, if we call the output at
   * time t again, there is a new entry in the table. For very small delays,
   * this means that we will have a different answer from the previous call
   * to the output fcn at the same time t.  The following code prevents this
   * from happening.
   */
  if (minorStepAndTAtLastMajorOutput) {
    /* pretend that the new entry has not been added to table */
    if (newIdx != 0) {
      if (*lastIdx == newIdx) {
        (*lastIdx)--;
      }

      newIdx--;
    } else {
      if (*lastIdx == newIdx) {
        *lastIdx = bufSz-1;
      }

      newIdx = bufSz - 1;
    }
  }

  i = *lastIdx;
  if (tBuf[i] < tMinusDelay) {
    /* Look forward starting at last index */
    while (tBuf[i] < tMinusDelay) {
      /* May occur if the delay is less than step-size - extrapolate */
      if (i == newIdx)
        break;
      i = ( i < (bufSz-1) ) ? (i+1) : 0;/* move through buffer */
    }
  } else {
    /*
     * Look backwards starting at last index which can happen when the
     * delay time increases.
     */
    while (tBuf[i] >= tMinusDelay) {
      /*
       * Due to the entry condition at top of function, we
       * should never hit the end.
       */
      i = (i > 0) ? i-1 : (bufSz-1);   /* move through buffer */
    }

    i = ( i < (bufSz-1) ) ? (i+1) : 0;
  }

  *lastIdx = i;
  if (discrete) {
    /*
     * tempEps = 128 * eps;
     * localEps = max(tempEps, tempEps*fabs(tBuf[i]))/2;
     */
    double tempEps = (DBL_EPSILON) * 128.0;
    double localEps = tempEps * fabs(tBuf[i]);
    if (tempEps > localEps) {
      localEps = tempEps;
    }

    localEps = localEps / 2.0;
    if (tMinusDelay >= (tBuf[i] - localEps)) {
      yout = uBuf[i];
    } else {
      if (i == 0) {
        yout = uBuf[bufSz-1];
      } else {
        yout = uBuf[i-1];
      }
    }
  } else {
    if (i == 0) {
      t1 = tBuf[bufSz-1];
      u1 = uBuf[bufSz-1];
    } else {
      t1 = tBuf[i-1];
      u1 = uBuf[i-1];
    }

    t2 = tBuf[i];
    u2 = uBuf[i];
    if (t2 == t1) {
      if (tMinusDelay >= t2) {
        yout = u2;
      } else {
        yout = u1;
      }
    } else {
      real_T f1 = (t2-tMinusDelay) / (t2-t1);
      real_T f2 = 1.0 - f1;

      /*
       * Use Lagrange's interpolation formula.  Exact outputs at t1, t2.
       */
      yout = f1*u1 + f2*u2;
    }
  }

  return(yout);
}

/*
 * This function updates continuous states using the ODE1 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE1_IntgData *id = (ODE1_IntgData *)rtsiGetSolverData(si);
  real_T *f0 = id->f[0];
  int_T i;
  int_T nXc = 15;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);
  rtsiSetdX(si, f0);
  SimpleNeuronTest_derivatives();
  rtsiSetT(si, tnew);
  for (i = 0; i < nXc; i++) {
    *x += h * f0[i];
    x++;
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model step function */
void SimpleNeuronTest_step(void)
{
  /* local block i/o variables */
  real_T rtb_Integrator_f;
  real_T rtb_Integrator_i;
  real_T rtb_Gain2;
  real_T rtb_F2;
  real_T rtb_Fcn1_h;
  real_T rtb_F2_nn;
  real_T rtb_Integrator_n;
  real_T rtb_F2_l;
  real_T rtb_F2_n;
  real_T rtb_F2_f;
  real_T rtb_F2_lp;
  real_T rtb_F2_m;
  real_T rtb_F2_g;
  real_T rtb_F2_i;
  real_T rtb_F2_eo;
  real_T rtb_F2_d;
  if (rtmIsMajorTimeStep(SimpleNeuronTest_M)) {
    /* set solver stop time */
    if (!(SimpleNeuronTest_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&SimpleNeuronTest_M->solverInfo,
                            ((SimpleNeuronTest_M->Timing.clockTickH0 + 1) *
        SimpleNeuronTest_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&SimpleNeuronTest_M->solverInfo,
                            ((SimpleNeuronTest_M->Timing.clockTick0 + 1) *
        SimpleNeuronTest_M->Timing.stepSize0 +
        SimpleNeuronTest_M->Timing.clockTickH0 *
        SimpleNeuronTest_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(SimpleNeuronTest_M)) {
    SimpleNeuronTest_M->Timing.t[0] = rtsiGetT(&SimpleNeuronTest_M->solverInfo);
  }

  /* Clock: '<S2>/Clock' */
  rtb_Integrator_f = SimpleNeuronTest_M->Timing.t[0];

  /* TransportDelay: '<S2>/Transport Delay' */
  {
    real_T **uBuffer = (real_T**)
      &SimpleNeuronTest_DW.TransportDelay_PWORK.TUbufferPtrs[0];
    real_T **tBuffer = (real_T**)
      &SimpleNeuronTest_DW.TransportDelay_PWORK.TUbufferPtrs[1];
    real_T simTime = SimpleNeuronTest_M->Timing.t[0];
    real_T tMinusDelay = simTime -
      SimpleNeuronTest_P.TwooutputPulseGenerator_OOn1;
    rtb_Integrator_i = rt_TDelayInterpolate(
      tMinusDelay,
      0.0,
      *tBuffer,
      *uBuffer,
      SimpleNeuronTest_DW.TransportDelay_IWORK.CircularBufSize,
      &SimpleNeuronTest_DW.TransportDelay_IWORK.Last,
      SimpleNeuronTest_DW.TransportDelay_IWORK.Tail,
      SimpleNeuronTest_DW.TransportDelay_IWORK.Head,
      SimpleNeuronTest_P.TransportDelay_InitOutput,
      1,
      0);
  }

  /* Switch: '<S2>/Switch' incorporates:
   *  Constant: '<S2>/Constant'
   */
  if (rtb_Integrator_f >= SimpleNeuronTest_P.TwooutputPulseGenerator_OOff1) {
    SimpleNeuronTest_B.Switch = SimpleNeuronTest_P.Constant_Value;
  } else {
    SimpleNeuronTest_B.Switch = rtb_Integrator_i;
  }

  /* End of Switch: '<S2>/Switch' */

  /* TransferFcn: '<S3>/Transfer Fcn' */
  SimpleNeuronTest_B.TransferFcn = 0.0;
  SimpleNeuronTest_B.TransferFcn += SimpleNeuronTest_P.TransferFcn_C *
    SimpleNeuronTest_X.TransferFcn_CSTATE;

  /* Relay: '<S3>/Relay' */
  if (rtmIsMajorTimeStep(SimpleNeuronTest_M)) {
    if (SimpleNeuronTest_B.TransferFcn >= SimpleNeuronTest_P.IonChannel11_T) {
      SimpleNeuronTest_DW.Relay_Mode = true;
    } else {
      if (SimpleNeuronTest_B.TransferFcn <= SimpleNeuronTest_P.Relay_OffVal) {
        SimpleNeuronTest_DW.Relay_Mode = false;
      }
    }
  }

  if (SimpleNeuronTest_DW.Relay_Mode) {
    SimpleNeuronTest_B.Relay = SimpleNeuronTest_P.Relay_YOn;
  } else {
    SimpleNeuronTest_B.Relay = SimpleNeuronTest_P.Relay_YOff;
  }

  /* End of Relay: '<S3>/Relay' */

  /* Switch: '<S3>/S3' incorporates:
   *  Constant: '<S1>/C1'
   */
  if (SimpleNeuronTest_B.Relay >= SimpleNeuronTest_P.S3_Threshold) {
    SimpleNeuronTest_B.S3 = SimpleNeuronTest_P.C1_Value;
  } else {
    SimpleNeuronTest_B.S3 = SimpleNeuronTest_B.TransferFcn;
  }

  /* End of Switch: '<S3>/S3' */
  if (rtmIsMajorTimeStep(SimpleNeuronTest_M)) {
  }

  /* Integrator: '<S23>/Integrator' */
  rtb_Integrator_i = SimpleNeuronTest_X.Integrator_CSTATE;

  /* Integrator: '<S22>/Integrator' */
  rtb_Integrator_f = SimpleNeuronTest_X.Integrator_CSTATE_i;

  /* Gain: '<S1>/Gain1' incorporates:
   *  Sum: '<S1>/Sum7'
   */
  SimpleNeuronTest_B.Gain1 = (rtb_Integrator_i + rtb_Integrator_f) *
    SimpleNeuronTest_P.Gain1_Gain;
  if (rtmIsMajorTimeStep(SimpleNeuronTest_M)) {
    /* Gain: '<S1>/Gain2' incorporates:
     *  Constant: '<S1>/C2'
     */
    rtb_Gain2 = SimpleNeuronTest_P.Gain2_Gain * SimpleNeuronTest_P.C2_Value;
  }

  if (rtmIsMajorTimeStep(SimpleNeuronTest_M)) {
    /* Switch: '<S3>/S1' incorporates:
     *  Constant: '<S3>/C2'
     *  Constant: '<S3>/C3'
     */
    if (SimpleNeuronTest_B.Relay >= SimpleNeuronTest_P.S1_Threshold) {
      rtb_Integrator_n = 1.0 / SimpleNeuronTest_P.IonChannel11_RR;
    } else {
      rtb_Integrator_n = 1.0 / SimpleNeuronTest_P.IonChannel11_Rc;
    }

    /* End of Switch: '<S3>/S1' */

    /* Fcn: '<S11>/Fcn1' incorporates:
     *  Fcn: '<S3>/F1'
     */
    SimpleNeuronTest_B.Fcn1 = 1.0 / (0.001 / rtb_Integrator_n);
  }

  if (rtmIsMajorTimeStep(SimpleNeuronTest_M)) {
    /* Switch: '<S3>/S2' incorporates:
     *  Constant: '<S1>/C1'
     *  Constant: '<S3>/C5'
     */
    if (SimpleNeuronTest_B.Relay >= SimpleNeuronTest_P.S2_Threshold) {
      SimpleNeuronTest_B.S2 = SimpleNeuronTest_P.C1_Value;
    } else {
      SimpleNeuronTest_B.S2 = SimpleNeuronTest_P.C5_Value;
    }

    /* End of Switch: '<S3>/S2' */
  }

  /* Sum: '<S11>/Sum' incorporates:
   *  Integrator: '<S11>/Integrator'
   *  Product: '<S11>/Product'
   *  Product: '<S11>/Product1'
   *  Sum: '<S3>/Sum2'
   */
  SimpleNeuronTest_B.Sum = (SimpleNeuronTest_B.S2 +
    SimpleNeuronTest_B.TransferFcn) * SimpleNeuronTest_B.Fcn1 -
    SimpleNeuronTest_X.Integrator_CSTATE_c * SimpleNeuronTest_B.Fcn1;
  if (rtmIsMajorTimeStep(SimpleNeuronTest_M)) {
    /* Sum: '<S12>/Sum5' incorporates:
     *  Constant: '<S4>/ARm'
     *  Fcn: '<S12>/F4'
     */
    SimpleNeuronTest_B.Sum5 = 1.0 / SimpleNeuronTest_P.NeuroMembrane_ARm;

    /* Fcn: '<S12>/F2' incorporates:
     *  Constant: '<S4>/ARm'
     */
    rtb_F2 = SimpleNeuronTest_P.NeuroMembrane_ARm;
  }

  /* Fcn: '<S14>/Fcn1' incorporates:
   *  Constant: '<S4>/ACm'
   *  Fcn: '<S12>/F3'
   *  Integrator: '<S14>/Integrator'
   *  Integrator: '<S18>/Integrator'
   *  Product: '<S12>/Divide'
   *  Sum: '<S12>/Sum1'
   */
  rtb_Fcn1_h = 1.0 / (1.0 / (fabs(SimpleNeuronTest_X.Integrator_CSTATE_d -
    SimpleNeuronTest_X.Integrator_CSTATE_al) + 1.0) *
                      SimpleNeuronTest_P.NeuroMembrane_ACm /
                      SimpleNeuronTest_B.Sum5);
  if (rtmIsMajorTimeStep(SimpleNeuronTest_M)) {
    /* Product: '<S12>/Product' */
    SimpleNeuronTest_B.Product = 0.0 * rtb_F2;
  }

  /* Sum: '<S14>/Sum' incorporates:
   *  Integrator: '<S14>/Integrator'
   *  Integrator: '<S18>/Integrator'
   *  Product: '<S12>/P1'
   *  Product: '<S14>/Product'
   *  Product: '<S14>/Product1'
   *  Sum: '<S12>/Sum4'
   */
  SimpleNeuronTest_B.Sum_a = (SimpleNeuronTest_X.Integrator_CSTATE_al -
    SimpleNeuronTest_X.Integrator_CSTATE_d * SimpleNeuronTest_B.Product) *
    rtb_Fcn1_h - SimpleNeuronTest_X.Integrator_CSTATE_d * rtb_Fcn1_h;
  if (rtmIsMajorTimeStep(SimpleNeuronTest_M)) {
    /* Sum: '<S13>/Sum5' incorporates:
     *  Constant: '<S4>/ERm'
     *  Fcn: '<S13>/F4'
     */
    SimpleNeuronTest_B.Sum5_l = 1.0 / SimpleNeuronTest_P.NeuroMembrane_ERm;

    /* Fcn: '<S13>/F2' incorporates:
     *  Constant: '<S4>/ERm'
     */
    rtb_F2_nn = SimpleNeuronTest_P.NeuroMembrane_ERm;
  }

  /* Fcn: '<S15>/Fcn1' incorporates:
   *  Constant: '<S4>/ECm'
   *  Fcn: '<S13>/F3'
   *  Integrator: '<S15>/Integrator'
   *  Integrator: '<S19>/Integrator'
   *  Product: '<S13>/Divide'
   *  Sum: '<S13>/Sum1'
   */
  rtb_F2 = 1.0 / (1.0 / (fabs(SimpleNeuronTest_X.Integrator_CSTATE_b -
    SimpleNeuronTest_X.Integrator_CSTATE_ds) + 1.0) *
                  SimpleNeuronTest_P.NeuroMembrane_ECm /
                  SimpleNeuronTest_B.Sum5_l);
  if (rtmIsMajorTimeStep(SimpleNeuronTest_M)) {
    /* Product: '<S13>/Product' */
    SimpleNeuronTest_B.Product_f = 0.0 * rtb_F2_nn;
  }

  /* Sum: '<S15>/Sum' incorporates:
   *  Integrator: '<S15>/Integrator'
   *  Integrator: '<S19>/Integrator'
   *  Product: '<S13>/P1'
   *  Product: '<S15>/Product'
   *  Product: '<S15>/Product1'
   *  Sum: '<S13>/Sum4'
   */
  SimpleNeuronTest_B.Sum_l = (SimpleNeuronTest_X.Integrator_CSTATE_ds -
    SimpleNeuronTest_X.Integrator_CSTATE_b * SimpleNeuronTest_B.Product_f) *
    rtb_F2 - SimpleNeuronTest_X.Integrator_CSTATE_b * rtb_F2;
  if (rtmIsMajorTimeStep(SimpleNeuronTest_M)) {
    /* Sum: '<S5>/Sum2' */
    SimpleNeuronTest_B.Sum2 = rtb_Gain2;

    /* Fcn: '<S16>/F4' incorporates:
     *  Constant: '<S5>/ARm'
     */
    SimpleNeuronTest_B.F4 = 1.0 / SimpleNeuronTest_P.NeuroMembrane1_ARm;
  }

  /* Gain: '<S10>/Gain' incorporates:
   *  Fcn: '<S10>/Fcn'
   *  Integrator: '<S36>/Integrator'
   *  Sum: '<S10>/Sum'
   */
  rtb_Integrator_n = SimpleNeuronTest_P.Synapse1_gamma * 4.0 *
    SimpleNeuronTest_P.Synapse1_ksi * (SimpleNeuronTest_X.Integrator_CSTATE_df -
    SimpleNeuronTest_X.Integrator_CSTATE_df *
    SimpleNeuronTest_X.Integrator_CSTATE_df);

  /* Switch: '<S10>/Switch1' incorporates:
   *  Constant: '<S10>/Constant1'
   */
  if (!(rtb_Integrator_n >= SimpleNeuronTest_P.Switch1_Threshold)) {
    rtb_Integrator_n = SimpleNeuronTest_P.Constant1_Value;
  }

  /* End of Switch: '<S10>/Switch1' */
  if (rtmIsMajorTimeStep(SimpleNeuronTest_M)) {
    /* Fcn: '<S16>/F2' incorporates:
     *  Constant: '<S5>/ARm'
     */
    SimpleNeuronTest_B.F2 = SimpleNeuronTest_P.NeuroMembrane1_ARm;
  }

  /* Fcn: '<S18>/Fcn1' incorporates:
   *  Constant: '<S5>/ACm'
   *  Fcn: '<S16>/F3'
   *  Integrator: '<S18>/Integrator'
   *  Product: '<S16>/Divide'
   *  Sum: '<S16>/Sum1'
   *  Sum: '<S16>/Sum5'
   */
  rtb_F2 = 1.0 / (1.0 / (fabs(SimpleNeuronTest_X.Integrator_CSTATE_al -
    SimpleNeuronTest_B.Sum2) + 1.0) * SimpleNeuronTest_P.NeuroMembrane1_ACm /
                  (SimpleNeuronTest_B.F4 + rtb_Integrator_n));

  /* Sum: '<S18>/Sum' incorporates:
   *  Integrator: '<S18>/Integrator'
   *  Product: '<S16>/P1'
   *  Product: '<S16>/Product'
   *  Product: '<S18>/Product'
   *  Product: '<S18>/Product1'
   *  Sum: '<S16>/Sum4'
   */
  SimpleNeuronTest_B.Sum_h = (SimpleNeuronTest_B.Sum2 - rtb_Integrator_n *
    SimpleNeuronTest_B.F2 * SimpleNeuronTest_X.Integrator_CSTATE_al) * rtb_F2 -
    SimpleNeuronTest_X.Integrator_CSTATE_al * rtb_F2;
  if (rtmIsMajorTimeStep(SimpleNeuronTest_M)) {
    /* Sum: '<S5>/Sum1' incorporates:
     *  Constant: '<S1>/C2'
     */
    SimpleNeuronTest_B.Sum1 = SimpleNeuronTest_P.C2_Value;

    /* Sum: '<S17>/Sum5' incorporates:
     *  Constant: '<S5>/ERm'
     *  Fcn: '<S17>/F4'
     */
    SimpleNeuronTest_B.Sum5_o = 1.0 / SimpleNeuronTest_P.NeuroMembrane1_ERm;

    /* Fcn: '<S17>/F2' incorporates:
     *  Constant: '<S5>/ERm'
     */
    rtb_F2_l = SimpleNeuronTest_P.NeuroMembrane1_ERm;
  }

  /* Fcn: '<S19>/Fcn1' incorporates:
   *  Constant: '<S5>/ECm'
   *  Fcn: '<S17>/F3'
   *  Integrator: '<S19>/Integrator'
   *  Product: '<S17>/Divide'
   *  Sum: '<S17>/Sum1'
   */
  rtb_F2 = 1.0 / (1.0 / (fabs(SimpleNeuronTest_X.Integrator_CSTATE_ds -
    SimpleNeuronTest_B.Sum1) + 1.0) * SimpleNeuronTest_P.NeuroMembrane1_ECm /
                  SimpleNeuronTest_B.Sum5_o);
  if (rtmIsMajorTimeStep(SimpleNeuronTest_M)) {
    /* Product: '<S17>/Product' */
    SimpleNeuronTest_B.Product_e = 0.0 * rtb_F2_l;
  }

  /* Sum: '<S19>/Sum' incorporates:
   *  Integrator: '<S19>/Integrator'
   *  Product: '<S17>/P1'
   *  Product: '<S19>/Product'
   *  Product: '<S19>/Product1'
   *  Sum: '<S17>/Sum4'
   */
  SimpleNeuronTest_B.Sum_lf = (SimpleNeuronTest_B.Sum1 -
    SimpleNeuronTest_X.Integrator_CSTATE_ds * SimpleNeuronTest_B.Product_e) *
    rtb_F2 - SimpleNeuronTest_X.Integrator_CSTATE_ds * rtb_F2;

  /* Sum: '<S6>/Sum2' incorporates:
   *  Integrator: '<S26>/Integrator'
   */
  rtb_F2 = SimpleNeuronTest_X.Integrator_CSTATE_in - SimpleNeuronTest_B.S2;
  if (rtmIsMajorTimeStep(SimpleNeuronTest_M)) {
    /* Sum: '<S20>/Sum5' incorporates:
     *  Constant: '<S6>/ARm'
     *  Fcn: '<S20>/F4'
     */
    SimpleNeuronTest_B.Sum5_j = 1.0 / SimpleNeuronTest_P.NeuroMembrane2_ARm;

    /* Fcn: '<S20>/F2' incorporates:
     *  Constant: '<S6>/ARm'
     */
    rtb_F2_n = SimpleNeuronTest_P.NeuroMembrane2_ARm;
  }

  /* Fcn: '<S22>/Fcn1' incorporates:
   *  Constant: '<S6>/ACm'
   *  Fcn: '<S20>/F3'
   *  Product: '<S20>/Divide'
   *  Sum: '<S20>/Sum1'
   */
  rtb_Integrator_n = 1.0 / (1.0 / (fabs(rtb_Integrator_f - rtb_F2) + 1.0) *
    SimpleNeuronTest_P.NeuroMembrane2_ACm / SimpleNeuronTest_B.Sum5_j);
  if (rtmIsMajorTimeStep(SimpleNeuronTest_M)) {
    /* Product: '<S20>/Product' */
    SimpleNeuronTest_B.Product_h = 0.0 * rtb_F2_n;
  }

  /* Sum: '<S22>/Sum' incorporates:
   *  Product: '<S20>/P1'
   *  Product: '<S22>/Product'
   *  Product: '<S22>/Product1'
   *  Sum: '<S20>/Sum4'
   */
  SimpleNeuronTest_B.Sum_g = (rtb_F2 - rtb_Integrator_f *
    SimpleNeuronTest_B.Product_h) * rtb_Integrator_n - rtb_Integrator_f *
    rtb_Integrator_n;

  /* Sum: '<S6>/Sum1' incorporates:
   *  Integrator: '<S27>/Integrator'
   */
  rtb_Integrator_n = SimpleNeuronTest_X.Integrator_CSTATE_e -
    SimpleNeuronTest_B.S2;
  if (rtmIsMajorTimeStep(SimpleNeuronTest_M)) {
    /* Sum: '<S21>/Sum5' incorporates:
     *  Constant: '<S6>/ERm'
     *  Fcn: '<S21>/F4'
     */
    SimpleNeuronTest_B.Sum5_c = 1.0 / SimpleNeuronTest_P.NeuroMembrane2_ERm;

    /* Fcn: '<S21>/F2' incorporates:
     *  Constant: '<S6>/ERm'
     */
    rtb_F2_f = SimpleNeuronTest_P.NeuroMembrane2_ERm;
  }

  /* Fcn: '<S23>/Fcn1' incorporates:
   *  Constant: '<S6>/ECm'
   *  Fcn: '<S21>/F3'
   *  Product: '<S21>/Divide'
   *  Sum: '<S21>/Sum1'
   */
  rtb_F2 = 1.0 / (1.0 / (fabs(rtb_Integrator_i - rtb_Integrator_n) + 1.0) *
                  SimpleNeuronTest_P.NeuroMembrane2_ECm /
                  SimpleNeuronTest_B.Sum5_c);
  if (rtmIsMajorTimeStep(SimpleNeuronTest_M)) {
    /* Product: '<S21>/Product' */
    SimpleNeuronTest_B.Product_p = 0.0 * rtb_F2_f;
  }

  /* Sum: '<S23>/Sum' incorporates:
   *  Product: '<S21>/P1'
   *  Product: '<S23>/Product'
   *  Product: '<S23>/Product1'
   *  Sum: '<S21>/Sum4'
   */
  SimpleNeuronTest_B.Sum_n = (rtb_Integrator_n - rtb_Integrator_i *
    SimpleNeuronTest_B.Product_p) * rtb_F2 - rtb_Integrator_i * rtb_F2;

  /* Sum: '<S7>/Sum2' incorporates:
   *  Gain: '<S1>/Gain3'
   *  Integrator: '<S14>/Integrator'
   *  Integrator: '<S34>/Integrator'
   *  Sum: '<S1>/Sum3'
   */
  rtb_Integrator_n = (SimpleNeuronTest_X.Integrator_CSTATE_d +
                      SimpleNeuronTest_X.Integrator_CSTATE_a) *
    SimpleNeuronTest_P.Gain3_Gain;
  if (rtmIsMajorTimeStep(SimpleNeuronTest_M)) {
    /* Sum: '<S24>/Sum5' incorporates:
     *  Constant: '<S7>/ARm'
     *  Fcn: '<S24>/F4'
     */
    SimpleNeuronTest_B.Sum5_lq = 1.0 / SimpleNeuronTest_P.NeuroMembrane3_ARm;

    /* Fcn: '<S24>/F2' incorporates:
     *  Constant: '<S7>/ARm'
     */
    rtb_F2_lp = SimpleNeuronTest_P.NeuroMembrane3_ARm;
  }

  /* Fcn: '<S26>/Fcn1' incorporates:
   *  Constant: '<S7>/ACm'
   *  Fcn: '<S24>/F3'
   *  Integrator: '<S26>/Integrator'
   *  Product: '<S24>/Divide'
   *  Sum: '<S24>/Sum1'
   */
  rtb_F2 = 1.0 / (1.0 / (fabs(SimpleNeuronTest_X.Integrator_CSTATE_in -
    rtb_Integrator_n) + 1.0) * SimpleNeuronTest_P.NeuroMembrane3_ACm /
                  SimpleNeuronTest_B.Sum5_lq);
  if (rtmIsMajorTimeStep(SimpleNeuronTest_M)) {
    /* Product: '<S24>/Product' */
    SimpleNeuronTest_B.Product_n = 0.0 * rtb_F2_lp;
  }

  /* Sum: '<S26>/Sum' incorporates:
   *  Integrator: '<S26>/Integrator'
   *  Product: '<S24>/P1'
   *  Product: '<S26>/Product'
   *  Product: '<S26>/Product1'
   *  Sum: '<S24>/Sum4'
   */
  SimpleNeuronTest_B.Sum_k = (rtb_Integrator_n -
    SimpleNeuronTest_X.Integrator_CSTATE_in * SimpleNeuronTest_B.Product_n) *
    rtb_F2 - SimpleNeuronTest_X.Integrator_CSTATE_in * rtb_F2;

  /* Sum: '<S7>/Sum1' incorporates:
   *  Gain: '<S1>/Gain4'
   *  Integrator: '<S15>/Integrator'
   *  Integrator: '<S35>/Integrator'
   *  Sum: '<S1>/Sum2'
   */
  rtb_Fcn1_h = (SimpleNeuronTest_X.Integrator_CSTATE_b +
                SimpleNeuronTest_X.Integrator_CSTATE_g) *
    SimpleNeuronTest_P.Gain4_Gain;
  if (rtmIsMajorTimeStep(SimpleNeuronTest_M)) {
    /* Sum: '<S25>/Sum5' incorporates:
     *  Constant: '<S7>/ERm'
     *  Fcn: '<S25>/F4'
     */
    SimpleNeuronTest_B.Sum5_g = 1.0 / SimpleNeuronTest_P.NeuroMembrane3_ERm;

    /* Fcn: '<S25>/F2' incorporates:
     *  Constant: '<S7>/ERm'
     */
    rtb_F2_m = SimpleNeuronTest_P.NeuroMembrane3_ERm;
  }

  /* Fcn: '<S27>/Fcn1' incorporates:
   *  Constant: '<S7>/ECm'
   *  Fcn: '<S25>/F3'
   *  Integrator: '<S27>/Integrator'
   *  Product: '<S25>/Divide'
   *  Sum: '<S25>/Sum1'
   */
  rtb_Integrator_n = 1.0 / (1.0 / (fabs(SimpleNeuronTest_X.Integrator_CSTATE_e -
    rtb_Fcn1_h) + 1.0) * SimpleNeuronTest_P.NeuroMembrane3_ECm /
    SimpleNeuronTest_B.Sum5_g);
  if (rtmIsMajorTimeStep(SimpleNeuronTest_M)) {
    /* Product: '<S25>/Product' */
    SimpleNeuronTest_B.Product_a = 0.0 * rtb_F2_m;
  }

  /* Sum: '<S27>/Sum' incorporates:
   *  Integrator: '<S27>/Integrator'
   *  Product: '<S25>/P1'
   *  Product: '<S27>/Product'
   *  Product: '<S27>/Product1'
   *  Sum: '<S25>/Sum4'
   */
  SimpleNeuronTest_B.Sum_p = (rtb_Fcn1_h -
    SimpleNeuronTest_X.Integrator_CSTATE_e * SimpleNeuronTest_B.Product_a) *
    rtb_Integrator_n - SimpleNeuronTest_X.Integrator_CSTATE_e * rtb_Integrator_n;
  if (rtmIsMajorTimeStep(SimpleNeuronTest_M)) {
    /* Sum: '<S8>/Sum2' */
    SimpleNeuronTest_B.Sum2_e = rtb_Gain2 - SimpleNeuronTest_B.S2;

    /* Sum: '<S28>/Sum5' incorporates:
     *  Constant: '<S8>/ARm'
     *  Fcn: '<S28>/F4'
     */
    SimpleNeuronTest_B.Sum5_jq = 1.0 / SimpleNeuronTest_P.NeuroMembrane4_ARm;

    /* Fcn: '<S28>/F2' incorporates:
     *  Constant: '<S8>/ARm'
     */
    rtb_F2_g = SimpleNeuronTest_P.NeuroMembrane4_ARm;
  }

  /* Fcn: '<S30>/Fcn1' incorporates:
   *  Constant: '<S8>/ACm'
   *  Fcn: '<S28>/F3'
   *  Integrator: '<S30>/Integrator'
   *  Product: '<S28>/Divide'
   *  Sum: '<S28>/Sum1'
   */
  rtb_F2 = 1.0 / (1.0 / (fabs(SimpleNeuronTest_X.Integrator_CSTATE_ic -
    SimpleNeuronTest_B.Sum2_e) + 1.0) * SimpleNeuronTest_P.NeuroMembrane4_ACm /
                  SimpleNeuronTest_B.Sum5_jq);
  if (rtmIsMajorTimeStep(SimpleNeuronTest_M)) {
    /* Product: '<S28>/Product' */
    SimpleNeuronTest_B.Product_d = 0.0 * rtb_F2_g;
  }

  /* Sum: '<S30>/Sum' incorporates:
   *  Integrator: '<S30>/Integrator'
   *  Product: '<S28>/P1'
   *  Product: '<S30>/Product'
   *  Product: '<S30>/Product1'
   *  Sum: '<S28>/Sum4'
   */
  SimpleNeuronTest_B.Sum_ps = (SimpleNeuronTest_B.Sum2_e -
    SimpleNeuronTest_X.Integrator_CSTATE_ic * SimpleNeuronTest_B.Product_d) *
    rtb_F2 - SimpleNeuronTest_X.Integrator_CSTATE_ic * rtb_F2;
  if (rtmIsMajorTimeStep(SimpleNeuronTest_M)) {
    /* Sum: '<S8>/Sum1' incorporates:
     *  Constant: '<S1>/C2'
     */
    SimpleNeuronTest_B.Sum1_n = SimpleNeuronTest_P.C2_Value -
      SimpleNeuronTest_B.S2;

    /* Sum: '<S29>/Sum5' incorporates:
     *  Constant: '<S8>/ERm'
     *  Fcn: '<S29>/F4'
     */
    SimpleNeuronTest_B.Sum5_i = 1.0 / SimpleNeuronTest_P.NeuroMembrane4_ERm;

    /* Fcn: '<S29>/F2' incorporates:
     *  Constant: '<S8>/ERm'
     */
    rtb_F2_i = SimpleNeuronTest_P.NeuroMembrane4_ERm;
  }

  /* Fcn: '<S31>/Fcn1' incorporates:
   *  Constant: '<S8>/ECm'
   *  Fcn: '<S29>/F3'
   *  Integrator: '<S31>/Integrator'
   *  Product: '<S29>/Divide'
   *  Sum: '<S29>/Sum1'
   */
  rtb_F2 = 1.0 / (1.0 / (fabs(SimpleNeuronTest_X.Integrator_CSTATE_ay -
    SimpleNeuronTest_B.Sum1_n) + 1.0) * SimpleNeuronTest_P.NeuroMembrane4_ECm /
                  SimpleNeuronTest_B.Sum5_i);
  if (rtmIsMajorTimeStep(SimpleNeuronTest_M)) {
    /* Product: '<S29>/Product' */
    SimpleNeuronTest_B.Product_k = 0.0 * rtb_F2_i;
  }

  /* Sum: '<S31>/Sum' incorporates:
   *  Integrator: '<S31>/Integrator'
   *  Product: '<S29>/P1'
   *  Product: '<S31>/Product'
   *  Product: '<S31>/Product1'
   *  Sum: '<S29>/Sum4'
   */
  SimpleNeuronTest_B.Sum_m = (SimpleNeuronTest_B.Sum1_n -
    SimpleNeuronTest_X.Integrator_CSTATE_ay * SimpleNeuronTest_B.Product_k) *
    rtb_F2 - SimpleNeuronTest_X.Integrator_CSTATE_ay * rtb_F2;
  if (rtmIsMajorTimeStep(SimpleNeuronTest_M)) {
    /* Sum: '<S9>/Sum2' */
    SimpleNeuronTest_B.Sum2_k = rtb_Gain2;

    /* Sum: '<S32>/Sum5' incorporates:
     *  Constant: '<S9>/ARm'
     *  Fcn: '<S32>/F4'
     */
    SimpleNeuronTest_B.Sum5_p = 1.0 / SimpleNeuronTest_P.NeuroMembrane5_ARm;

    /* Fcn: '<S32>/F2' incorporates:
     *  Constant: '<S9>/ARm'
     */
    rtb_F2_eo = SimpleNeuronTest_P.NeuroMembrane5_ARm;
  }

  /* Fcn: '<S34>/Fcn1' incorporates:
   *  Constant: '<S9>/ACm'
   *  Fcn: '<S32>/F3'
   *  Integrator: '<S34>/Integrator'
   *  Product: '<S32>/Divide'
   *  Sum: '<S32>/Sum1'
   */
  rtb_Fcn1_h = 1.0 / (1.0 / (fabs(SimpleNeuronTest_X.Integrator_CSTATE_a -
    SimpleNeuronTest_B.Sum2_k) + 1.0) * SimpleNeuronTest_P.NeuroMembrane5_ACm /
                      SimpleNeuronTest_B.Sum5_p);
  if (rtmIsMajorTimeStep(SimpleNeuronTest_M)) {
    /* Product: '<S32>/Product' */
    SimpleNeuronTest_B.Product_m = 0.0 * rtb_F2_eo;
  }

  /* Sum: '<S34>/Sum' incorporates:
   *  Integrator: '<S34>/Integrator'
   *  Product: '<S32>/P1'
   *  Product: '<S34>/Product'
   *  Product: '<S34>/Product1'
   *  Sum: '<S32>/Sum4'
   */
  SimpleNeuronTest_B.Sum_d = (SimpleNeuronTest_B.Sum2_k -
    SimpleNeuronTest_X.Integrator_CSTATE_a * SimpleNeuronTest_B.Product_m) *
    rtb_Fcn1_h - SimpleNeuronTest_X.Integrator_CSTATE_a * rtb_Fcn1_h;
  if (rtmIsMajorTimeStep(SimpleNeuronTest_M)) {
    /* Sum: '<S9>/Sum1' incorporates:
     *  Constant: '<S1>/C2'
     */
    SimpleNeuronTest_B.Sum1_j = SimpleNeuronTest_P.C2_Value;

    /* Sum: '<S33>/Sum5' incorporates:
     *  Constant: '<S9>/ERm'
     *  Fcn: '<S33>/F4'
     */
    SimpleNeuronTest_B.Sum5_d = 1.0 / SimpleNeuronTest_P.NeuroMembrane5_ERm;

    /* Fcn: '<S33>/F2' incorporates:
     *  Constant: '<S9>/ERm'
     */
    rtb_F2_d = SimpleNeuronTest_P.NeuroMembrane5_ERm;
  }

  /* Fcn: '<S35>/Fcn1' incorporates:
   *  Constant: '<S9>/ECm'
   *  Fcn: '<S33>/F3'
   *  Integrator: '<S35>/Integrator'
   *  Product: '<S33>/Divide'
   *  Sum: '<S33>/Sum1'
   */
  rtb_Fcn1_h = 1.0 / (1.0 / (fabs(SimpleNeuronTest_X.Integrator_CSTATE_g -
    SimpleNeuronTest_B.Sum1_j) + 1.0) * SimpleNeuronTest_P.NeuroMembrane5_ECm /
                      SimpleNeuronTest_B.Sum5_d);
  if (rtmIsMajorTimeStep(SimpleNeuronTest_M)) {
    /* Product: '<S33>/Product' */
    SimpleNeuronTest_B.Product_j = 0.0 * rtb_F2_d;
  }

  /* Sum: '<S35>/Sum' incorporates:
   *  Integrator: '<S35>/Integrator'
   *  Product: '<S33>/P1'
   *  Product: '<S35>/Product'
   *  Product: '<S35>/Product1'
   *  Sum: '<S33>/Sum4'
   */
  SimpleNeuronTest_B.Sum_kc = (SimpleNeuronTest_B.Sum1_j -
    SimpleNeuronTest_X.Integrator_CSTATE_g * SimpleNeuronTest_B.Product_j) *
    rtb_Fcn1_h - SimpleNeuronTest_X.Integrator_CSTATE_g * rtb_Fcn1_h;

  /* Switch: '<S10>/Switch2' incorporates:
   *  Constant: '<S10>/Constant4'
   *  Constant: '<S10>/Constant5'
   */
  if (SimpleNeuronTest_B.Switch >= SimpleNeuronTest_P.Switch2_Threshold) {
    rtb_Integrator_n = SimpleNeuronTest_P.Synapse1_SecretionTC;
  } else {
    rtb_Integrator_n = SimpleNeuronTest_P.Synapse1_DecompositionTC;
  }

  /* End of Switch: '<S10>/Switch2' */

  /* Fcn: '<S36>/Fcn1' */
  rtb_Fcn1_h = 1.0 / rtb_Integrator_n;

  /* Sum: '<S36>/Sum' incorporates:
   *  Gain: '<S10>/Gain1'
   *  Integrator: '<S36>/Integrator'
   *  Product: '<S36>/Product'
   *  Product: '<S36>/Product1'
   */
  SimpleNeuronTest_B.Sum_ds = SimpleNeuronTest_P.Gain1_Gain_o *
    SimpleNeuronTest_B.Switch * rtb_Fcn1_h -
    SimpleNeuronTest_X.Integrator_CSTATE_df * rtb_Fcn1_h;
  if (rtmIsMajorTimeStep(SimpleNeuronTest_M)) {
    /* DiscretePulseGenerator: '<S2>/Discrete Pulse Generator' */
    SimpleNeuronTest_B.DiscretePulseGenerator =
      (SimpleNeuronTest_DW.clockTickCounter <
       SimpleNeuronTest_P.TwooutputPulseGenerator_PW) &&
      (SimpleNeuronTest_DW.clockTickCounter >= 0) ?
      SimpleNeuronTest_P.TwooutputPulseGenerator_A : 0.0;
    if (SimpleNeuronTest_DW.clockTickCounter >=
        SimpleNeuronTest_P.TwooutputPulseGenerator_P1 - 1.0) {
      SimpleNeuronTest_DW.clockTickCounter = 0;
    } else {
      SimpleNeuronTest_DW.clockTickCounter++;
    }

    /* End of DiscretePulseGenerator: '<S2>/Discrete Pulse Generator' */
  }

  if (rtmIsMajorTimeStep(SimpleNeuronTest_M)) {
    /* Matfile logging */
    rt_UpdateTXYLogVars(SimpleNeuronTest_M->rtwLogInfo,
                        (SimpleNeuronTest_M->Timing.t));
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(SimpleNeuronTest_M)) {
    /* Update for TransportDelay: '<S2>/Transport Delay' */
    {
      real_T **uBuffer = (real_T**)
        &SimpleNeuronTest_DW.TransportDelay_PWORK.TUbufferPtrs[0];
      real_T **tBuffer = (real_T**)
        &SimpleNeuronTest_DW.TransportDelay_PWORK.TUbufferPtrs[1];
      real_T simTime = SimpleNeuronTest_M->Timing.t[0];
      SimpleNeuronTest_DW.TransportDelay_IWORK.Head =
        ((SimpleNeuronTest_DW.TransportDelay_IWORK.Head <
          (SimpleNeuronTest_DW.TransportDelay_IWORK.CircularBufSize-1)) ?
         (SimpleNeuronTest_DW.TransportDelay_IWORK.Head+1) : 0);
      if (SimpleNeuronTest_DW.TransportDelay_IWORK.Head ==
          SimpleNeuronTest_DW.TransportDelay_IWORK.Tail) {
        SimpleNeuronTest_DW.TransportDelay_IWORK.Tail =
          ((SimpleNeuronTest_DW.TransportDelay_IWORK.Tail <
            (SimpleNeuronTest_DW.TransportDelay_IWORK.CircularBufSize-1)) ?
           (SimpleNeuronTest_DW.TransportDelay_IWORK.Tail+1) : 0);
      }

      (*tBuffer)[SimpleNeuronTest_DW.TransportDelay_IWORK.Head] = simTime;
      (*uBuffer)[SimpleNeuronTest_DW.TransportDelay_IWORK.Head] =
        SimpleNeuronTest_B.DiscretePulseGenerator;
    }
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(SimpleNeuronTest_M)) {
    /* signal main to stop simulation */
    {                                  /* Sample time: [0.0s, 0.0s] */
      if ((rtmGetTFinal(SimpleNeuronTest_M)!=-1) &&
          !((rtmGetTFinal(SimpleNeuronTest_M)-
             (((SimpleNeuronTest_M->Timing.clockTick1+
                SimpleNeuronTest_M->Timing.clockTickH1* 4294967296.0)) * 0.001))
            > (((SimpleNeuronTest_M->Timing.clockTick1+
                 SimpleNeuronTest_M->Timing.clockTickH1* 4294967296.0)) * 0.001)
            * (DBL_EPSILON))) {
        rtmSetErrorStatus(SimpleNeuronTest_M, "Simulation finished");
      }
    }

    rt_ertODEUpdateContinuousStates(&SimpleNeuronTest_M->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick0 and the high bits
     * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++SimpleNeuronTest_M->Timing.clockTick0)) {
      ++SimpleNeuronTest_M->Timing.clockTickH0;
    }

    SimpleNeuronTest_M->Timing.t[0] = rtsiGetSolverStopTime
      (&SimpleNeuronTest_M->solverInfo);

    {
      /* Update absolute timer for sample time: [0.001s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.001, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       * Timer of this task consists of two 32 bit unsigned integers.
       * The two integers represent the low bits Timing.clockTick1 and the high bits
       * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
       */
      SimpleNeuronTest_M->Timing.clockTick1++;
      if (!SimpleNeuronTest_M->Timing.clockTick1) {
        SimpleNeuronTest_M->Timing.clockTickH1++;
      }
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void SimpleNeuronTest_derivatives(void)
{
  XDot_SimpleNeuronTest_T *_rtXdot;
  _rtXdot = ((XDot_SimpleNeuronTest_T *) SimpleNeuronTest_M->ModelData.derivs);

  /* Derivatives for TransferFcn: '<S3>/Transfer Fcn' */
  _rtXdot->TransferFcn_CSTATE = 0.0;
  _rtXdot->TransferFcn_CSTATE += SimpleNeuronTest_P.TransferFcn_A *
    SimpleNeuronTest_X.TransferFcn_CSTATE;
  _rtXdot->TransferFcn_CSTATE += SimpleNeuronTest_B.Gain1;

  /* Derivatives for Integrator: '<S23>/Integrator' */
  _rtXdot->Integrator_CSTATE = SimpleNeuronTest_B.Sum_n;

  /* Derivatives for Integrator: '<S22>/Integrator' */
  _rtXdot->Integrator_CSTATE_i = SimpleNeuronTest_B.Sum_g;

  /* Derivatives for Integrator: '<S14>/Integrator' */
  _rtXdot->Integrator_CSTATE_d = SimpleNeuronTest_B.Sum_a;

  /* Derivatives for Integrator: '<S34>/Integrator' */
  _rtXdot->Integrator_CSTATE_a = SimpleNeuronTest_B.Sum_d;

  /* Derivatives for Integrator: '<S15>/Integrator' */
  _rtXdot->Integrator_CSTATE_b = SimpleNeuronTest_B.Sum_l;

  /* Derivatives for Integrator: '<S35>/Integrator' */
  _rtXdot->Integrator_CSTATE_g = SimpleNeuronTest_B.Sum_kc;

  /* Derivatives for Integrator: '<S11>/Integrator' */
  _rtXdot->Integrator_CSTATE_c = SimpleNeuronTest_B.Sum;

  /* Derivatives for Integrator: '<S18>/Integrator' */
  _rtXdot->Integrator_CSTATE_al = SimpleNeuronTest_B.Sum_h;

  /* Derivatives for Integrator: '<S19>/Integrator' */
  _rtXdot->Integrator_CSTATE_ds = SimpleNeuronTest_B.Sum_lf;

  /* Derivatives for Integrator: '<S36>/Integrator' */
  _rtXdot->Integrator_CSTATE_df = SimpleNeuronTest_B.Sum_ds;

  /* Derivatives for Integrator: '<S26>/Integrator' */
  _rtXdot->Integrator_CSTATE_in = SimpleNeuronTest_B.Sum_k;

  /* Derivatives for Integrator: '<S27>/Integrator' */
  _rtXdot->Integrator_CSTATE_e = SimpleNeuronTest_B.Sum_p;

  /* Derivatives for Integrator: '<S30>/Integrator' */
  _rtXdot->Integrator_CSTATE_ic = SimpleNeuronTest_B.Sum_ps;

  /* Derivatives for Integrator: '<S31>/Integrator' */
  _rtXdot->Integrator_CSTATE_ay = SimpleNeuronTest_B.Sum_m;
}

/* Model initialize function */
void SimpleNeuronTest_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)SimpleNeuronTest_M, 0,
                sizeof(RT_MODEL_SimpleNeuronTest_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&SimpleNeuronTest_M->solverInfo,
                          &SimpleNeuronTest_M->Timing.simTimeStep);
    rtsiSetTPtr(&SimpleNeuronTest_M->solverInfo, &rtmGetTPtr(SimpleNeuronTest_M));
    rtsiSetStepSizePtr(&SimpleNeuronTest_M->solverInfo,
                       &SimpleNeuronTest_M->Timing.stepSize0);
    rtsiSetdXPtr(&SimpleNeuronTest_M->solverInfo,
                 &SimpleNeuronTest_M->ModelData.derivs);
    rtsiSetContStatesPtr(&SimpleNeuronTest_M->solverInfo, (real_T **)
                         &SimpleNeuronTest_M->ModelData.contStates);
    rtsiSetNumContStatesPtr(&SimpleNeuronTest_M->solverInfo,
      &SimpleNeuronTest_M->Sizes.numContStates);
    rtsiSetErrorStatusPtr(&SimpleNeuronTest_M->solverInfo, (&rtmGetErrorStatus
      (SimpleNeuronTest_M)));
    rtsiSetRTModelPtr(&SimpleNeuronTest_M->solverInfo, SimpleNeuronTest_M);
  }

  rtsiSetSimTimeStep(&SimpleNeuronTest_M->solverInfo, MAJOR_TIME_STEP);
  SimpleNeuronTest_M->ModelData.intgData.f[0] =
    SimpleNeuronTest_M->ModelData.odeF[0];
  SimpleNeuronTest_M->ModelData.contStates = ((X_SimpleNeuronTest_T *)
    &SimpleNeuronTest_X);
  rtsiSetSolverData(&SimpleNeuronTest_M->solverInfo, (void *)
                    &SimpleNeuronTest_M->ModelData.intgData);
  rtsiSetSolverName(&SimpleNeuronTest_M->solverInfo,"ode1");
  rtmSetTPtr(SimpleNeuronTest_M, &SimpleNeuronTest_M->Timing.tArray[0]);
  rtmSetTFinal(SimpleNeuronTest_M, 10.0);
  SimpleNeuronTest_M->Timing.stepSize0 = 0.001;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    SimpleNeuronTest_M->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(SimpleNeuronTest_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(SimpleNeuronTest_M->rtwLogInfo, (NULL));
    rtliSetLogT(SimpleNeuronTest_M->rtwLogInfo, "tout");
    rtliSetLogX(SimpleNeuronTest_M->rtwLogInfo, "");
    rtliSetLogXFinal(SimpleNeuronTest_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(SimpleNeuronTest_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(SimpleNeuronTest_M->rtwLogInfo, 0);
    rtliSetLogMaxRows(SimpleNeuronTest_M->rtwLogInfo, 1000);
    rtliSetLogDecimation(SimpleNeuronTest_M->rtwLogInfo, 1);
    rtliSetLogY(SimpleNeuronTest_M->rtwLogInfo, "");
    rtliSetLogYSignalInfo(SimpleNeuronTest_M->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(SimpleNeuronTest_M->rtwLogInfo, (NULL));
  }

  /* block I/O */
  (void) memset(((void *) &SimpleNeuronTest_B), 0,
                sizeof(B_SimpleNeuronTest_T));

  /* states (continuous) */
  {
    (void) memset((void *)&SimpleNeuronTest_X, 0,
                  sizeof(X_SimpleNeuronTest_T));
  }

  /* states (dwork) */
  (void) memset((void *)&SimpleNeuronTest_DW, 0,
                sizeof(DW_SimpleNeuronTest_T));

  /* Matfile logging */
  rt_StartDataLoggingWithStartTime(SimpleNeuronTest_M->rtwLogInfo, 0.0,
    rtmGetTFinal(SimpleNeuronTest_M), SimpleNeuronTest_M->Timing.stepSize0,
    (&rtmGetErrorStatus(SimpleNeuronTest_M)));

  /* Start for TransportDelay: '<S2>/Transport Delay' */
  {
    real_T *pBuffer = &SimpleNeuronTest_DW.TransportDelay_RWORK.TUbufferArea[0];
    SimpleNeuronTest_DW.TransportDelay_IWORK.Tail = 0;
    SimpleNeuronTest_DW.TransportDelay_IWORK.Head = 0;
    SimpleNeuronTest_DW.TransportDelay_IWORK.Last = 0;
    SimpleNeuronTest_DW.TransportDelay_IWORK.CircularBufSize = 1024;
    pBuffer[0] = SimpleNeuronTest_P.TransportDelay_InitOutput;
    pBuffer[1024] = SimpleNeuronTest_M->Timing.t[0];
    SimpleNeuronTest_DW.TransportDelay_PWORK.TUbufferPtrs[0] = (void *)
      &pBuffer[0];
    SimpleNeuronTest_DW.TransportDelay_PWORK.TUbufferPtrs[1] = (void *)
      &pBuffer[1024];
  }

  /* Start for DiscretePulseGenerator: '<S2>/Discrete Pulse Generator' */
  SimpleNeuronTest_DW.clockTickCounter = 0;

  /* InitializeConditions for TransferFcn: '<S3>/Transfer Fcn' */
  SimpleNeuronTest_X.TransferFcn_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<S23>/Integrator' */
  SimpleNeuronTest_X.Integrator_CSTATE = SimpleNeuronTest_P.Integrator_IC;

  /* InitializeConditions for Integrator: '<S22>/Integrator' */
  SimpleNeuronTest_X.Integrator_CSTATE_i = SimpleNeuronTest_P.Integrator_IC_h;

  /* InitializeConditions for Integrator: '<S14>/Integrator' */
  SimpleNeuronTest_X.Integrator_CSTATE_d = SimpleNeuronTest_P.Integrator_IC_e;

  /* InitializeConditions for Integrator: '<S34>/Integrator' */
  SimpleNeuronTest_X.Integrator_CSTATE_a = SimpleNeuronTest_P.Integrator_IC_l;

  /* InitializeConditions for Integrator: '<S15>/Integrator' */
  SimpleNeuronTest_X.Integrator_CSTATE_b = SimpleNeuronTest_P.Integrator_IC_n;

  /* InitializeConditions for Integrator: '<S35>/Integrator' */
  SimpleNeuronTest_X.Integrator_CSTATE_g = SimpleNeuronTest_P.Integrator_IC_g;

  /* InitializeConditions for Integrator: '<S11>/Integrator' */
  SimpleNeuronTest_X.Integrator_CSTATE_c = SimpleNeuronTest_P.Integrator_IC_c;

  /* InitializeConditions for Integrator: '<S18>/Integrator' */
  SimpleNeuronTest_X.Integrator_CSTATE_al = SimpleNeuronTest_P.Integrator_IC_i;

  /* InitializeConditions for Integrator: '<S19>/Integrator' */
  SimpleNeuronTest_X.Integrator_CSTATE_ds = SimpleNeuronTest_P.Integrator_IC_o;

  /* InitializeConditions for Integrator: '<S36>/Integrator' */
  SimpleNeuronTest_X.Integrator_CSTATE_df = SimpleNeuronTest_P.Integrator_IC_ls;

  /* InitializeConditions for Integrator: '<S26>/Integrator' */
  SimpleNeuronTest_X.Integrator_CSTATE_in = SimpleNeuronTest_P.Integrator_IC_oc;

  /* InitializeConditions for Integrator: '<S27>/Integrator' */
  SimpleNeuronTest_X.Integrator_CSTATE_e = SimpleNeuronTest_P.Integrator_IC_ln;

  /* InitializeConditions for Integrator: '<S30>/Integrator' */
  SimpleNeuronTest_X.Integrator_CSTATE_ic = SimpleNeuronTest_P.Integrator_IC_a;

  /* InitializeConditions for Integrator: '<S31>/Integrator' */
  SimpleNeuronTest_X.Integrator_CSTATE_ay = SimpleNeuronTest_P.Integrator_IC_f;
}

/* Model terminate function */
void SimpleNeuronTest_terminate(void)
{
  /* (no terminate code required) */
}

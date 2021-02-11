/*
 * SimpleNeuronTest_data.c
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

/* Block parameters (auto storage) */
P_SimpleNeuronTest_T SimpleNeuronTest_P = {
  100.0,                               /* Mask Parameter: TwooutputPulseGenerator_A
                                        * Referenced by: '<S2>/Discrete Pulse Generator'
                                        */
  0.1,                                 /* Mask Parameter: NeuroMembrane_ACm
                                        * Referenced by: '<S4>/ACm'
                                        */
  0.1,                                 /* Mask Parameter: NeuroMembrane1_ACm
                                        * Referenced by: '<S5>/ACm'
                                        */
  0.1,                                 /* Mask Parameter: NeuroMembrane2_ACm
                                        * Referenced by: '<S6>/ACm'
                                        */
  0.1,                                 /* Mask Parameter: NeuroMembrane3_ACm
                                        * Referenced by: '<S7>/ACm'
                                        */
  0.1,                                 /* Mask Parameter: NeuroMembrane4_ACm
                                        * Referenced by: '<S8>/ACm'
                                        */
  0.1,                                 /* Mask Parameter: NeuroMembrane5_ACm
                                        * Referenced by: '<S9>/ACm'
                                        */
  1.0,                                 /* Mask Parameter: NeuroMembrane_ARm
                                        * Referenced by: '<S4>/ARm'
                                        */
  1.0,                                 /* Mask Parameter: NeuroMembrane1_ARm
                                        * Referenced by: '<S5>/ARm'
                                        */
  1.0,                                 /* Mask Parameter: NeuroMembrane2_ARm
                                        * Referenced by: '<S6>/ARm'
                                        */
  1.0,                                 /* Mask Parameter: NeuroMembrane3_ARm
                                        * Referenced by: '<S7>/ARm'
                                        */
  1.0,                                 /* Mask Parameter: NeuroMembrane4_ARm
                                        * Referenced by: '<S8>/ARm'
                                        */
  1.0,                                 /* Mask Parameter: NeuroMembrane5_ARm
                                        * Referenced by: '<S9>/ARm'
                                        */
  0.1,                                 /* Mask Parameter: Synapse1_DecompositionTC
                                        * Referenced by: '<S10>/Constant4'
                                        */
  0.1,                                 /* Mask Parameter: NeuroMembrane_ECm
                                        * Referenced by: '<S4>/ECm'
                                        */
  0.1,                                 /* Mask Parameter: NeuroMembrane1_ECm
                                        * Referenced by: '<S5>/ECm'
                                        */
  0.1,                                 /* Mask Parameter: NeuroMembrane2_ECm
                                        * Referenced by: '<S6>/ECm'
                                        */
  0.1,                                 /* Mask Parameter: NeuroMembrane3_ECm
                                        * Referenced by: '<S7>/ECm'
                                        */
  0.1,                                 /* Mask Parameter: NeuroMembrane4_ECm
                                        * Referenced by: '<S8>/ECm'
                                        */
  0.1,                                 /* Mask Parameter: NeuroMembrane5_ECm
                                        * Referenced by: '<S9>/ECm'
                                        */
  1.0,                                 /* Mask Parameter: NeuroMembrane_ERm
                                        * Referenced by: '<S4>/ERm'
                                        */
  1.0,                                 /* Mask Parameter: NeuroMembrane1_ERm
                                        * Referenced by: '<S5>/ERm'
                                        */
  1.0,                                 /* Mask Parameter: NeuroMembrane2_ERm
                                        * Referenced by: '<S6>/ERm'
                                        */
  1.0,                                 /* Mask Parameter: NeuroMembrane3_ERm
                                        * Referenced by: '<S7>/ERm'
                                        */
  1.0,                                 /* Mask Parameter: NeuroMembrane4_ERm
                                        * Referenced by: '<S8>/ERm'
                                        */
  1.0,                                 /* Mask Parameter: NeuroMembrane5_ERm
                                        * Referenced by: '<S9>/ERm'
                                        */
  0.5,                                 /* Mask Parameter: TwooutputPulseGenerator_OOff1
                                        * Referenced by: '<S2>/Switch'
                                        */
  0.04,                                /* Mask Parameter: TwooutputPulseGenerator_OOn1
                                        * Referenced by: '<S2>/Transport Delay'
                                        */
  400.0,                               /* Mask Parameter: TwooutputPulseGenerator_P1
                                        * Referenced by: '<S2>/Discrete Pulse Generator'
                                        */
  1.0,                                 /* Mask Parameter: TwooutputPulseGenerator_PW
                                        * Referenced by: '<S2>/Discrete Pulse Generator'
                                        */
  1.0,                                 /* Mask Parameter: IonChannel11_RR
                                        * Referenced by: '<S3>/C3'
                                        */
  1.0,                                 /* Mask Parameter: IonChannel11_Rc
                                        * Referenced by: '<S3>/C2'
                                        */
  0.001,                               /* Mask Parameter: Synapse1_SecretionTC
                                        * Referenced by: '<S10>/Constant5'
                                        */
  10.0,                                /* Mask Parameter: IonChannel11_T
                                        * Referenced by: '<S3>/Relay'
                                        */
  1.0,                                 /* Mask Parameter: Synapse1_gamma
                                        * Referenced by: '<S10>/Gain'
                                        */
  1.0,                                 /* Mask Parameter: Synapse1_ksi
                                        * Referenced by: '<S10>/Gain'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S3>/C5'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S2>/Constant'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S2>/Transport Delay'
                                        */
  -200.0,                              /* Computed Parameter: TransferFcn_A
                                        * Referenced by: '<S3>/Transfer Fcn'
                                        */
  200.0,                               /* Computed Parameter: TransferFcn_C
                                        * Referenced by: '<S3>/Transfer Fcn'
                                        */
  100.0,                               /* Expression: 100
                                        * Referenced by: '<S1>/C1'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S3>/Relay'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S3>/Relay'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S3>/Relay'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S3>/S3'
                                        */
  100.0,                               /* Expression: 100
                                        * Referenced by: '<S1>/C2'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S23>/Integrator'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S22>/Integrator'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S1>/Gain1'
                                        */
  -1.0,                                /* Expression: -1
                                        * Referenced by: '<S1>/Gain2'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S14>/Integrator'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S34>/Integrator'
                                        */
  0.5,                                 /* Expression: 0.5
                                        * Referenced by: '<S1>/Gain3'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S15>/Integrator'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S35>/Integrator'
                                        */
  0.5,                                 /* Expression: 0.5
                                        * Referenced by: '<S1>/Gain4'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S3>/S1'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S11>/Integrator'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S3>/S2'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S18>/Integrator'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S19>/Integrator'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S36>/Integrator'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S10>/Constant1'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S10>/Switch1'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S26>/Integrator'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S27>/Integrator'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S30>/Integrator'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S31>/Integrator'
                                        */
  0.01,                                /* Expression: 0.01
                                        * Referenced by: '<S10>/Gain1'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S10>/Switch2'
                                        */
  0.0                                  /* Expression: 0
                                        * Referenced by: '<S2>/Discrete Pulse Generator'
                                        */
};

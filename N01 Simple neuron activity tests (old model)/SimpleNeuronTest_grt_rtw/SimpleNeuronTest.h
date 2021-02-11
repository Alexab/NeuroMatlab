/*
 * SimpleNeuronTest.h
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
#ifndef RTW_HEADER_SimpleNeuronTest_h_
#define RTW_HEADER_SimpleNeuronTest_h_
#include <float.h>
#include <math.h>
#include <string.h>
#include <stddef.h>
#ifndef SimpleNeuronTest_COMMON_INCLUDES_
# define SimpleNeuronTest_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "rt_logging.h"
#endif                                 /* SimpleNeuronTest_COMMON_INCLUDES_ */

#include "SimpleNeuronTest_types.h"

/* Shared type includes */
#include "multiword_types.h"
#include "rt_nonfinite.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetBlkStateChangeFlag
# define rtmGetBlkStateChangeFlag(rtm) ((rtm)->ModelData.blkStateChange)
#endif

#ifndef rtmSetBlkStateChangeFlag
# define rtmSetBlkStateChangeFlag(rtm, val) ((rtm)->ModelData.blkStateChange = (val))
#endif

#ifndef rtmGetContStateDisabled
# define rtmGetContStateDisabled(rtm)  ((rtm)->ModelData.contStateDisabled)
#endif

#ifndef rtmSetContStateDisabled
# define rtmSetContStateDisabled(rtm, val) ((rtm)->ModelData.contStateDisabled = (val))
#endif

#ifndef rtmGetContStates
# define rtmGetContStates(rtm)         ((rtm)->ModelData.contStates)
#endif

#ifndef rtmSetContStates
# define rtmSetContStates(rtm, val)    ((rtm)->ModelData.contStates = (val))
#endif

#ifndef rtmGetDerivCacheNeedsReset
# define rtmGetDerivCacheNeedsReset(rtm) ((rtm)->ModelData.derivCacheNeedsReset)
#endif

#ifndef rtmSetDerivCacheNeedsReset
# define rtmSetDerivCacheNeedsReset(rtm, val) ((rtm)->ModelData.derivCacheNeedsReset = (val))
#endif

#ifndef rtmGetFinalTime
# define rtmGetFinalTime(rtm)          ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetIntgData
# define rtmGetIntgData(rtm)           ((rtm)->ModelData.intgData)
#endif

#ifndef rtmSetIntgData
# define rtmSetIntgData(rtm, val)      ((rtm)->ModelData.intgData = (val))
#endif

#ifndef rtmGetOdeF
# define rtmGetOdeF(rtm)               ((rtm)->ModelData.odeF)
#endif

#ifndef rtmSetOdeF
# define rtmSetOdeF(rtm, val)          ((rtm)->ModelData.odeF = (val))
#endif

#ifndef rtmGetRTWLogInfo
# define rtmGetRTWLogInfo(rtm)         ((rtm)->rtwLogInfo)
#endif

#ifndef rtmGetZCCacheNeedsReset
# define rtmGetZCCacheNeedsReset(rtm)  ((rtm)->ModelData.zCCacheNeedsReset)
#endif

#ifndef rtmSetZCCacheNeedsReset
# define rtmSetZCCacheNeedsReset(rtm, val) ((rtm)->ModelData.zCCacheNeedsReset = (val))
#endif

#ifndef rtmGetdX
# define rtmGetdX(rtm)                 ((rtm)->ModelData.derivs)
#endif

#ifndef rtmSetdX
# define rtmSetdX(rtm, val)            ((rtm)->ModelData.derivs = (val))
#endif

#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
# define rtmGetStopRequested(rtm)      ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
# define rtmSetStopRequested(rtm, val) ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
# define rtmGetStopRequestedPtr(rtm)   (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
# define rtmGetT(rtm)                  (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTFinal
# define rtmGetTFinal(rtm)             ((rtm)->Timing.tFinal)
#endif

/* Block signals (auto storage) */
typedef struct {
  real_T Switch;                       /* '<S2>/Switch' */
  real_T TransferFcn;                  /* '<S3>/Transfer Fcn' */
  real_T Relay;                        /* '<S3>/Relay' */
  real_T S3;                           /* '<S3>/S3' */
  real_T Gain1;                        /* '<S1>/Gain1' */
  real_T Fcn1;                         /* '<S11>/Fcn1' */
  real_T S2;                           /* '<S3>/S2' */
  real_T Sum;                          /* '<S11>/Sum' */
  real_T Sum5;                         /* '<S12>/Sum5' */
  real_T Product;                      /* '<S12>/Product' */
  real_T Sum_a;                        /* '<S14>/Sum' */
  real_T Sum5_l;                       /* '<S13>/Sum5' */
  real_T Product_f;                    /* '<S13>/Product' */
  real_T Sum_l;                        /* '<S15>/Sum' */
  real_T Sum2;                         /* '<S5>/Sum2' */
  real_T F4;                           /* '<S16>/F4' */
  real_T F2;                           /* '<S16>/F2' */
  real_T Sum_h;                        /* '<S18>/Sum' */
  real_T Sum1;                         /* '<S5>/Sum1' */
  real_T Sum5_o;                       /* '<S17>/Sum5' */
  real_T Product_e;                    /* '<S17>/Product' */
  real_T Sum_lf;                       /* '<S19>/Sum' */
  real_T Sum5_j;                       /* '<S20>/Sum5' */
  real_T Product_h;                    /* '<S20>/Product' */
  real_T Sum_g;                        /* '<S22>/Sum' */
  real_T Sum5_c;                       /* '<S21>/Sum5' */
  real_T Product_p;                    /* '<S21>/Product' */
  real_T Sum_n;                        /* '<S23>/Sum' */
  real_T Sum5_lq;                      /* '<S24>/Sum5' */
  real_T Product_n;                    /* '<S24>/Product' */
  real_T Sum_k;                        /* '<S26>/Sum' */
  real_T Sum5_g;                       /* '<S25>/Sum5' */
  real_T Product_a;                    /* '<S25>/Product' */
  real_T Sum_p;                        /* '<S27>/Sum' */
  real_T Sum2_e;                       /* '<S8>/Sum2' */
  real_T Sum5_jq;                      /* '<S28>/Sum5' */
  real_T Product_d;                    /* '<S28>/Product' */
  real_T Sum_ps;                       /* '<S30>/Sum' */
  real_T Sum1_n;                       /* '<S8>/Sum1' */
  real_T Sum5_i;                       /* '<S29>/Sum5' */
  real_T Product_k;                    /* '<S29>/Product' */
  real_T Sum_m;                        /* '<S31>/Sum' */
  real_T Sum2_k;                       /* '<S9>/Sum2' */
  real_T Sum5_p;                       /* '<S32>/Sum5' */
  real_T Product_m;                    /* '<S32>/Product' */
  real_T Sum_d;                        /* '<S34>/Sum' */
  real_T Sum1_j;                       /* '<S9>/Sum1' */
  real_T Sum5_d;                       /* '<S33>/Sum5' */
  real_T Product_j;                    /* '<S33>/Product' */
  real_T Sum_kc;                       /* '<S35>/Sum' */
  real_T Sum_ds;                       /* '<S36>/Sum' */
  real_T DiscretePulseGenerator;       /* '<S2>/Discrete Pulse Generator' */
} B_SimpleNeuronTest_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  struct {
    real_T modelTStart;
    real_T TUbufferArea[2048];
  } TransportDelay_RWORK;              /* '<S2>/Transport Delay' */

  struct {
    void *TUbufferPtrs[2];
  } TransportDelay_PWORK;              /* '<S2>/Transport Delay' */

  struct {
    void *LoggedData;
  } Scope2_PWORK;                      /* '<Root>/Scope2' */

  int32_T clockTickCounter;            /* '<S2>/Discrete Pulse Generator' */
  struct {
    int_T Tail;
    int_T Head;
    int_T Last;
    int_T CircularBufSize;
  } TransportDelay_IWORK;              /* '<S2>/Transport Delay' */

  boolean_T Relay_Mode;                /* '<S3>/Relay' */
} DW_SimpleNeuronTest_T;

/* Continuous states (auto storage) */
typedef struct {
  real_T TransferFcn_CSTATE;           /* '<S3>/Transfer Fcn' */
  real_T Integrator_CSTATE;            /* '<S23>/Integrator' */
  real_T Integrator_CSTATE_i;          /* '<S22>/Integrator' */
  real_T Integrator_CSTATE_d;          /* '<S14>/Integrator' */
  real_T Integrator_CSTATE_a;          /* '<S34>/Integrator' */
  real_T Integrator_CSTATE_b;          /* '<S15>/Integrator' */
  real_T Integrator_CSTATE_g;          /* '<S35>/Integrator' */
  real_T Integrator_CSTATE_c;          /* '<S11>/Integrator' */
  real_T Integrator_CSTATE_al;         /* '<S18>/Integrator' */
  real_T Integrator_CSTATE_ds;         /* '<S19>/Integrator' */
  real_T Integrator_CSTATE_df;         /* '<S36>/Integrator' */
  real_T Integrator_CSTATE_in;         /* '<S26>/Integrator' */
  real_T Integrator_CSTATE_e;          /* '<S27>/Integrator' */
  real_T Integrator_CSTATE_ic;         /* '<S30>/Integrator' */
  real_T Integrator_CSTATE_ay;         /* '<S31>/Integrator' */
} X_SimpleNeuronTest_T;

/* State derivatives (auto storage) */
typedef struct {
  real_T TransferFcn_CSTATE;           /* '<S3>/Transfer Fcn' */
  real_T Integrator_CSTATE;            /* '<S23>/Integrator' */
  real_T Integrator_CSTATE_i;          /* '<S22>/Integrator' */
  real_T Integrator_CSTATE_d;          /* '<S14>/Integrator' */
  real_T Integrator_CSTATE_a;          /* '<S34>/Integrator' */
  real_T Integrator_CSTATE_b;          /* '<S15>/Integrator' */
  real_T Integrator_CSTATE_g;          /* '<S35>/Integrator' */
  real_T Integrator_CSTATE_c;          /* '<S11>/Integrator' */
  real_T Integrator_CSTATE_al;         /* '<S18>/Integrator' */
  real_T Integrator_CSTATE_ds;         /* '<S19>/Integrator' */
  real_T Integrator_CSTATE_df;         /* '<S36>/Integrator' */
  real_T Integrator_CSTATE_in;         /* '<S26>/Integrator' */
  real_T Integrator_CSTATE_e;          /* '<S27>/Integrator' */
  real_T Integrator_CSTATE_ic;         /* '<S30>/Integrator' */
  real_T Integrator_CSTATE_ay;         /* '<S31>/Integrator' */
} XDot_SimpleNeuronTest_T;

/* State disabled  */
typedef struct {
  boolean_T TransferFcn_CSTATE;        /* '<S3>/Transfer Fcn' */
  boolean_T Integrator_CSTATE;         /* '<S23>/Integrator' */
  boolean_T Integrator_CSTATE_i;       /* '<S22>/Integrator' */
  boolean_T Integrator_CSTATE_d;       /* '<S14>/Integrator' */
  boolean_T Integrator_CSTATE_a;       /* '<S34>/Integrator' */
  boolean_T Integrator_CSTATE_b;       /* '<S15>/Integrator' */
  boolean_T Integrator_CSTATE_g;       /* '<S35>/Integrator' */
  boolean_T Integrator_CSTATE_c;       /* '<S11>/Integrator' */
  boolean_T Integrator_CSTATE_al;      /* '<S18>/Integrator' */
  boolean_T Integrator_CSTATE_ds;      /* '<S19>/Integrator' */
  boolean_T Integrator_CSTATE_df;      /* '<S36>/Integrator' */
  boolean_T Integrator_CSTATE_in;      /* '<S26>/Integrator' */
  boolean_T Integrator_CSTATE_e;       /* '<S27>/Integrator' */
  boolean_T Integrator_CSTATE_ic;      /* '<S30>/Integrator' */
  boolean_T Integrator_CSTATE_ay;      /* '<S31>/Integrator' */
} XDis_SimpleNeuronTest_T;

#ifndef ODE1_INTG
#define ODE1_INTG

/* ODE1 Integration Data */
typedef struct {
  real_T *f[1];                        /* derivatives */
} ODE1_IntgData;

#endif

/* Parameters (auto storage) */
struct P_SimpleNeuronTest_T_ {
  real_T TwooutputPulseGenerator_A;    /* Mask Parameter: TwooutputPulseGenerator_A
                                        * Referenced by: '<S2>/Discrete Pulse Generator'
                                        */
  real_T NeuroMembrane_ACm;            /* Mask Parameter: NeuroMembrane_ACm
                                        * Referenced by: '<S4>/ACm'
                                        */
  real_T NeuroMembrane1_ACm;           /* Mask Parameter: NeuroMembrane1_ACm
                                        * Referenced by: '<S5>/ACm'
                                        */
  real_T NeuroMembrane2_ACm;           /* Mask Parameter: NeuroMembrane2_ACm
                                        * Referenced by: '<S6>/ACm'
                                        */
  real_T NeuroMembrane3_ACm;           /* Mask Parameter: NeuroMembrane3_ACm
                                        * Referenced by: '<S7>/ACm'
                                        */
  real_T NeuroMembrane4_ACm;           /* Mask Parameter: NeuroMembrane4_ACm
                                        * Referenced by: '<S8>/ACm'
                                        */
  real_T NeuroMembrane5_ACm;           /* Mask Parameter: NeuroMembrane5_ACm
                                        * Referenced by: '<S9>/ACm'
                                        */
  real_T NeuroMembrane_ARm;            /* Mask Parameter: NeuroMembrane_ARm
                                        * Referenced by: '<S4>/ARm'
                                        */
  real_T NeuroMembrane1_ARm;           /* Mask Parameter: NeuroMembrane1_ARm
                                        * Referenced by: '<S5>/ARm'
                                        */
  real_T NeuroMembrane2_ARm;           /* Mask Parameter: NeuroMembrane2_ARm
                                        * Referenced by: '<S6>/ARm'
                                        */
  real_T NeuroMembrane3_ARm;           /* Mask Parameter: NeuroMembrane3_ARm
                                        * Referenced by: '<S7>/ARm'
                                        */
  real_T NeuroMembrane4_ARm;           /* Mask Parameter: NeuroMembrane4_ARm
                                        * Referenced by: '<S8>/ARm'
                                        */
  real_T NeuroMembrane5_ARm;           /* Mask Parameter: NeuroMembrane5_ARm
                                        * Referenced by: '<S9>/ARm'
                                        */
  real_T Synapse1_DecompositionTC;     /* Mask Parameter: Synapse1_DecompositionTC
                                        * Referenced by: '<S10>/Constant4'
                                        */
  real_T NeuroMembrane_ECm;            /* Mask Parameter: NeuroMembrane_ECm
                                        * Referenced by: '<S4>/ECm'
                                        */
  real_T NeuroMembrane1_ECm;           /* Mask Parameter: NeuroMembrane1_ECm
                                        * Referenced by: '<S5>/ECm'
                                        */
  real_T NeuroMembrane2_ECm;           /* Mask Parameter: NeuroMembrane2_ECm
                                        * Referenced by: '<S6>/ECm'
                                        */
  real_T NeuroMembrane3_ECm;           /* Mask Parameter: NeuroMembrane3_ECm
                                        * Referenced by: '<S7>/ECm'
                                        */
  real_T NeuroMembrane4_ECm;           /* Mask Parameter: NeuroMembrane4_ECm
                                        * Referenced by: '<S8>/ECm'
                                        */
  real_T NeuroMembrane5_ECm;           /* Mask Parameter: NeuroMembrane5_ECm
                                        * Referenced by: '<S9>/ECm'
                                        */
  real_T NeuroMembrane_ERm;            /* Mask Parameter: NeuroMembrane_ERm
                                        * Referenced by: '<S4>/ERm'
                                        */
  real_T NeuroMembrane1_ERm;           /* Mask Parameter: NeuroMembrane1_ERm
                                        * Referenced by: '<S5>/ERm'
                                        */
  real_T NeuroMembrane2_ERm;           /* Mask Parameter: NeuroMembrane2_ERm
                                        * Referenced by: '<S6>/ERm'
                                        */
  real_T NeuroMembrane3_ERm;           /* Mask Parameter: NeuroMembrane3_ERm
                                        * Referenced by: '<S7>/ERm'
                                        */
  real_T NeuroMembrane4_ERm;           /* Mask Parameter: NeuroMembrane4_ERm
                                        * Referenced by: '<S8>/ERm'
                                        */
  real_T NeuroMembrane5_ERm;           /* Mask Parameter: NeuroMembrane5_ERm
                                        * Referenced by: '<S9>/ERm'
                                        */
  real_T TwooutputPulseGenerator_OOff1;/* Mask Parameter: TwooutputPulseGenerator_OOff1
                                        * Referenced by: '<S2>/Switch'
                                        */
  real_T TwooutputPulseGenerator_OOn1; /* Mask Parameter: TwooutputPulseGenerator_OOn1
                                        * Referenced by: '<S2>/Transport Delay'
                                        */
  real_T TwooutputPulseGenerator_P1;   /* Mask Parameter: TwooutputPulseGenerator_P1
                                        * Referenced by: '<S2>/Discrete Pulse Generator'
                                        */
  real_T TwooutputPulseGenerator_PW;   /* Mask Parameter: TwooutputPulseGenerator_PW
                                        * Referenced by: '<S2>/Discrete Pulse Generator'
                                        */
  real_T IonChannel11_RR;              /* Mask Parameter: IonChannel11_RR
                                        * Referenced by: '<S3>/C3'
                                        */
  real_T IonChannel11_Rc;              /* Mask Parameter: IonChannel11_Rc
                                        * Referenced by: '<S3>/C2'
                                        */
  real_T Synapse1_SecretionTC;         /* Mask Parameter: Synapse1_SecretionTC
                                        * Referenced by: '<S10>/Constant5'
                                        */
  real_T IonChannel11_T;               /* Mask Parameter: IonChannel11_T
                                        * Referenced by: '<S3>/Relay'
                                        */
  real_T Synapse1_gamma;               /* Mask Parameter: Synapse1_gamma
                                        * Referenced by: '<S10>/Gain'
                                        */
  real_T Synapse1_ksi;                 /* Mask Parameter: Synapse1_ksi
                                        * Referenced by: '<S10>/Gain'
                                        */
  real_T C5_Value;                     /* Expression: 0
                                        * Referenced by: '<S3>/C5'
                                        */
  real_T Constant_Value;               /* Expression: 0
                                        * Referenced by: '<S2>/Constant'
                                        */
  real_T TransportDelay_InitOutput;    /* Expression: 0
                                        * Referenced by: '<S2>/Transport Delay'
                                        */
  real_T TransferFcn_A;                /* Computed Parameter: TransferFcn_A
                                        * Referenced by: '<S3>/Transfer Fcn'
                                        */
  real_T TransferFcn_C;                /* Computed Parameter: TransferFcn_C
                                        * Referenced by: '<S3>/Transfer Fcn'
                                        */
  real_T C1_Value;                     /* Expression: 100
                                        * Referenced by: '<S1>/C1'
                                        */
  real_T Relay_OffVal;                 /* Expression: 0
                                        * Referenced by: '<S3>/Relay'
                                        */
  real_T Relay_YOn;                    /* Expression: 1
                                        * Referenced by: '<S3>/Relay'
                                        */
  real_T Relay_YOff;                   /* Expression: 0
                                        * Referenced by: '<S3>/Relay'
                                        */
  real_T S3_Threshold;                 /* Expression: 1
                                        * Referenced by: '<S3>/S3'
                                        */
  real_T C2_Value;                     /* Expression: 100
                                        * Referenced by: '<S1>/C2'
                                        */
  real_T Integrator_IC;                /* Expression: 0
                                        * Referenced by: '<S23>/Integrator'
                                        */
  real_T Integrator_IC_h;              /* Expression: 0
                                        * Referenced by: '<S22>/Integrator'
                                        */
  real_T Gain1_Gain;                   /* Expression: 1
                                        * Referenced by: '<S1>/Gain1'
                                        */
  real_T Gain2_Gain;                   /* Expression: -1
                                        * Referenced by: '<S1>/Gain2'
                                        */
  real_T Integrator_IC_e;              /* Expression: 0
                                        * Referenced by: '<S14>/Integrator'
                                        */
  real_T Integrator_IC_l;              /* Expression: 0
                                        * Referenced by: '<S34>/Integrator'
                                        */
  real_T Gain3_Gain;                   /* Expression: 0.5
                                        * Referenced by: '<S1>/Gain3'
                                        */
  real_T Integrator_IC_n;              /* Expression: 0
                                        * Referenced by: '<S15>/Integrator'
                                        */
  real_T Integrator_IC_g;              /* Expression: 0
                                        * Referenced by: '<S35>/Integrator'
                                        */
  real_T Gain4_Gain;                   /* Expression: 0.5
                                        * Referenced by: '<S1>/Gain4'
                                        */
  real_T S1_Threshold;                 /* Expression: 1
                                        * Referenced by: '<S3>/S1'
                                        */
  real_T Integrator_IC_c;              /* Expression: 0
                                        * Referenced by: '<S11>/Integrator'
                                        */
  real_T S2_Threshold;                 /* Expression: 1
                                        * Referenced by: '<S3>/S2'
                                        */
  real_T Integrator_IC_i;              /* Expression: 0
                                        * Referenced by: '<S18>/Integrator'
                                        */
  real_T Integrator_IC_o;              /* Expression: 0
                                        * Referenced by: '<S19>/Integrator'
                                        */
  real_T Integrator_IC_ls;             /* Expression: 0
                                        * Referenced by: '<S36>/Integrator'
                                        */
  real_T Constant1_Value;              /* Expression: 0
                                        * Referenced by: '<S10>/Constant1'
                                        */
  real_T Switch1_Threshold;            /* Expression: 0
                                        * Referenced by: '<S10>/Switch1'
                                        */
  real_T Integrator_IC_oc;             /* Expression: 0
                                        * Referenced by: '<S26>/Integrator'
                                        */
  real_T Integrator_IC_ln;             /* Expression: 0
                                        * Referenced by: '<S27>/Integrator'
                                        */
  real_T Integrator_IC_a;              /* Expression: 0
                                        * Referenced by: '<S30>/Integrator'
                                        */
  real_T Integrator_IC_f;              /* Expression: 0
                                        * Referenced by: '<S31>/Integrator'
                                        */
  real_T Gain1_Gain_o;                 /* Expression: 0.01
                                        * Referenced by: '<S10>/Gain1'
                                        */
  real_T Switch2_Threshold;            /* Expression: 1
                                        * Referenced by: '<S10>/Switch2'
                                        */
  real_T DiscretePulseGenerator_PhaseDel;/* Expression: 0
                                          * Referenced by: '<S2>/Discrete Pulse Generator'
                                          */
};

/* Real-time Model Data Structure */
struct tag_RTM_SimpleNeuronTest_T {
  const char_T *errorStatus;
  RTWLogInfo *rtwLogInfo;
  RTWSolverInfo solverInfo;

  /*
   * ModelData:
   * The following substructure contains information regarding
   * the data used in the model.
   */
  struct {
    X_SimpleNeuronTest_T *contStates;
    real_T *derivs;
    boolean_T *contStateDisabled;
    boolean_T zCCacheNeedsReset;
    boolean_T derivCacheNeedsReset;
    boolean_T blkStateChange;
    real_T odeF[1][15];
    ODE1_IntgData intgData;
  } ModelData;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    int_T numContStates;
    int_T numSampTimes;
  } Sizes;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    uint32_T clockTickH0;
    time_T stepSize0;
    uint32_T clockTick1;
    uint32_T clockTickH1;
    time_T tFinal;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[2];
  } Timing;
};

/* Block parameters (auto storage) */
extern P_SimpleNeuronTest_T SimpleNeuronTest_P;

/* Block signals (auto storage) */
extern B_SimpleNeuronTest_T SimpleNeuronTest_B;

/* Continuous states (auto storage) */
extern X_SimpleNeuronTest_T SimpleNeuronTest_X;

/* Block states (auto storage) */
extern DW_SimpleNeuronTest_T SimpleNeuronTest_DW;

/* Model entry point functions */
extern void SimpleNeuronTest_initialize(void);
extern void SimpleNeuronTest_step(void);
extern void SimpleNeuronTest_terminate(void);

/* Real-time Model object */
extern RT_MODEL_SimpleNeuronTest_T *const SimpleNeuronTest_M;

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
 * '<Root>' : 'SimpleNeuronTest'
 * '<S1>'   : 'SimpleNeuronTest/Small  NewNeuron6'
 * '<S2>'   : 'SimpleNeuronTest/Two-output Pulse Generator'
 * '<S3>'   : 'SimpleNeuronTest/Small  NewNeuron6/Ion Channel11'
 * '<S4>'   : 'SimpleNeuronTest/Small  NewNeuron6/Neuro Membrane'
 * '<S5>'   : 'SimpleNeuronTest/Small  NewNeuron6/Neuro Membrane1'
 * '<S6>'   : 'SimpleNeuronTest/Small  NewNeuron6/Neuro Membrane2'
 * '<S7>'   : 'SimpleNeuronTest/Small  NewNeuron6/Neuro Membrane3'
 * '<S8>'   : 'SimpleNeuronTest/Small  NewNeuron6/Neuro Membrane4'
 * '<S9>'   : 'SimpleNeuronTest/Small  NewNeuron6/Neuro Membrane5'
 * '<S10>'  : 'SimpleNeuronTest/Small  NewNeuron6/Synapse1'
 * '<S11>'  : 'SimpleNeuronTest/Small  NewNeuron6/Ion Channel11/Inertial Link (H1)'
 * '<S12>'  : 'SimpleNeuronTest/Small  NewNeuron6/Neuro Membrane/Neuro Channel'
 * '<S13>'  : 'SimpleNeuronTest/Small  NewNeuron6/Neuro Membrane/Neuro Channel1'
 * '<S14>'  : 'SimpleNeuronTest/Small  NewNeuron6/Neuro Membrane/Neuro Channel/Inertial Link (H1)'
 * '<S15>'  : 'SimpleNeuronTest/Small  NewNeuron6/Neuro Membrane/Neuro Channel1/Inertial Link (H1)'
 * '<S16>'  : 'SimpleNeuronTest/Small  NewNeuron6/Neuro Membrane1/Neuro Channel'
 * '<S17>'  : 'SimpleNeuronTest/Small  NewNeuron6/Neuro Membrane1/Neuro Channel1'
 * '<S18>'  : 'SimpleNeuronTest/Small  NewNeuron6/Neuro Membrane1/Neuro Channel/Inertial Link (H1)'
 * '<S19>'  : 'SimpleNeuronTest/Small  NewNeuron6/Neuro Membrane1/Neuro Channel1/Inertial Link (H1)'
 * '<S20>'  : 'SimpleNeuronTest/Small  NewNeuron6/Neuro Membrane2/Neuro Channel'
 * '<S21>'  : 'SimpleNeuronTest/Small  NewNeuron6/Neuro Membrane2/Neuro Channel1'
 * '<S22>'  : 'SimpleNeuronTest/Small  NewNeuron6/Neuro Membrane2/Neuro Channel/Inertial Link (H1)'
 * '<S23>'  : 'SimpleNeuronTest/Small  NewNeuron6/Neuro Membrane2/Neuro Channel1/Inertial Link (H1)'
 * '<S24>'  : 'SimpleNeuronTest/Small  NewNeuron6/Neuro Membrane3/Neuro Channel'
 * '<S25>'  : 'SimpleNeuronTest/Small  NewNeuron6/Neuro Membrane3/Neuro Channel1'
 * '<S26>'  : 'SimpleNeuronTest/Small  NewNeuron6/Neuro Membrane3/Neuro Channel/Inertial Link (H1)'
 * '<S27>'  : 'SimpleNeuronTest/Small  NewNeuron6/Neuro Membrane3/Neuro Channel1/Inertial Link (H1)'
 * '<S28>'  : 'SimpleNeuronTest/Small  NewNeuron6/Neuro Membrane4/Neuro Channel'
 * '<S29>'  : 'SimpleNeuronTest/Small  NewNeuron6/Neuro Membrane4/Neuro Channel1'
 * '<S30>'  : 'SimpleNeuronTest/Small  NewNeuron6/Neuro Membrane4/Neuro Channel/Inertial Link (H1)'
 * '<S31>'  : 'SimpleNeuronTest/Small  NewNeuron6/Neuro Membrane4/Neuro Channel1/Inertial Link (H1)'
 * '<S32>'  : 'SimpleNeuronTest/Small  NewNeuron6/Neuro Membrane5/Neuro Channel'
 * '<S33>'  : 'SimpleNeuronTest/Small  NewNeuron6/Neuro Membrane5/Neuro Channel1'
 * '<S34>'  : 'SimpleNeuronTest/Small  NewNeuron6/Neuro Membrane5/Neuro Channel/Inertial Link (H1)'
 * '<S35>'  : 'SimpleNeuronTest/Small  NewNeuron6/Neuro Membrane5/Neuro Channel1/Inertial Link (H1)'
 * '<S36>'  : 'SimpleNeuronTest/Small  NewNeuron6/Synapse1/Inertial Link (H1)1'
 */
#endif                                 /* RTW_HEADER_SimpleNeuronTest_h_ */

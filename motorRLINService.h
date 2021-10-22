/** ###################################################################
**     Filename  : motorRLINService.h
**     Project   : Motor Application
**     Purpose   : Position and Sensor Micro Motor and BDC Motor Application  
**     Date/Time : 2020/5/12
** ###################################################################*/

#ifndef __MOTORSVC__RLIN_H_
#define __MOTORSVC__RLIN_H_

#define MOTOR_SLAVE_IFC_HANDLE             (0)

#define RLIN_SIGNAL_TRIGGER_COUNT          (2u)

#define RLIN_STATUS_ON                     (1u)
#define RLIN_STATUS_OFF                    (0u)

#define RLIN_BEMF_FEEDBACK_ENABLE          (0u)

#define RLIN_FIXANGLE_INVALID              (0xFF)
#define RLIN_STEPFREQ_INVALID              (1001u)
#define RLIN_STEPMODE_INVALID              (0x0F)
#define RLIN_CURRENT_INVALID               (0x0F)
#define RLIN_SPEED_INVALID                 (0xFF)

typedef enum
{
    LIN_SYSIGN_OFF = 0u,
    LIN_SYSIGN_ACC = 1u,
    LIN_SYSIGN_RUN = 2u,
    LIN_SYSIGN_CRANK = 3u,    
}enSysIGNSts;

typedef struct
{
    UINT8 uSwingMode;
    UINT8 uAngle;
    UINT8 uSavedMode;
    UINT8 uSwingCnt;
    UINT8 uFocusCnt;
    UINT8 uAvoidCnt;
    UINT8 uSweepCnt;
    UINT8 uOnOffCnt;
}stMicroLinMotorConfig;

typedef struct
{
    UINT16 uStepFreq;
    UINT8  uStepMode;
    UINT8  uRunCurr;
    UINT8  uHoldCurr;
    UINT8  uStallThr;
}stMicroLinDrvConfig;



/* Micro Step and BDC Motor RLIN common API */
void motorRLINSvcInit( void );
void motorRLINSvcHandler( void );
void motorRLINTimeOutCallback( void );

/* Micro Step Motor RLIN API */
void microRLINSvcInit( void );
void microRLINRcvCtrlMsg0x37( void );
void microRLINRcvCtrlMsg0x31( void );
void microRLINRcvCtrlMsg0x32( void );
void microRLINRcvCtrlMsg0x33( void );

void microRLINRcvDebugMsg0x10( void );
void microRLINUpdateCtrlStatus( void );

#endif /* #ifndef __MOTORSVC__RLIN_H_ */


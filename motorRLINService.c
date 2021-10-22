/** ###################################################################
**     Filename  : motorRLINService.c
**     Project   : Motor Application
**     Purpose   : Position and Sensor Micro Motor and BDC Motor Application 
**     Date/Time : 2020/5/12
** ###################################################################*/

/* MODULE motorRLINService.c */

#include "pfProject.h"

static UINT8 uMotorNotAvail1 = 0x00;


//#pragma section 
//#pragma section text APP_CODE

/* Global Function Definition */                   
void motorRLINSvcInit( void )
{
    /* Call initialization function */
    if( 0u != l_sys_init() )
    {
        /* Process Lin Slave Component Initialization Error here!! */
    }
        
    /* Start LIN component */
    if( 0u != l_ifc_init(MOTOR_SLAVE_IFC_HANDLE) )
    {
       /* Process LIN Interface Initialization Error here!! */
    }
        
    /* Initialize Transport Layer */
    //ld_init();
        
    microRLINSvcInit();
    
    return;
}

void motorRLINSvcHandler( void )
{
    //orignal
#if 0
    if ( 1u == l_flg_tst_LI0_ICC_ICCLIN1_FrP00_ICC_LIN1_flag() )
    {
        l_flg_clr_LI0_ICC_ICCLIN1_FrP00_ICC_LIN1_flag();

        microRLINRcvCtrlMsg0x37();
    }
    else if ( 1u == l_flg_tst_LI0_ICC_ICCLIN1_FrP01_ICC_LIN1_flag() )
    {
        l_flg_clr_LI0_ICC_ICCLIN1_FrP01_ICC_LIN1_flag();
            
        microRLINRcvCtrlMsg0x31();
    }
    else if ( 1u == l_flg_tst_LI0_ICC_ICCLIN1_FrP02_ICC_LIN1_flag() )
    {
        l_flg_clr_LI0_ICC_ICCLIN1_FrP02_ICC_LIN1_flag();
        microRLINRcvCtrlMsg0x32();
        microRLINUpdateCtrlStatus();
    }
    else if ( 1u == l_flg_tst_LI0_ICC_ICCLIN1_FrP03_ICC_LIN1_flag() )
    {
        l_flg_clr_LI0_ICC_ICCLIN1_FrP03_ICC_LIN1_flag();
        microRLINRcvCtrlMsg0x33();
    }
    else
    {
    
    }
    
    motorRLINTimeOutCallback();
    
    return;
#endif
    UINT8 uIdx;
    static UINT16 TimeCnt[8] = {0u,0u,0u,0u,0u,0u,0u,0u};
    static UINT8 Notclose[8] = {0u,0u,0u,0u,0u,0u,0u,0u};
    static UINT16 StopCnt[8] = {0u,0u,0u,0u,0u,0u,0u,0u};

    /*uMotorNotAvail1 = 0;

    for ( uIdx = MICRO_IDX_START; uIdx < MICRO_IDX_NUMBER; uIdx ++ )
    {
        if ( MICRO_POS_MODE_SELF_LEARNING == microMotorCtrlGetWorkMode(uIdx) )
        {
            uMotorNotAvail1 |= ( 1 << uIdx );
        }
    }

    if (uMotorNotAvail1)
    {
        return;
    }*/
    if(Notclose[3] == 0)
    {
        if(StopCnt[3] == 0)
        {
            if(TimeCnt[3] == 10000)
            {
                microMotorCtrlSetRunAndDir1(3, FALSE, MICRO_SWING_DECREMENT);
                TimeCnt[3] = 0u;
                Notclose[3] = 1u;
                StopCnt[3]++;
            }
            else
            {
                TimeCnt[3]++;
            }
        }
        else
        {
            if(StopCnt[3] == 5000)
            {
                microMotorCtrlSetRunAndDir1(3, TRUE, MICRO_SWING_DECREMENT);
                StopCnt[3] = 0u;
            }
            else
            {
                StopCnt[3]++;
            }
        }
          
    }
    else
    {
        if(StopCnt[3] == 0)
        {
            if(TimeCnt[3] == 10000)
            {
                microMotorCtrlSetRunAndDir1(3, FALSE, MICRO_SWING_INCREMENT);
                TimeCnt[3] = 0u;
                Notclose[3] = 0u;
                StopCnt[3]++;
            }
            else
            {
                TimeCnt[3]++;
            }
        }
        else
        {
            if(StopCnt[3] == 5000)
            {
                microMotorCtrlSetRunAndDir1(3, TRUE, MICRO_SWING_INCREMENT);
                StopCnt[3] = 0u;
            }
            else
            {
                StopCnt[3]++;
            }
        }
    }

}

void motorRLINTimeOutCallback( void )
{
    //lin_lld_driver_timeout();
}

/* END motorRLINService.c */


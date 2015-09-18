#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "driverlib/interrupt.h" 
#include "utils/uartstdio.h"
#include "ac_common.h"
#include "ac_hal.h"
#include "Iot_Timer.h"
#include "Iot_Uart.h"
//*****************************************************************************
//
// Counter to count the number of interrupts that have been called.
//
//*****************************************************************************
static volatile u32 g_u32Timer0BReportCounter = 0;
u32 g_u32PeriodicReportTimer = DEFAULTREPORTTEME;
u32 flag = 0;
//*****************************************************************************
//	Timer 1B中断处理函数
//*****************************************************************************


//*****************************************************************************
//
// The interrupt handler for the Timer0B interrupt.
//
//*****************************************************************************
void Timer0AIntHandler(void)
{

    u32 cloudconnectstatus = 0;
    //
    // Clear the timer interrupt flag.
    //
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    cloudconnectstatus =AC_GetStoreStatus(CLOUDSTATUS);
    if((g_u32Timer0BReportCounter++>=g_u32PeriodicReportTimer)&&(CLOUDCONNECT==cloudconnectstatus))
    {
          IntMasterDisable();

          //AC_SendLedStatus2Server(KEY_LED_CONTROL_FROMSWITCH);
          //Report data
          g_u32Timer0BReportCounter = 0;
          IntMasterEnable();
    }
}

//*****************************************************************************
//
// Configure the UART and pb0,pb1.  This is used for communicating with 7681.
//
//*****************************************************************************

//*****************************************************************************
//
// Print "Hello World!" to the UART on the evaluation board.
//
//*****************************************************************************
void PeriodicTimerInit()
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    //
    // Configure Timer0B as a 16-bit periodic timer.
    //
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
    
    //
    // Set the Timer0B load value to 1s.
    //
    TimerLoadSet(TIMER0_BASE, TIMER_A, SysCtlClockGet()/4);
    
    //
    // Enable processor interrupts.
    //
    IntMasterEnable();
    //
    // Configure the Timer0B interrupt for timer timeout.
    //
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    
    //
    // Enable the Timer0B interrupt on the processor (NVIC).
    //
    IntEnable(INT_TIMER0A);
    
    //
    // Enable Timer0B.
    //
    TimerEnable(TIMER0_BASE, TIMER_A);
    
}

/*********************************************************************************************************
** Function name:           SetReportPeriodic
** Descriptions:            设置数据上报周期 
** input parameters:        TimerInterval:   时间间隔 s
**                          
** Output parameters::      无
** Returned value:          TRUE :      成功
**                          FALSE:      失败
** Created by:              
** Created Date:            
**--------------------------------------------------------------------------------------------------------
** Modified by:            
** Modified date:          
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void SetReportPeriodic(u32 TimerInterval)
{
    g_u32Timer0BReportCounter = 0;
    g_u32PeriodicReportTimer =TimerInterval;
}


/*********************************************************************************************************
** Function name:           SetReportPeriodic
** Descriptions:            设置数据上报周期 
** input parameters:        TimerInterval:   时间间隔 s
**                          
** Output parameters::      无
** Returned value:          TRUE :      成功
**                          FALSE:      失败
** Created by:              
** Created Date:            
**--------------------------------------------------------------------------------------------------------
** Modified by:            
** Modified date:          
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void TimerInit()
{
  PeriodicTimerInit();
 
}

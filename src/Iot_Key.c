/**
******************************************************************************
* @file     Iot_Key.c
* @authors  cxy
* @version  V1.0.0
* @date     10-Sep-2014
* @brief   
******************************************************************************
*/

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_nvic.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "utils/uartstdio.h"
#include "inc/hw_gpio.h"
#include "ac_common.h"
#include "ac_hal.h"
#include "ac_cfg.h"
vu32  g_vu32Key = 0;



/*********************************************************************************************************
** Function name:           KeyIntHandle
** Descriptions:            
** input parameters:        
**                          
** Output parameters::      无
** Returned value:          
**                          
** Created by:              
** Created Date:            
**--------------------------------------------------------------------------------------------------------
** Modified by:            
** Modified date:          
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void KeyIntHandle(void)
{
    unsigned long ulStatus;
    ulStatus = GPIOIntStatus(GPIO_PORTF_BASE, true); 
    GPIOIntClear(GPIO_PORTF_BASE, ulStatus); 
    if (ulStatus & GPIO_PIN_0) //
    {
        SysCtlDelay(SysCtlClockGet() / 1000 / 3);//10ms      
        AC_SendRestMsg(NULL);
        while (GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0) == 0x00); 
        SysCtlDelay(SysCtlClockGet() / 3); // 延时约10ms，消除松键抖动
    }
    else if (ulStatus & GPIO_PIN_4) //
    {
        SysCtlDelay(SysCtlClockGet() / 1000 / 3);//10ms      
        g_vu32Key = g_vu32Key^0x1;
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, g_vu32Key << 2);
        while (GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4) == 0x00); 
        SysCtlDelay(SysCtlClockGet() / 3); // 延时约10ms，消除松键抖动
        AC_SendLedStatus2Server();
    }   
}



/*********************************************************************************************************
** Function name:           KeyInit
** Descriptions:           
** input parameters:        
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
void KeyInit(void)
{
    
    //
    // Reset the error indicator.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);                   /*  使能GPIO PF口  */
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;                                    //UNLOCK CR REGISTER
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= 0x01;
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = 0;   //
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE,GPIO_PIN_4|GPIO_PIN_0);
    GPIOIntTypeSet(GPIO_PORTF_BASE, GPIO_PIN_4|GPIO_PIN_0, GPIO_FALLING_EDGE);

    ROM_GPIODirModeSet(GPIO_PORTF_BASE, GPIO_PIN_4|GPIO_PIN_0, GPIO_DIR_MODE_IN);
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4|GPIO_PIN_0,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0);
    GPIOIntEnable(GPIO_PORTF_BASE, GPIO_PIN_4|GPIO_PIN_0);
    IntEnable(INT_GPIOF); // 使能GPIOF端口中断
}

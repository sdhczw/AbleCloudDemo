//*****************************************************************************
//
// hello.c - Simple hello world example.
//
// Copyright (c) 2012-2014 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
// 
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
// 
// This is part of revision 2.1.0.12573 of the EK-TM4C123GXL Firmware Package.
//
//*****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "driverlib/i2c.h"
#include "driverlib/timer.h"
#include "driverlib/interrupt.h" 
#include "ac_common.h"
#include "ac_hal.h"
#include "Iot_Uart.h"
#include "Iot_Key.h"
#include "Iot_Timer.h"
//

void ClockInit()
{
    // Enable lazy stacking for interrupt handlers.  This allows floating-point
  // instructions to be used within interrupt handlers, but at the expense of
  // extra stack usage.
  //
  ROM_FPULazyStackingEnable();
  
  //
  // Set the clocking to run directly from the crystal.
  //
  ROM_SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ |
                     SYSCTL_OSC_MAIN);
  
  //
  // Enable the GPIO port that is used for the on-board LED.
  //
  ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
  
  //
  // Enable the GPIO pins for the LED (PF2 & PF3).
  //
  ROM_GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_2);
}
void Sleep(unsigned long milisecond)
{
    SysCtlDelay(SysCtlClockGet() / 1000 / 3*milisecond);//100ms
}
//*****************************************************************************
//
// Print "Hello World!" to the UART on the evaluation board.
//
//*****************************************************************************
int main(void)
{
    ClockInit();
    UartInit();
    TimerInit();
    KeyInit();


    while(WIFIPOWEROFF==AC_GetStoreStatus(WIFIPOWERSTATUS))
    {
        AC_Init();
        Sleep(500);//100ms
        ProcessWifiMsg();
    }
    
    while(1)
    {
        ProcessWifiMsg();
    }    
}



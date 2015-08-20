//*****************************************************************************
//
// Beta_Arm.h - Simple hello world example.
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
#ifndef IOT_UART_H
#define IOT_UART_H

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

#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "driverlib/interrupt.h"
#include "bmd.h"
#include "ac_api.h"
#include <ac_common.h>
#include <ac_protocol_interface.h>
//*****************************************************************************
//
// macro
//
//*****************************************************************************
#define RCTRL_MSG_FLAG		       0x02030405
#define RCTRL_MSG_PREFIX		"\2\3\4\5"
#define PRINT_FLAG                      "\1\2\3\4"


//how many packets can be buffered in rxring ,(each packet size need < UARTRX_RING_LEN - 1)
#define    NUM_DESCS           30

//buffer length for uart rx buffer whose data is moved from uart UART HW RX FIFO
#define    UART1RX_RING_LEN    1024   
#define    AC_PAYLOADLENOFFSET 9

#define    UART_BAUTRATE       115200

#define    UART0_INTPRIO       6

#define    UART1_INTPRIO       6


// ================================================================
//					Message Definition
// ================================================================

//*****************************************************************************
//
// message define
//
//*****************************************************************************
typedef enum {
    PKT_UNKNOWN,
    PKT_PUREDATA,
    PKT_PRINTCMD,
} PKT_TYPE;

typedef struct tag_RCTRL_STRU_MSGHEAD
{
    u32 MsgFlag;         //消息标示 byte0:0X76, byte1:0x81, byte2:0x43, byte3:0x50 0x76814350
    AC_MessageHead  struMessageHead;
}RCTRL_STRU_MSGHEAD;    //消息头定义


typedef struct {
    PKT_TYPE pkt_type;
    u16   pkt_len;
}PKT_FIFO;//packet infor is in sequence with index[0,num_desc-1] which mapping the sequence in rx


/*
* 2014/05/13,terrence
* struct to descrypt the packet in ring buffer
* we just need to know the packet number and their lengh in sequence
*/
typedef struct {
    PKT_TYPE  cur_type;              //receiving packet:which packet type is receiving current? 
    u8     cur_num;               //receiving packet:current index of receiving packet
    u8     pkt_num;               //completely packets:packet number in ring buffer
    PKT_FIFO  infor[NUM_DESCS];      //completely packets:FIFO,packet infor in ring
} PKT_DESC; 


typedef struct
{
    BUFFER_INFO                    Rx_Buffer;  //receive buffer
    PKT_DESC                       Rx_desc;    //description       
    
    BUFFER_INFO                    Tx_Buffer;  //transmit buffer
    
} UARTStruct;

// ================================================================
//				Golbal	Variable Definition
// ================================================================

//*****************************************************************************
//
//! fuction
//
//*****************************************************************************
extern void UartSend(u8  *Buffer, u16  NByte);
extern void UartInit();
extern void ProcessWifiMsg();
extern void SendDevStatus2Server(u32 Base, u8 Version,u8 MsgId);
#endif


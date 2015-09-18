/**
******************************************************************************
* @file     ac_hal.h
* @authors  cxy
* @version  V1.0.0
* @date     10-Sep-2014
* @brief    
******************************************************************************
*/

#ifndef  __AC_HAL_H__ 
#define  __AC_HAL_H__

#include <ac_common.h>
#include <ac_protocol_interface.h>
#include <ac_api.h>
#include <Iot_Uart.h>

#define AC_CODE_KLV_TEST  (65)
#define AC_CODE_BINARY_LED  (68)
#define AC_CODE_KLV_LED  (69)
#define AC_CODE_JSON_LED  (70)

#define AC_CODE_KLV_REPORT  (203)
#define AC_CODE_JSON_REPORT  (203)
#define AC_CODE_BINARY_REPORT (203) 

#define CLIENT_SERVER_OK  (102)   
#define CLOUDSTATUS 0
#define WIFIPOWERSTATUS 1

#define CLOUDCONNECT 1 
#define CLOUDDISCONNECT 0

#define AC_Printf UARTprintf

#define WIFIPOWERON 1
#define WIFIPOWEROFF 0

#define KEY_LED_ON_OFF (1)
#define KEY_LED_CONTROL_STATUS (2)

#define KEY_LED_CONTROL_FROMAPP (0)
#define KEY_LED_CONTROL_FROMSWITCH (1)

#ifdef __cplusplus
extern "C" {
#endif
void AC_Init(void);
void AC_SendMessage(u8 *pu8Msg, u16 u16DataLen);
void AC_DealNotifyMessage(AC_MessageHead *pstruMsg, AC_OptList *pstruOptList, u8 *pu8Playload);
void AC_DealOtaMessage(AC_MessageHead *pstruMsg, AC_OptList *pstruOptList,  u8 *pu8Playload);
void AC_DealEvent(AC_MessageHead *pstruMsg, AC_OptList *pstruOptList,u8 *pu8Playload);
u32  AC_GetStoreStatus(u32 u32Type);
unsigned short crc16_ccitt(const unsigned char *buf, unsigned int len);	
void AC_StoreStatus(u32 u32Type , u32 u32Data);
void AC_SendDevStatus2Server();
void AC_SendLedBinaryStatus2Server(u8 u8control);
void AC_SendLedKlvStatus2Server(u8 u8control);
void AC_SendDeviceConfig(AC_OptList *pstruOptList, AC_Configuration *pstruConfig);
#ifdef __cplusplus
}
#endif
#endif
/******************************* FILE END ***********************************/




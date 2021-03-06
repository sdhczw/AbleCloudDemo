/**
******************************************************************************
* @file     ac_api.h
* @authors  cxy
* @version  V1.0.0
* @date     10-Sep-2014
* @brief    
******************************************************************************
*/

#ifndef  __AC_API_H__ 
#define  __AC_API_H__

#include <ac_common.h>
#include <ac_protocol_interface.h>

typedef struct 
{
    AC_TransportInfo *pstruTransportInfo;
    AC_SsessionInfo *pstruSsession;
    
}AC_OptList;


#ifdef __cplusplus
extern "C" {
#endif
void AC_BuildOption(AC_OptList *pstruOptList, u8 *pu8OptNum, u8 *pu8Buffer, u16 *pu16Len);
void AC_BuildMessage(u8 u8MsgCode, u8 u8MsgId, 
    u8 *pu8Payload, u16 u16PayloadLen,
    AC_OptList *pstruOptList,
    u8 *pu8Msg, u16 *pu16Len);
void AC_SendDeviceStart(AC_OptList *pstruOptList);
void AC_SendDeviceRegsiter(u8 *pu8EqVersion, u8 *pu8ModuleKey, u64 u64Domain, u8 *pu8DeviceId);
void AC_SendDeviceRegsiterWithMac(u8 *pu8EqVersion, u8 *pu8ModuleKey, u64 u64Domain);
void AC_SendAckMsg(AC_OptList *pstruOptList, u8 u8MsgId);
void AC_SendErrMsg(AC_OptList *pstruOptList, u8 u8MsgId, u8 *pu8ErrorMsg, u16 u16DataLen);
void AC_SendRestMsg(AC_OptList *pstruOptList);
void AC_SendRebootMsg(AC_OptList *pstruOptList);
void AC_RecvMessage(AC_MessageHead *pstruMsg);
void AC_ParseOption(AC_MessageHead *pstruMsg, AC_OptList *pstruOptList, u16 *pu16OptLen);
void AC_SendDeviceConfig(AC_OptList *pstruOptList, AC_Configuration *pstruConfig);
#ifdef __cplusplus
}
#endif
#endif
/******************************* FILE END ***********************************/




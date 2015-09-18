/**
******************************************************************************
* @file     ac_hal.h
* @authors  cxy
* @version  V1.0.0
* @date     10-Sep-2014
* @brief    
******************************************************************************
*/

#ifndef  __AC_KLV_H__ 
#define  __AC_KLV_H__

#include <ac_common.h>
#include <ac_protocol_interface.h>
#include <ac_api.h>
#include <ac_klv.h>

#define INVALID_TYPE 0x00 //无效类型，只有key，没有value，适用于不需要参数的控制，
#define BOOL_TYPE	  0x01    //布尔型（占用8bit数值表示，只使用第一个bit）
#define INT8_TYPE  	0x02  //8位整形
#define INT16_TYPE	0x03  //16位整型（16位，网络字节序）
#define INT32_TYPE	0x04  //整形（32位，网络字节序）
#define INT64_TYPE	0x05  //长整型（64位，网络字节序）
#define FLOAT_TYPE	0x06  //浮点型（32位，网络字节序）
#define DOUBLE_TYPE	0x07  //双精度浮点型（64位，网络字节序）
#define STRING_TYPE		0x08  //字符串
#define BINARY_TYPE	0x09	//二进制

#define WRITE 0  //可写 
#define READ  1  //只读
#define ALARM 2  //告警
#define ERROR 3  //故障

#ifdef __cplusplus
extern "C" {
#endif
typedef struct KlV{
    u32 offset;    
    u8 data[AC_MESSAGE_MAX_LEN];				/* The item's name string, if this item is the child of, or is in the list of subitems of an object. */
} AC_KLV;

void AC_GetKey(u8 *pu8Playload,u8* key, u8 *pNum);
s8 AC_GetKeyValue(u8 *pu8Playload, u16 u16PayloadLen, u8 u8Key,void *pValue,u16 *pu16Length,u8 *pu8Type);
s8 AC_SetKeyValue(AC_KLV *pOut,u8 Key,u16 Length,u8 Type, void *pValue);
AC_KLV * AC_CreateObj();
void AC_SendKLVMessage(AC_MessageHead *pstruMsg, AC_OptList *pstruOptList,AC_KLV* pOut);
void AC_ReportKLVMessage(u8 u8MsgCode, AC_OptList *pstruOptList,AC_KLV* pOut);
void AC_FreeObj(AC_KLV * pOut);
#ifdef __cplusplus
}
#endif
#endif
/******************************* FILE END ***********************************/




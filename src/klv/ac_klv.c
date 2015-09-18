/**
******************************************************************************
* @file     ac_app_main.c
* @authors  cxy
* @version  V1.0.0
* @date     10-Sep-2014
* @brief   
******************************************************************************
*/

#include <ac_common.h>
#include <ac_protocol_interface.h>
#include <ac_api.h>
#include <ac_hal.h>
#include <ac_cfg.h>
#include <ac_klv.h>
#include <stdlib.h>
/*************************************************
* Function: AC_GetKeyValue
* Author: zw pu8Playload:in,Key:in,pValue:out,pLength:out
* Returns: 
* Parameter: 
* History:
*************************************************/
s8 AC_GetKeyValue(u8 *pu8Playload, u16 u16PayloadLen, u8 u8Key,void *pValue,u16 *pu16Length,u8 *pu8Type)
{
    u8 *p = pu8Playload;
    u32 i = 0;
    u8 temp;
    while(i<u16PayloadLen)
    {
        
        *pu8Type = ((p[i+1])&0x1f);
        
        switch(*pu8Type)
        {
            case INVALID_TYPE:
            if(u8Key==p[i])
            {
                *pu16Length = 0;
                return AC_RET_OK; 
            }
            else
            {
                i = i + 2;
            }
            break;
            case INT8_TYPE:
            case BOOL_TYPE:
            if(u8Key==p[i])
            {
                *pu16Length = 1;
                memcpy(pValue,p+i+2,*pu16Length);
                return AC_RET_OK; 
            }
            else
            {
                i = i + 3;
            }
            break;
            case INT16_TYPE:
            if(u8Key==p[i])
            {
                *pu16Length = 2;
                if(!AC_checkCPUendian())
                {
                    temp = p[i+2];
                    p[i+2] = p[i+3];
                    p[i+3] =  temp; 
                }
                memcpy(pValue,p+i+2,*pu16Length);
                return AC_RET_OK; 
            }
            else
            {
                i = i + 4;
            }
            break;
            case INT32_TYPE:
            case FLOAT_TYPE:
            if(u8Key==p[i])
            {
                *pu16Length = 4;
                if(!AC_checkCPUendian())
                {
                    temp = p[i+2];
                    p[i+2+0] = p[i+2+3];
                    p[i+2+3] =  temp;
                    temp = p[i+2+1];
                    p[i+2+1] = p[i+2+2];
                    p[i+2+2] =  temp;
                }
                memcpy(pValue,p+i+2,*pu16Length);
                return AC_RET_OK; 
            }
            else
            {
                i = i + 6;
            }
            break;
            case INT64_TYPE:
            case DOUBLE_TYPE:
            if(u8Key==p[i])
            {
                *pu16Length = 8;
                if(!AC_checkCPUendian())
                {
                    temp = p[i+2+0];
                    p[i+2+0] = p[i+2+7];
                    p[i+2+7] =  temp;
                    temp = p[i+2+1];
                    p[i+2+1] = p[i+2+6];
                    p[i+2+6] =  temp; 
                    temp = p[i+2+2];
                    p[i+2+2] = p[i+2+5];
                    p[i+2+5] =  temp; 
                    temp = p[i+2+3];
                    p[i+2+3] = p[i+2+4];
                    p[i+2+4] =  temp; 
                }
                memcpy(pValue,p+i+2,*pu16Length);
                return AC_RET_OK; 
            }
            else
            {
                i = i + 10;
            }
            break;
            default:
            if(u8Key==p[i])
            {
                if(!AC_checkCPUendian())
                {
                    *pu16Length = (u16)(p[i+2]<<8) + (u16)p[i+3];
                }
                else
                {
                    *pu16Length = (u16)p[i+2] + (u16)(p[i+3]<<8);
                }
                memcpy(pValue,p+i+4,*pu16Length);
                return AC_RET_OK; 
            }
            else
            {
                i = i + 4 +(u16) (p[i+2]<<8) + (u16)(p[i+3]);
            }
            break;           
        }  
    }
    return AC_RET_ERROR;
}
/*************************************************
* Function: AC_SetKeyValue
* Description: 
* Author: zw 
* Returns: 
* Parameter: 
* History:
*************************************************/
s8 AC_SetKeyValue(AC_KLV *pOut,u8 u8Key,u16 u16Length,u8 u8Type,void *pValue)
{
    u8 temp = 0;
    u8 *p = pOut->data + pOut->offset;
    u8 i = 0;
    if(u16Length>AC_MESSAGE_MAX_LEN||u8Type>10)
    {
        return AC_RET_ERROR;
    }
    p[0] = u8Key;
    p[1] = u8Type&0x1f;
    
    switch(u8Type)
    {
        case INVALID_TYPE:
        u16Length = 0;
        break;
        case BOOL_TYPE:
        case INT8_TYPE:
        memcpy(p+2,pValue,1); 
        u16Length = 1;
        break;
        case INT16_TYPE:
        memcpy(p+2,pValue,2);
        if(!AC_checkCPUendian())
        {
            temp = p[i+2+0];
            p[i+2+0] = p[i+2+1];
            p[i+2+1] =  temp; 
        }
        u16Length = 2;
        break;
        case INT32_TYPE:
        case FLOAT_TYPE:
        memcpy(p+2,pValue,4); 
        if(!AC_checkCPUendian())
        {
            
            temp = p[i+2+0];
            p[i+2+0] = p[i+2+3];
            p[i+2+3] =  temp;
            temp = p[i+2+1];
            p[i+2+1] = p[i+2+2];
            p[i+2+2] =  temp;
        }
        u16Length = 4;
        break;
        case INT64_TYPE:
        case DOUBLE_TYPE:
        memcpy(p+2,pValue,8); 
        if(!AC_checkCPUendian())
        {
            temp = p[i+2+0];
            p[i+2+0] = p[i+2+7];
            p[i+2+7] =  temp;
            temp = p[i+2+1];
            p[i+2+1] = p[i+2+6];
            p[i+2+6] =  temp; 
            temp = p[i+2+2];
            p[i+2+2] = p[i+2+5];
            p[i+2+5] =  temp; 
            temp = p[i+2+3];
            p[i+2+3] = p[i+2+4];
            p[i+2+4] =  temp; 
        }
        u16Length = 8;
        break;
        default:
        if(!AC_checkCPUendian())
        {
            *((u16*)(p+2)) = AC_HtoNs(u16Length);
        }
        memcpy(p+4,pValue,u16Length);
        u16Length = u16Length + 2;
        break;
    }
    
    pOut->offset = pOut->offset + 2 + u16Length;
    return AC_RET_OK;
}
/*************************************************
* Function: AC_CreateObj
* Author: zw pu8Playload:in,Key:in,pValue:out,pLength:out
* Returns: 
* Parameter: 
* History:
*************************************************/
AC_KLV *AC_CreateObj()
{
    AC_KLV *p = (AC_KLV *)malloc(AC_MESSAGE_MAX_LEN+1);
    if(p!=NULL)
    {
        memset(p,0,AC_MESSAGE_MAX_LEN+1);
    }
    return p;
}

/*************************************************
* Function: AC_SetKeyValue
* Description: 
* Author: zw 
* Returns: 
* Parameter: 
* History:
*************************************************/
void AC_FreeObj(AC_KLV *pOut)
{
    free(pOut);
}

/*************************************************
* Function: AC_SendKLVMessage
* Description: 
* Author: cxy 
* Returns: 
* Parameter: 
* History:
*************************************************/
void AC_SendKLVMessage(AC_MessageHead *pstruMsg, AC_OptList *pstruOptList,AC_KLV* pOut)
{
    u16 u16DataLen;
    u8 *pu8TempBuffer = malloc(AC_MESSAGE_MAX_LEN);
    AC_BuildMessage(AC_CODE_KLV_RSP,pstruMsg->MsgId,
                    pOut->data, pOut->offset,
                    pstruOptList, 
                    pu8TempBuffer, &u16DataLen);
    AC_SendMessage(pu8TempBuffer, u16DataLen);
    free(pu8TempBuffer);
}

/*************************************************
* Function: AC_SendKLVMessage
* Description: 
* Author: cxy 
* Returns: 
* Parameter: 
* History:
*************************************************/
void AC_ReportKLVMessage(u8 u8MsgCode, AC_OptList *pstruOptList,AC_KLV* pOut)
{
    u16 u16DataLen;
    u8 *pu8TempBuffer = malloc(AC_MESSAGE_MAX_LEN);
    AC_BuildMessage(u8MsgCode,0,
                    pOut->data, pOut->offset,
                    pstruOptList, 
                    pu8TempBuffer, &u16DataLen);
    AC_SendMessage(pu8TempBuffer, u16DataLen);
    free(pu8TempBuffer);
}

/*************************************************
* Function: AC_SetKeyValue
* Description: 
* Author: zw 
* Returns: 
* Parameter: 
* History:
*************************************************/
void AC_KlvTest()
{
    AC_KLV *pOut = AC_CreateObj();
    u8 u8temp = 1;
    u16 u16temp = 0x5a5a;
    u32 u32temp = 0xa5a5a5a5;
    u64 u64temp = 0x1234567890123456;
    u8 u8out= 1;
    u16 u16out = 0;
    u32 u32out = 0;
    u64 u64out = 0;
    u8 stringout[10] = {0};
    u16 u16length = 0;
    u8 u8Type = 0;
    AC_SetKeyValue(pOut,1,0,INVALID_TYPE,NULL);
    AC_SetKeyValue(pOut,2,sizeof(u8temp),INT8_TYPE,&u8temp);
    AC_SetKeyValue(pOut,3,sizeof(u16temp),INT16_TYPE,&u16temp);
    AC_SetKeyValue(pOut,4,sizeof(u32temp),INT32_TYPE,&u32temp);
    AC_SetKeyValue(pOut,5,sizeof(u64temp),INT64_TYPE,&u64temp);
    AC_SetKeyValue(pOut,6,sizeof("Hello") -1,STRING_TYPE,"Hello");
    AC_GetKeyValue(pOut->data,pOut->offset,1,NULL,&u16length,&u8Type);
    AC_GetKeyValue(pOut->data,pOut->offset,2,&u8out,&u16length,&u8Type);
    AC_GetKeyValue(pOut->data,pOut->offset,3,&u16out,&u16length,&u8Type);
    AC_GetKeyValue(pOut->data,pOut->offset,4,&u32out,&u16length,&u8Type);
    AC_GetKeyValue(pOut->data,pOut->offset,5,&u64out,&u16length,&u8Type);
    AC_GetKeyValue(pOut->data,pOut->offset,6,stringout,&u16length,&u8Type);                    
    AC_FreeObj(pOut);
}


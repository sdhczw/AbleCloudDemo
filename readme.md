#AbleCloud


##修改记录：
###v1.0.5 2015.09.18
1.合并二进制、klv、json工程，默认支持klv，支持json、二进制需要配置工程对应宏开关

###v1.0.5 2015.09.01
1.更新AC_SendDeviceRegsiter和AC_SendDeviceRegsiterWithMac去除AC_OptList传入参数

###v1.0.4 2015.07.14
1.在ac_api.c增加 AC_SendRebootMsg，用于ota_confirm消息确认之后重启wifi。


###v1.0.3 2015.07.08
1.在<ac_protocol_interface.h> 增加扩展消息 AC_CODE_EXT = 63 AC_CODE_EXT_REGSITER = 0,并增加 
typedef struct 
{
    AC_ExtMessageHead struExtMessageHead;
    AC_RegisterReq struRegReq;
}AC_ExtRegisterReq;
2.在ac_hal,c 中增加通过mac地址注册函数，这个函数的作用是通过WIFIMAC地址作为设备ID注册信息
###v1.0.2  2015.06.19

1.增加扩展设备注册消息，用于支持设备统一入库
2.删除无效代码

###v1.0.1 2015.03.28
1.设备ID扩展到16个字节
2.AC_ConfigWifi接口增加端口配置，u32TestAddrConfig = 0：dns配置生效，u32TestAddrConfig = 1：ip地址生效 

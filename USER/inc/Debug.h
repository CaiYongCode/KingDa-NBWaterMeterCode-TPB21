#ifndef __DEBUG_H__
#define __DEBUG_H__
/*********************************************************************************
文件包含区
*********************************************************************************/
#include "include.h"
/*********************************************************************************
宏定义区
*********************************************************************************/
/*********************************************************************************
数据类型定义
*********************************************************************************/
struct Debug_EN
{
  u8 Status;
  u8 SendData;
};
/*********************************************************************************
常量定义区
*********************************************************************************/
/*********************************************************************************
公共变量定义区
*********************************************************************************/
/*********************************************************************************
外部变量声明区
*********************************************************************************/
/*********************************************************************************
私有变量定义区
*********************************************************************************/ 
extern struct Debug_EN Debug;
/*********************************************************************************
测试变量定义区
*********************************************************************************/
/*********************************************************************************
内部函数定义区
*********************************************************************************/
/*********************************************************************************
功能代码定义区
*********************************************************************************/
void Debug_Process(void);
void Debug_ACK_Busy(unsigned char cmd);
void Debug_ACK_OK(unsigned char cmd);
void Send_Debug_Data(void);
#endif
/******************************************END********************************************************/
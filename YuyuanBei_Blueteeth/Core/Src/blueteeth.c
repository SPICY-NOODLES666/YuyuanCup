#include "..\Inc\blueteeth.h"
#include "main.h"
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

#define BUFFER_SIZE 100
// AT命令字符串定义区域
char Chead[] = "AT+";
char role[] = "AT+ROLE=";
char Cconnect[] = "CONN";
char Csend[] = "SEND";
char sendav[] = "AT+SENDEN=1\\r\\n";
char senddv[] = "AT+SENDEN=0\\r\\n";
char Cset[] = "=";
char C[200];
char *Clist[3] = {Cconnect, Csend};

UART_HandleTypeDef *huart = NULL;
char *receivedData = NULL;

// 作用：设置蓝牙连接的USART串口，定义蓝牙主机从机
// 输入：USART串口结构体，char型变量："1":主机;"0":从机
// 输出：无
void BL_set(UART_HandleTypeDef *usart, char Flag)
{
    memset(C, 0, strlen(C));
    strcat(C, role);
    strcat(C, Flag);
    huart = usart;
    HAL_UART_Transmit(huart, sendav, sizeof(sendav) - 1, 1000);
    HAL_UART_Transmit(huart, C, sizeof(C) - 1, 1000);
    HAL_UART_Transmit(huart, senddv, sizeof(senddv) - 1, 1000);
    return;
}

// 作用：接收主控制器发来的命令
// 输入：命令字符：1：连接，2：发送；字符串data：在data的第一位应该含有双引号，末位应有换行符和双引号，否则将导致命令不成功。
// 输出：存在全局变量C中的字符串
void BL_command(int flag, char *data)
{
    memset(C, 0, strlen(C));
    strcat(Chead, Clist[flag - 1]);
    strcat(C, Cset);
    strcat(C, data);
    Command(flag);
    return;
}

// 作用：接收数据
// 输入：无
// 输出：获得的字符串
char *BL_Receive()
{
    memset(receivedData, 0, BUFFER_SIZE);
    uint8_t ch;
    if (HAL_UART_GET_FLAG(huart, UART_FLAG_RXNE) != RESET)
    {
        ch = (uint8_t)(huart->Instance->DR); // 读取数据寄存器
        static uint8_t index = 0;
        if (ch != '\n' && index < BUFFER_SIZE - 1)
        {                               // 如果不是换行且缓冲区未满
            receivedData[index++] = ch; // 存储接收到的字符
        }
        else
        {
            receivedData[index] = '\0'; // 在字符串末尾添加结束符
            index = 0;                  // 重置索引
            // 这里可以添加代码处理接收到的字符串，例如返回给上位机
            HAL_UART_Transmit(huart, (uint8_t *)receivedData, strlen(receivedData), 1000);
        }
    }
    return receivedData;
}

// 作用：处理传入的命令
// 输入：命令类型，*全局变量命令
// 输出：无
void Command(int flag)
{
    if (flag == 1)
    {
        Connect();
    }
    else
    {
        Sendmessage();
    }
}

// 作用：连接设备
// 输入：无
// 输出：无
void Connect()
{
    HAL_UART_Transmit(huart, sendav, sizeof(sendav) - 1, 1000);
    HAL_UART_Transmit(huart, C, sizeof(C) - 1, 1000);
    HAL_UART_Transmit(huart, senddv, sizeof(sendav) - 1, 1000);
}

// 作用：通过USART命令蓝牙发送消息
// 输入：无
// 输出：无
void Sendmessage()
{
    HAL_UART_Transmit(huart, sendav, sizeof(sendav) - 1, 1000);
    HAL_UART_Transmit(huart, C, sizeof(C) - 1, 1000);
    HAL_UART_Transmit(huart, senddv, sizeof(sendav) - 1, 1000);
    return;
}
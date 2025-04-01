#ifndef blueteeth_H
#define blueteeth_H
#include "main.h"
#include "stm32f103xb.h"
#include "stm32f1xx_hal_uart.h"
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

void BL_Receive(char *receivedData);
void BL_set(UART_HandleTypeDef *usart, char Flag);
void BL_command(int flag, char *data);
void Command(int flag);
void Connect();
void Sendmessage();
void MX_USART1_UART_Init(USART_TypeDef *usart);
#endif

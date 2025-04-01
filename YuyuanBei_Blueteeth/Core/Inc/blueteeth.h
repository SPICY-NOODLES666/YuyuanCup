#ifndef blueteeth_H
#define blueteeth_H

static void MX_USART1_UART_Init(USART_TypeDef *usart);
char *BL_Receive();
void BL_set(UART_HandleTypeDef *usart, char Flag);
void BL_command(int flag, char *data);
void Command(int flag);
void Connect();
void Sendmessage();
#endif

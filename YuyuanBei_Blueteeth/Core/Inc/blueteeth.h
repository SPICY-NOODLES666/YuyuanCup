#ifndef blueteeth_H
#define blueteeth_H

char *BL_Receive();
void BL_set(UART_HandleTypeDef *usart, char Flag);
void BL_command(int flag, char *data);
void Command(int flag);
void Connect();
void Sendmessage();
#endif

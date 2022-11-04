#ifndef __UART_H_
#define __UART_H_

#define uchar unsigned char

#include <avr/io.h>

void UART_init(uint32_t usart_baudrate);
uchar UART_RX();
uchar UART_RX_NONBLOCK(uchar *c);
void UART_TX(uchar c);
uchar UART_TX_NONBLOCK(uchar c);
void UART_SendString(const char *str);

#endif
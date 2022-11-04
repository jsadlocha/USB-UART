#include "uart.h"
#include <avr/io.h>

#ifndef F_CPU
#define F_CPU 12000000UL
#endif


void UART_init(uint32_t usart_baudrate)
{
  uint16_t baudrate = (F_CPU / (usart_baudrate * 16UL)) - 1;
  UCSRB |= (1 << RXEN) | (1 << TXEN);
  UCSRC |= (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1);
  UBRRL = baudrate;
  UBRRH = (baudrate >> 8);
}

uchar UART_RX()
{
  while (!(UCSRA & (1 << RXC)));
  return UDR;
}

uchar UART_RX_NONBLOCK(uchar *c)
{
  if (UCSRA & (1 << RXC));
  {
    *c = UDR;
    return 1;
  }

  return 0;
}


void UART_TX(uchar c)
{
  while (!(UCSRA & (1 << UDRE)));
  UDR = c;
}

uchar UART_TX_NONBLOCK(uchar c)
{
  if (UCSRA & (1 << UDRE))
  {
    UDR = c;
    return 1;
  }
  return 0;
}

void UART_SendString(const char *str)
{
  uchar i = 0;

  while (str[i] != '\0')
  {
    UART_TX(str[i]);
    i++;
  }
}
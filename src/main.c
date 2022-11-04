#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include "usbdrv/usbdrv.h"
#include "fifo.h"
#include "uart.h"

#define BULK_OUT 0x4

#define SET_BAUD_RATE 32
#define DEVICE_CONTROL 34

#define SENDBUFSIZE 64

static uchar buffer[16]; // control out
static uchar sendBuffer[64]; // bulk in 
static uchar currentPosition, bytesRemaining;
static uchar uart_start = 0;


void UART_setup()
{
  uint32_t baud_rate = buffer[0] | buffer[1] << 8 | buffer[2] << 16 | buffer[3] << 24;
  UART_init(baud_rate);
  uart_start = 1;
}


void UART_RECEIVE()
{
  uchar c;
  while(!isFull(&deviceHostFifo) && UART_RX_NONBLOCK(&c))
  {
    if (!put_byte(&deviceHostFifo, c))
      break;
    // what if cannot put byte to fifo
  }
}

void UART_TRANSCEIVE()
{
  uchar c;
  do {
    if (!get_byte(&hostDeviceFifo, &c))
      break;

      UART_TX(c); // blocking io
  } while(isEmpty(&hostDeviceFifo));
  // what if cannot send byte wait or?
}

USB_PUBLIC uchar usbFunctionSetup(uchar data[8])
{
  usbRequest_t *rq = (void *)data;

  switch (rq->bRequest)
  {
    case SET_BAUD_RATE:
      if (rq->wLength.word == 7)
      {
        currentPosition = 0;
        bytesRemaining = 7;
        return USB_NO_MSG;
      }
      break;
    case DEVICE_CONTROL:
      if (rq->wValue.word == 3)
      {
        // open device
      }
      else if (rq->wValue.word == 0)
      {
        // close device
      }
      break;
    default:
    break;
  }

 
  return 0;
}

uchar usbFunctionWrite(uchar *data, uchar len)
{
  uchar i;

  if (len > bytesRemaining)
    len = bytesRemaining;

  bytesRemaining -= len;

  for (i = 0; i < len; i++)
    buffer[currentPosition++] = data[i];

  if (bytesRemaining == 0)
  {
    UART_setup();
    return 1;
  }
  return 0;
}

void usbFunctionWriteOut(uchar *data, uchar len)
{
  // bulk read
  switch (usbRxToken)
  {
    case BULK_OUT:
      put(&hostDeviceFifo, data, len);
      // if buffer is full data be gone
      break;
  }
  
  return;
}

int main()
{
  uchar i, size;

  wdt_enable(WDTO_1S);

  usbInit();

  usbDeviceDisconnect();
  for (i = 0; i < 250; ++i)
  {
    wdt_reset();
    _delay_ms(2);
  }
  usbDeviceConnect();

  sei();

  while (1)
  {
    wdt_reset();
    usbPoll();
    if(uart_start)
    {
      UART_TRANSCEIVE();
      UART_RECEIVE();
    }
    if (usbInterruptIsReady3())
    {
      if (!isEmpty(&deviceHostFifo))
      {
        size = get(&deviceHostFifo, sendBuffer, SENDBUFSIZE);
        usbSetInterrupt3(sendBuffer, size);
      }
    }
  }
  return 0;
}

// doc http://vusb.wikidot.com/driver-api
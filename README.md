# USB-UART 
</br></br>
## project in progress...
</br></br></br>


## Files
main.hex - firmware for usb-uart on atmega8.

Makefile - build system.

tools/serial_monitor.py - serial monitor implemented in python.

tools/uart_proxy.cpp - uart proxy implementation on esp8266 for testing main board.

## Compilation
make - build project

make flash - burn on chip through programmer stk500v1. I use arduino uno board as programmer with arduinoisp.


## USB-UART Circuit diagram

![USB_UART](https://user-images.githubusercontent.com/108707659/198907135-b436ccb3-076b-4b09-a1f1-59eedfc9d483.png)

## Circuit board and whole environment

![usb-uart_and_uart-proxy-strip](https://user-images.githubusercontent.com/108707659/200113160-c766eea7-4ece-4f0a-b9fa-96a48175beff.jpg)


## High level diagram
![environment](https://user-images.githubusercontent.com/108707659/200113178-2214fb50-fe7b-47c4-8d4b-142e1fa9628c.png)

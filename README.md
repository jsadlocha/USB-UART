# USB-UART 
</br></br>
## project in progress...
</br></br></br>

I use Arduino uno as USB-UART for testing the main board.

## Files
main.hex - firmware for usb-uart on atmega8.

Makefile - build system.

tools/serial_monitor.py - serial monitor implemented in python.

## Compilation
`make` - build project

`make flash` - burn on chip through programmer stk500v1. I use arduino uno board as programmer with arduinoisp.


## USB-UART Circuit diagram

![USB_UART](https://user-images.githubusercontent.com/108707659/198907135-b436ccb3-076b-4b09-a1f1-59eedfc9d483.png)

## Circuit board

![board2](https://user-images.githubusercontent.com/108707659/200307752-016c9318-0601-4c16-a88c-0e95c249611b.jpg)



## High level diagram

![Diagram1](https://user-images.githubusercontent.com/108707659/200307810-6968f86c-220e-453f-810d-168a3441ab24.png)

import serial

print("Usage: python serial_monitor.py <device> <baud_rate>")
print("Example: python serial_monitor.py /dev/ttyACM0 115200")

with serial.Serial('/dev/ttyACM0', 9600, timeout=1) as con:
    while True:
        print('>>> ', end='')
        text = input()
        if (text == "quit"):
            break
        text += '\n'
        con.write(bytearray(text, 'ascii'))
        print(con.readline().decode(), end='')

a = serial.Serial()
con.close()

# stty -F /dev/ttyACM0 cs8 115200 ignbrk -brkint -imaxbel -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke noflsh -ixon -crtscts

# exec 5>/dev/ttyACM0 // open serial monitor
# exec 5>&-  // close file
# echo -ne "dupa\n" > /dev/ttyACM0 // write data
# cat /dev/ttyACM0 // read data

# sudo modprobe usbmon
# sudo wireshark

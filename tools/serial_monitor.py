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

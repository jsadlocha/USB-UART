import serial
import asyncio
import sys

class SerialMonitor:
  def __init__(self, device, baud):
    self.device = device
    self.baud = baud
    self.end = False
    asyncio.run(self.run())

  def writing(self, con):
    while True:
      print('>>> ', end='')
      text = input()
      if (text == "quit"):
        self.end = True
        break
      text += '\n'
      con.write(bytearray(text, 'ascii'))

  def reading(self, con):
    while True:
      print(con.read(255).decode(), end='', flush=True)
      if self.end:
        break

  async def run(self):
    loop = asyncio.get_event_loop()

    with serial.Serial(self.device, self.baud, timeout=1) as con:
      r_task = loop.run_in_executor(None, self.reading, con)
      w_task = loop.run_in_executor(None, self.writing, con)
      await w_task
      await r_task

    print('\nConnection close.')


if __name__ == "__main__":
  device = "/dev/ttyACM0"
  baud = 9600

  if (len(sys.argv) < 2):
    print("Usage: python serial_monitor.py <device> <baud_rate>\n")
    print("Run with default settings:\n")
    print("python serial_monitor.py /dev/ttyACM0 9600\n")
  
  if (len(sys.argv) == 3):
    device = sys.argv[1]
    baud = int(sys.argv[2], 10)
    
  SerialMonitor(device, baud)



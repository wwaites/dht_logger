import time
import serial
from sys import argv, stderr, stdout

port = argv[1]

ser = serial.Serial(port=port, baudrate=115200)
ser.isOpen()
time.sleep(5)

data = ""
while ser.inWaiting():
    data += ser.read(1)
stderr.write(data)

ser.write("d")
time.sleep(2)

data = ""
while ser.inWaiting():
    data += ser.read(1)
stdout.write(data)


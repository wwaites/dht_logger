##    DHT11 Data Logger -- Read data from the logger and write to stdout
##    Copyright (C) 2017 William Waites
##
##    This program is free software: you can redistribute it and/or modify
##    it under the terms of the GNU General Public License as published by
##    the Free Software Foundation, either version 3 of the License, or
##    (at your option) any later version.
##
##    This program is distributed in the hope that it will be useful,
##    but WITHOUT ANY WARRANTY; without even the implied warranty of
##    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
##    GNU General Public License for more details.
##
##    You should have received a copy of the GNU General Public License
##    along with this program.  If not, see <http://www.gnu.org/licenses/>.

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


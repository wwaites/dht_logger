Data Logger for DHT-based Humidity and Temperature sensor

For more sanity, use the Arduino Makefile instead of their IDE:

	brew tap sudar/arduino-mk
	brew install arduino-mk
	sudo pip install pyserial

then just "make upload" possibly tweaking Makefile settings.

Parameters for the program, the number of data points to log
and how often, are in dht_logger.h.

Usage is to run the program on the microcontroller and then
periodically read the data off with the getdata.py script.

See http://www.altpibroch.com/learning/instrumenting-the-instrument
for an application.


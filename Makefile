ARDUINO_DIR   = /Users/ww/Applications/Arduino.app/Contents/Java
AVR_TOOLS_DIR = ${ARDUINO_DIR}/hardware/tools/avr/
ARDMK_DIR     = /usr/local/opt/arduino-mk
MONITOR_PORT ?= /dev/tty.wchusbserial1420
BOARD_TAG    ?= nano

ARDUINO_LIBS = EEPROM DHT TimerOne

include ${ARDMK_DIR}/Arduino.mk

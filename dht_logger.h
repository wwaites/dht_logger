/*
    DHT11 Data Logger -- Logging Humidity and Temperature Data
    Copyright (C) 2017 William Waites

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef DHT_LOGGER_H
#define DHT_LOGGER_H

// which pin the peripheral is on
#define DHT11_PIN 4

// humidity and temperature values are read every second into a circular buffer
// in RAM and then averaged when the buffer is full and written to flash

// how big a circular buffer of values in RAM -- default 30 (seconds)
#define RAM_COUNT 30
// how big a circular buffer in flash -- default 384 (x 30 seconds or about 3 hours)
#define PROM_COUNT 384

// set to true to reinitialise flash on startup (should be done by pressing the button or something
#define PROM_RESET false

#endif /* DHT_LOGGER_H */

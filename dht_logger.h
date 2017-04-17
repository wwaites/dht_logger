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

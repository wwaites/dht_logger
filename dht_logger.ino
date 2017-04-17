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
#include <dht.h>
#include <EEPROM.h>
#include <TimerOne.h>
#include "dht_logger.h"
#include "MeanBuffer.h"
#include "EEPROMBuffer.h"

MeanBuffer h_ram, t_ram;
EEPROMBuffer<0> h_prom;
EEPROMBuffer<1> t_prom;

dht DHT;

int ticks = 0;
int dht_error = 0;

void tick() {
  if (dht_error != DHTLIB_OK) {
    return;
  }
  h_ram.push(DHT.humidity);
  t_ram.push(DHT.temperature);
  ticks++;
}

void dump() {
  for (int i=0; i<PROM_COUNT; i++) {
    byte h = h_prom.read(i);
    byte t = t_prom.read(i);
    Serial.print(i);
    Serial.print("\t");
    Serial.print(h);
    Serial.print("\t");
    Serial.println(t);
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println(F("DHT LOGGER "));
  Serial.print(F("DHT LIBRARY VERSION: "));
  Serial.println(DHT_LIB_VERSION);

  h_prom.init(PROM_COUNT, PROM_RESET);
  h_prom.push(255);
  t_prom.init(PROM_COUNT, PROM_RESET);
  t_prom.push(255);

  Timer1.initialize(1000000);
  Timer1.attachInterrupt(tick);
}

void loop() {
  dht_error = DHT.read11(DHT11_PIN);
  switch (dht_error) {
  case DHTLIB_OK:
    break;
  case DHTLIB_ERROR_CHECKSUM:
    Serial.println(F("Checksum error"));
    break;
  case DHTLIB_ERROR_TIMEOUT: 
    Serial.println(F("Time out error")); 
    break;
  default: 
    Serial.println(F("Unknown error"));
    break;
  }

  if (ticks > RAM_COUNT) {
    digitalWrite(LED_BUILTIN, HIGH);
    cli();
    byte h_avg = h_ram.mean();
    byte t_avg = t_ram.mean();
    h_prom.push(h_avg);
    t_prom.push(t_avg);
    ticks = 0;
    sei();
  }

  while (Serial.available() > 0) {
    int byte = Serial.read();
    switch (byte) {
    case 'd':
      dump();
      break;
    case 'p':
      h_prom.report();
      t_prom.report();
      break;
    default:
      Serial.println("Unknown command.");
    }
  }

  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
}

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
#ifndef EEPROM_BUFFER_H
#define EEPROM_BUFFER_H

#include <EEPROM.h>

#define EEPROM_BUFFERS 4
#define EEPROM_BUFBASE (EEPROM_BUFFERS * sizeof(eeprom_header_t))

struct eeprom_header_t {
  uint16_t offset;
  uint16_t size;
  uint16_t index;
};

template<byte slot>
class EEPROMBuffer {
 public:
  void init() {
    EEPROM.get(slot * sizeof(eeprom_header_t), header);
    report();
  };

  void report() {
    Serial.print(F("EEPROM Buffer "));
    Serial.print(slot);
    Serial.print(" ");
    Serial.print(header.offset);
    Serial.print("+");
    Serial.print(header.index);
    Serial.print("/");
    Serial.println(header.size);
  };

  void init(uint16_t size, bool reset) {
    if (reset) {
      header.size   = size;
      header.offset = EEPROM_BUFBASE;
      for (byte i=0; i<slot; i++) {
        eeprom_header_t h;
        EEPROM.get(i * sizeof(eeprom_header_t), h);
        header.offset += h.size;
      }
      header.index = 0;
      EEPROM.put(slot * sizeof(eeprom_header_t), header);
      for (uint16_t i=0; i<size; i++) {
        push(0);
      }
    }

    init();

    if (size != header.size) {
      Serial.print(F("EEPROM Buffer mismatch: found "));
      Serial.print(header.size);
      Serial.print(F(" expected "));
      Serial.println(size);
    }

  };

  void push(byte b) {
    EEPROM.write(header.offset + header.index, b);
    header.index++;
    if (header.index >= header.size)
      header.index = 0;
    EEPROM.put(slot * sizeof(eeprom_header_t) + 2*sizeof(uint16_t), header.index);
  }

  byte read(uint16_t index) {
    uint16_t addr = header.offset + ((header.index + index) % header.size);
    return EEPROM.read(addr);
  }

 private:
  eeprom_header_t header;
};

#endif /* EEPROM_BUFFER_H */

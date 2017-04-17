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
#ifndef MEAN_BUFFER_H
#define MEAN_BUFFER_H

#include "CircularBuffer.h"

class MeanBuffer : public CircularBuffer<byte, RAM_COUNT> {
 public:
  byte mean() {
    uint16_t n = remain();
    uint16_t sum = 0;
    while (remain() > 0) {
      sum += pop();
    }
    return sum/n;
  }
};

#endif /* MEAN_BUFFER_H */

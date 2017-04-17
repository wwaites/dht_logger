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

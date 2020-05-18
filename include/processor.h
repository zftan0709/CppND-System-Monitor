#ifndef PROCESSOR_H
#define PROCESSOR_H
#include "linux_parser.h"

class Processor {
 public:
  float Utilization();

 private:
 long prevTotal{0};
 long prevActive{0};
};

#endif
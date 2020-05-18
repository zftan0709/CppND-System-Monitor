#ifndef PROCESS_H
#define PROCESS_H
#include "linux_parser.h"
#include <string>
#include <vector>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  Process(int id);
  int Pid();
  std::string User();
  std::string Command();
  float CpuUtilization();
  std::string Ram();
  long int UpTime(); 
  bool operator<(Process const& a) const; 

 private:
  int id_;
  float cpuUtil_;
  int ram_;
  long int upTime_;
  std::string command_;
  std::string user_;
};

#endif
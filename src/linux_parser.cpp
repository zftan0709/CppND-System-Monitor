#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// Read and return the system operating system
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// Read and return the system kernel
string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
  float value,memTotal,memFree;
  string info,line;
  std::ifstream stream(kProcDirectory + kMeminfoFilename);
  if(stream.is_open()){
    while(std::getline(stream,line)){
      std::istringstream lineStream(line);
      while(lineStream >> info >> value){
        if(info == "MemTotal:"){
          memTotal = value;
        }
        else if(info == "MemFree:")
        {
          memFree = value;
        }
      }
    }
  }
  return (memTotal-memFree)/memTotal; 
}

// Read and return the system uptime
long LinuxParser::UpTime() { 
  long upTime,idleTime;
  string line;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if(stream.is_open()){
    std::getline(stream,line);
    std::istringstream linestream(line);
    linestream >> upTime >> idleTime;
  }
  return upTime;
}

// Read and return CPU utilization
vector<float> LinuxParser::CpuUtilization() {
  vector<float> cpuStat;
  string line, cpu;
  int tmp;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if(stream.is_open()){
    while(std::getline(stream,line)){
      std::istringstream linestream(line);
      linestream >> cpu;
      if(cpu != "cpu")continue;
      while(linestream >> tmp){
        cpuStat.push_back(tmp);
      }
      break;
    }
  }
  return cpuStat;
}

// Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  int numTotalProcesses;
  string processes;
  string line;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while(std::getline(stream, line)){
      std::istringstream linestream(line);
      linestream >> processes >> numTotalProcesses;
      if(processes == "processes")
      {
        return numTotalProcesses;
      }
    }
  }
  return -1;
}

// Read and return the number of running processes
int LinuxParser::RunningProcesses() {
  int numRunningProcesses;
  string processes;
  string line;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while(std::getline(stream, line)){
      std::istringstream linestream(line);
      linestream >> processes >> numRunningProcesses;
      if(processes == "procs_running")
      {
        return numRunningProcesses;
      }
    }
  }
  return -1;
}

// Read and return the command associated with a process
string LinuxParser::Command(int pid) {
  string command;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kCmdlineFilename);
  if(stream.is_open()){
    std::getline(stream,command);
  }
  return command;
}

// Read and return the memory used by a process
int LinuxParser::Ram(int pid) {
  string line,key;
  int ram = 0;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatusFilename);
  if(stream.is_open()){
    while(std::getline(stream,line)){
      std::istringstream linestream(line);
      linestream >> key;
      if(key == "VmSize:"){ 
        linestream >> ram;
        break;
      }
    }
  }
  return ram/1000;
}

// Read and return the user ID associated with a process
string LinuxParser::Uid(int pid) {
  string line,key,value;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatusFilename);
  if(stream.is_open()){
    while(std::getline(stream,line)){
      std::istringstream linestream(line);
      linestream >> key;
      if(key == "Uid:"){
        linestream >> value;
        break;
      }
    }
  }
  return value;
}

// Read and return the user associated with a process
string LinuxParser::User(int pid) {
  string uid = Uid(pid);
  string line,user{"N/A"};
  std::ifstream stream(kPasswordPath);
  if(stream.is_open()){
    while(std::getline(stream,line)){
      if(line.find(uid) != std::string::npos){
        std::replace(line.begin(),line.end(),':',' ');
        std::istringstream linestream(line);
        linestream >> user;
        break;
      }
    }
  }
  return user;
}

// Read and return the uptime of a process
long LinuxParser::UpTime(int pid) {
  string line,value;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatFilename);
  if(stream.is_open()){
      std::getline(stream,line);
      std::istringstream linestream(line);
      int count = 0;
      while(count < 22){
        linestream >> value;
        count++;
      }
  }
  long startTime = (value=="")? 0:std::stol(value);
  return UpTime() - startTime/sysconf(_SC_CLK_TCK);
}

// Read and return CPU utilization of a process
float LinuxParser::CpuUtilization(int pid) {
  string line,value;
  float utime,stime,cutime,cstime;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatFilename);
  if(stream.is_open()){
    std::getline(stream,line);
    std::istringstream linestream(line);
    int count = 0;
    while(count < 13){
      linestream >> value;
      count++;
    }
    linestream>>utime>>stime>>cutime>>cstime;
  }
  float upTime = float(UpTime(pid));
  float totalTime = (utime + stime + cutime + cstime)/sysconf(_SC_CLK_TCK);
  upTime = (upTime - 0 < 0.001) ? 0.001:upTime; 
  return totalTime/upTime;
}
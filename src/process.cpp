#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"

using std::string;
using std::to_string;
using std::vector;

Process::Process(int id){
    id_ = id;
    ram_ = LinuxParser::Ram(id);
    upTime_ = LinuxParser::UpTime(id);
    command_ = LinuxParser::Command(id);
    cpuUtil_ = LinuxParser::CpuUtilization(id);
    user_ = LinuxParser::User(id);
}
// Return this process's ID
int Process::Pid() { return id_; }

// Return this process's CPU utilization
float Process::CpuUtilization() { return cpuUtil_; }

// Return the command that generated this process
string Process::Command() { return command_; }

// Return this process's memory utilization
string Process::Ram() { return std::to_string(ram_); }

// Return the user (name) that generated this process
string Process::User() { return user_; }

// Return the age of this process (in seconds)
long int Process::UpTime() { return upTime_; }

// Overload the "less than" comparison operator for Process objects
bool Process::operator<(Process const& a) const {
    return this->cpuUtil_ > a.cpuUtil_ ? true:false;
}
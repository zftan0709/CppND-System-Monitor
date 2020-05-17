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
// TODO: Return this process's ID
int Process::Pid() { return id_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { return cpuUtil_; }

// TODO: Return the command that generated this process
string Process::Command() { return command_; }

// TODO: Return this process's memory utilization
string Process::Ram() { return std::to_string(ram_); }

// TODO: Return the user (name) that generated this process
string Process::User() { return user_; }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return upTime_; }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a[[maybe_unused]]) const {
    return this->cpuUtil_ > a.cpuUtil_ ? true:false;
}
#include "processor.h"
using namespace LinuxParser;
// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
    std::vector<float> cpuStat = CpuUtilization();
    float curActive = cpuStat[CPUStates::kUser_]+cpuStat[CPUStates::kNice_]+cpuStat[CPUStates::kSystem_]+
    cpuStat[CPUStates::kIRQ_]+cpuStat[CPUStates::kSoftIRQ_]+cpuStat[CPUStates::kSteal_];

    float curTotal = curActive + cpuStat[CPUStates::kIdle_]+cpuStat[CPUStates::kIOwait_];

    float cpu_percentage = (curActive - prevActive)/(curTotal - prevTotal);
    prevTotal = curTotal;
    prevActive = curActive;
    return cpu_percentage;
}
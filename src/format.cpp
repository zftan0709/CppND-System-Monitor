#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds[[maybe_unused]]) {
    int minutes = seconds/60;
    int hours = minutes/60;
    //return std::to_string(hours)+":"+std::to_string(minutes%60)+":"+std::to_string(seconds%60);
    std::stringstream ss;
    ss << std::setfill('0') << hours << ":" << std::setw(2) << minutes%60 << ":" << std::setw(2) << seconds%60;
    return ss.str();
}
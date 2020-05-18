#include <string>

#include "format.h"

using std::string;

// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
string Format::ElapsedTime(long seconds) {
    int minutes = seconds/60;
    int hours = minutes/60;
    //return std::to_string(hours)+":"+std::to_string(minutes%60)+":"+std::to_string(seconds%60);
    std::stringstream ss;
    ss << std::setfill('0') << hours << ":" << std::setw(2) << minutes%60 << ":" << std::setw(2) << seconds%60;
    return ss.str();
}
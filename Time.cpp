//
// Created by User on 01.02.2026..
//

#include "Time.h"
#include <ctime>
#include <iostream>

Time::Time(std::istream& input, std::ostream& output)
    : Command(input, output){
}


void Time::execute()
{
    std::time_t currentTime = std::time(nullptr);

    std::tm localTime;
    localtime_s(&localTime, &currentTime);

    int hour = localTime.tm_hour;
    int min = localTime.tm_min;
    int sec = localTime.tm_sec;

    *output
        << (hour < 10 ? "0" : "") << hour << ":"
        << (min < 10 ? "0" : "") << min << ":"
        << (sec < 10 ? "0" : "") << sec
        << std::endl;
}
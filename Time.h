//
// Created by User on 01.02.2026..
//

#ifndef PROJEKAT_TIME_H
#define PROJEKAT_TIME_H


#pragma once
#include "Command.h"
class Time : public Command
{
public:
    Time(std::istream& input, std::ostream& output);
    void execute() override;
};



#endif //PROJEKAT_TIME_H
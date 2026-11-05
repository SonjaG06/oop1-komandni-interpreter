//
// Created by User on 31.01.2026..
//

#ifndef PROJEKAT_DATE_H
#define PROJEKAT_DATE_H


#pragma once
#include "Command.h"
class Date : public Command
{
public:
    Date(std::istream& input, std::ostream& output);
    void execute() override;
};

#endif //PROJEKAT_DATE_H
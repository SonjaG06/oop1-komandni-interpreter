//
// Created by User on 24.02.2026..
//

#ifndef PROJEKAT_HEAD_H
#define PROJEKAT_HEAD_H

#include "Command.h"
#include <string>

class Head : public Command {
public:
    Head(std::istream& input, std::ostream& output, int n);
    void execute() override;
private:
    int n; //broj linija koje treba da ispise
};


#endif //PROJEKAT_HEAD_H
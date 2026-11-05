#ifndef ECHO_H
#define ECHO_H

#include <string>

#include "Command.h"

class Echo : public Command{
public:
    Echo(std::istream& input, std::ostream& output);

    void execute();

};

#endif
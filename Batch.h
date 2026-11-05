#ifndef PROJEKAT_BATCH_H
#define PROJEKAT_BATCH_H

#include <string>
#include "Command.h"

class Interpreter;

class Batch : public Command{
public:
    Batch(std::istream& input, std::ostream& output, Interpreter& interpreter);
    void execute() override;

private:
    Interpreter& interpreter;
};

#endif
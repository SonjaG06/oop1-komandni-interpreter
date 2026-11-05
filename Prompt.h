//
// Created by User on 16.02.2026..
//

#ifndef PROJEKAT_PROMPT_H
#define PROJEKAT_PROMPT_H

#include "Command.h"
#include <string>

class Interpreter; // resava kruznu zavisnost

class Prompt : public Command {
public:
    Prompt(std::istream& input, std::ostream& output, const std::string& newPrompt, Interpreter* interpreter); // konstruktor za promenu prompta
    void execute() override;

private:
    std::string parameter;
    Interpreter* interpreter;
};

#endif // PROJEKAT_PROMPT_H

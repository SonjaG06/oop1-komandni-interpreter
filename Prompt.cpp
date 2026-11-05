#include "Prompt.h"
#include "Interpreter.h"

Prompt::Prompt(std::istream& input, std::ostream& output, const std::string& newPrompt, Interpreter* interpreter)
    : Command(input, output), parameter(newPrompt), interpreter(interpreter)
{
}

void Prompt::execute()
{
    if (interpreter)
        interpreter->setPrompt(parameter);
}

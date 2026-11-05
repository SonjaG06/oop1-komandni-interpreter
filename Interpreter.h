#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <string>
#include <iostream>
#include <vector>
#include "Parser.h"

class Interpreter
{
public:
    Interpreter() = default;

    void run();

    void executeCommand(const std::string& line, std::ostream* defaultOut=&std::cout);

    void setPrompt(const std::string& newPrompt);

    bool isRunning() const;

private:
    bool running = true;       // status interpreter-a
    std::string prompt = "$ "; // trenutni prompt

    // Glavni handler komandi
    void commandHandler(const std::string &command,
                        const std::string &argument,
                        bool quotedArgument,
                        const std::string &option,
                        const std::string &secondArgument = "",
                        std::istream* input = &std::cin,
                        std::ostream* output = &std::cout);

    std::vector<std::string> splitPipe(std::string line);

    void handleExit();
    void handleEcho(std::istream* input, std::ostream* output);
    void handleWordCount(std::istream* input, std::ostream* output, const std::string &option);
    void handleHead(std::istream* input, std::ostream* output, const std::string &option);
    void handlePrompt(std::istream* input, std::ostream* output, const std::string& argument);
    void handleBatch(std::istream* input, std::ostream* output);
    void handleDate(std::istream* input, std::ostream* output);
    void handleTime(std::istream* input, std::ostream* output);
    void handleTouch(std::istream* input, std::ostream* output, const std::string &argument);
    void handleRemove(std::istream* input, std::ostream* output, const std::string &argument);
    void handleTr(std::istream* input, std::ostream* output, const std::string &option, const std::string &with);
    void handleTruncate(std::istream* input, std::ostream* output, const std::string &argument);
    std::istream* handleInput(bool isQuoted, std::string argument, std::string commandName);
    std::ostream* handleOutput(std::string parserOutput, Parser::RedirectType fileMode, std::ostream* defaultOut=&std::cout);
};

#endif // INTERPRETER_H
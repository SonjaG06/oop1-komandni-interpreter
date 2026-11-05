#include "Interpreter.h"

#include <complex>

#include "Parser.h"
#include "Exception.h"
#include "Echo.h"
#include "WordCount.h"
#include "Head.h"
#include "Batch.h"
#include "Date.h"
#include "Time.h"
#include "Touch.h"
#include "Remove.h"
#include "Translate.h"
#include "Prompt.h"

#include <iostream>
#include <fstream>
#include <ranges>
#include <sstream>

#include "Truncate.h"

void Interpreter::run()
{
    while (running)
    {
        std::cout << prompt;

        std::string line;
        if (!std::getline(std::cin, line))
            break;
        executeCommand(line);
    }
}

bool Interpreter::isRunning() const
{
    return running;
}

void Interpreter::setPrompt(const std::string& newPrompt)
{
    prompt = newPrompt + " ";
}

//izvrsavanje komande
void Interpreter::executeCommand(const std::string& line, std::ostream* defaultOut)
{
    std::vector<std::string> commandsString = splitPipe(line);
    try
    {
        std::istream* prevOutput;
        for (int i = 0; i < commandsString.size(); ++i) {
            Parser parser(commandsString[i]);
            parser.parse();
            std::istream* commandInput = (i == 0) ? &std::cin : prevOutput;
            std::ostream* commandOutput = defaultOut;
            std::stringstream *buffer = nullptr;
            if (i!=0 and !parser.getArgument().empty()) throw Exception("input nije dozvoljan u cevovodu");
            if (i!=commandsString.size()-1 && !parser.getOutput().empty()) throw Exception("output nije dozvoljen u cevovodu");
            if (!parser.getArgument().empty()) {
                commandInput = handleInput(parser.isQuoted(),parser.getArgument(), parser.getCommand());
            }
            if (i<commandsString.size()-1) {
                buffer = new std::stringstream();
                commandOutput = buffer;
            }
            else if (!parser.getOutput().empty()) {
                commandOutput = handleOutput(parser.getOutput(),parser.getFileMode(),defaultOut);
            }
            commandHandler(parser.getCommand(), parser.getArgument(), parser.isQuoted(),parser.getOption(),parser.getSecondArgument(),
                commandInput,
                commandOutput);
            if (buffer) {
                prevOutput = buffer;
            }
            std::cout << std::endl;
        }
    }
    catch (const Exception& e)
    {
        std::cout << e.what() << std::endl;
    }
}


void Interpreter::commandHandler(const std::string& command,
                                 const std::string& argument,
                                 const bool quotedArgument,
                                 const std::string& option,
                                 const std::string& secondArgument,
                                 std::istream* input,
                                 std::ostream* output) {
    if (command == "exit")
        handleExit();

    else if (command == "echo")
        handleEcho(input, output);

    else if (command == "date") {
        if (!argument.empty()) {
            throw Exception("Funkcija ne treba da prima argument");
        }
            handleDate(input, output);
    }

    else if (command == "time") {
        if (!argument.empty()) {
            throw Exception("Funkcija ne treba da prima argument");
        }
            handleTime(input, output);
    }

    else if (command == "touch") {
        if (quotedArgument) {
            throw Exception("Argument ne sme biti pod navodnicima");
        }
        handleTouch(input, output, argument);
    }

    else if (command == "rm")
        handleRemove(input, output, argument);

    else if (command == "wc")
        handleWordCount(input, output, option);

    else if (command == "head")
        handleHead(input, output, option);

    else if (command == "prompt") {
        handlePrompt(input,output,argument);
    }
    else if (command == "batch")
        handleBatch(input, output);

    else if (command == "tr") {
        handleTr(input, output, option, secondArgument);
    }
    else if (command == "truncate")
        handleTruncate(input,output,argument);

    else if (!command.empty())
        throw Exception("Nepoznata komanda: " + command);
}

//hendleri

void Interpreter::handleExit()
{
    running = false;
}


void Interpreter::handleEcho(std::istream* input, std::ostream* output)
{
    Echo e(*input,*output);
    e.execute();
    output->flush();
}

void Interpreter::handleWordCount(std::istream* input, std::ostream* output, const std::string& option)
{
    WordCount wc(*input, *output, option);
    wc.execute();
    output->flush();
}

void Interpreter::handleHead(std::istream* input, std::ostream* output, const std::string& option)
{
    int numLines = 10;

    if (option.rfind("-n", 0) == 0)
    {
        try
        {
            numLines = std::stoi(option.substr(2));
        }
        catch (...)
        {
            throw Exception("Greska! Nevalidan broj linija.");
        }
    }

    Head h(*input, *output, numLines);\
    h.execute();
    output->flush();
}

void Interpreter::handlePrompt(std::istream* input, std::ostream* output, const std::string& argument)
{
    if (argument.empty())
        throw Exception("Greska! Prompt ne sme biti prazan.");

    Prompt p(*input,*output,argument,this);
    p.execute();
}

void Interpreter::handleBatch(std::istream* input, std::ostream* output)
{
    Batch b(*input, *output, *this);
    b.execute();
    output->flush();
}

void Interpreter::handleDate(std::istream* input, std::ostream* output)
{
    Date d(*input, *output);
    d.execute();
    output->flush();
}

void Interpreter::handleTime(std::istream* input, std::ostream* output)
{
    Time t(*input, *output);
    t.execute();
    output->flush();
}


void Interpreter::handleTouch(std::istream* input, std::ostream* output, const std::string& argument)
{
    if (argument.empty())
        throw Exception("Greska! Nije uneto ime fajla.");

    Touch t(*input, *output, argument);
    t.execute();
    output->flush();
}

void Interpreter::handleRemove(std::istream* input, std::ostream* output, const std::string& argument)
{
    if (argument.empty())
        throw Exception("Greska! Nije uneto ime fajla.");

    Remove r(*input, *output, argument);
    r.execute();
    output->flush();
}

void Interpreter::handleTr(std::istream *input, std::ostream* output, const std::string& option, const std::string& with) {
    Translate tr(*input, *output ,option, with);
    tr.execute();
    output->flush();
}

void Interpreter::handleTruncate(std::istream *input, std::ostream *output, const std::string &argument) {
    Truncate tr(*input, *output, argument);
    tr.execute();
    output->flush();
}


//citanje unosa
std::istream* Interpreter::handleInput(bool isQuoted, std::string argument, std::string commandName) {
    if (commandName == "touch" or commandName == "rm" or commandName == "truncate") {
        return &std::cin;
    }
    std::istream *input;
    if (isQuoted) {
        input = new std::istringstream(argument);
    }
    else if (!argument.empty()) {
        if (argument[0] == '<') {
            argument.erase(0,1);
        }
        input = new std::ifstream(argument);
        if (!dynamic_cast<std::ifstream*>(input)->is_open()) {
            throw Exception("Nije moguce otvoriti fajl");
        }
    }
    else {
        input = &std::cin;
    }
    return input;
}

std::ostream* Interpreter::handleOutput(std::string parserOutput, Parser::RedirectType fileMode, std::ostream* defaultOut) {
    std::ostream *output;
    if (!parserOutput.empty()) {
        if (fileMode == Parser::RedirectType::Append) {
            output = new std::ofstream(parserOutput,std::ios_base::app);
        }
        else {
            output = new std::ofstream(parserOutput);
        }
        if (!dynamic_cast<std::ofstream*>(output)->is_open()) {
            throw Exception("Neuspesno otvaranje redirekcionog fajla");
            return output;
        }
    }
    else {
        output = defaultOut;
    }
    return output;
}

std::vector<std::string> Interpreter::splitPipe(std::string line) {
    bool inQuotes = false;
    std::vector<std::string> result;
    std::string current = "";
    for (int i = 0; i < line.size(); i++) {
        if (line[i] == '\"') {
            inQuotes = !inQuotes;
            current += line[i];
        }
        else if (line[i] == '|' and !inQuotes) {
            result.push_back(current);
            current = "";
        }
        else
            current += line[i];
    }
    result.push_back(current);
    return result;
}

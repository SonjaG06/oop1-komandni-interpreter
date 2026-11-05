//
// Created by User on 16.02.2026..
//

#ifndef PROJEKAT_REMOVE_H
#define PROJEKAT_REMOVE_H
#include "Command.h"
#include <string>


class Remove : public Command {
public:
    explicit Remove(std::istream& input, std::ostream& output, const std::string& filename);
    void execute() override;
private:
    std::string filename;
};


#endif //PROJEKAT_REMOVE_H
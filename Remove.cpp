#include "Remove.h"
#include "Exception.h"
#include <filesystem>
#include <iostream>

Remove::Remove(std::istream& input, std::ostream& output, const std::string& filename)
    : Command(input, output), filename(filename)
{

}

void Remove::execute()
{
    if (!std::filesystem::remove(filename)) {
        throw Exception("Greska! Fajl ne postoji!");
    }
}

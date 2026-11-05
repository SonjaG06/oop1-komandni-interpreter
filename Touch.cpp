//
// Created by User on 01.02.2026..
//

#include "Touch.h"
#include "Exception.h"
#include <fstream>
#include <iostream>

Touch::Touch(std::istream& input, std::ostream& output, const std::string& filename)
    : Command(input, output), filename(filename) {

}

void Touch::execute() {
    if (filename==" ") {
        throw Exception("Greska! Morate uneti ime fajla!");
    }

    // provera da li fajl vec postoji
    std::ifstream in(filename);
    if (in.is_open()) {
        throw Exception("Greska! Fajl vec postoji!");
    }

    // kreiranje novog fajla
    std::ofstream out(filename);
    if (!out) {
        throw Exception("Greska! Fajl ne moze da se kreira!");
    }
    out.close();
}
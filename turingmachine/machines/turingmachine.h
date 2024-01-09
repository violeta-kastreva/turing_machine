//
// Created by Vily on 31.12.2023 г..
//

#ifndef TURING_MACHINE_TURINGMACHINE_H
#define TURING_MACHINE_TURINGMACHINE_H

#include <string>

class TuringMachine {

public:
    virtual void init(std::istream& inputStream) = 0;

    virtual void run(const std::string& outputFileName) = 0;
};

#endif //TURING_MACHINE_TURINGMACHINE_H

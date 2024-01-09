#pragma once
#ifndef TURING_MACHINE_TURINGMACHINEFACTORY_H
#define TURING_MACHINE_TURINGMACHINEFACTORY_H

#include <string>
#include "../machines/regularturingmachine.h"

/**
* Factory class for Turing Machines, returns the needed machine based on the input
*/
class TuringMachineFactory {
public:
    TuringMachineFactory();
    TuringMachine * getMachine(const std::string& fileName);
private:
};

#endif //TURING_MACHINE_TURINGMACHINEFACTORY_H

#pragma once
#ifndef TURING_MACHINE_TURINGMACHINEFACTORY_H
#define TURING_MACHINE_TURINGMACHINEFACTORY_H

#include <string>
#include "../machines/RegularTuringMachine.h"

class TuringMachineFactory {
public:

    TuringMachineFactory();

    TuringMachine* getMachine(const std::string& fileName);
};


#endif //TURING_MACHINE_TURINGMACHINEFACTORY_H

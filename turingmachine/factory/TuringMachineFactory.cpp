#include <iostream>
#include <fstream>
#include "TuringMachineFactory.h"
#include "../machines/RegularTuringMachine.h"
#include "../machines/CompositionTuringMachine.h"
#include "../machines/ConditionalTuringMachine.h"
#include "../machines/IterationTuringMachine.h"
#include "../multitape/MultitapeTuringMachine.h"

TuringMachineFactory::TuringMachineFactory() = default;

TuringMachine* TuringMachineFactory::getMachine(const std::string &fileName) {
    std::ifstream tmData(fileName);
    if (!tmData.is_open()) {
        throw std::runtime_error("Unable to open file: " + fileName);
    }

    std::string machineType;
    std::getline(tmData, machineType);

    TuringMachine* machine = new RegularTuringMachine();

    if(machineType == "REGULAR"){
        machine = new RegularTuringMachine();
    } else if (machineType == "COMPOSITION"){
        machine = new CompositionTuringMachine();
    } else if (machineType == "CONDITIONAL"){
        machine = new ConditionalCompositionTuringMachine();
    } else if (machineType == "LOOP"){
        machine = new IterationLoopTuringMachine();
    } else if (machineType == "MULTITAPE"){
        machine = new MultiTapeTuringMachine();
    }

    machine->init(tmData);

    return machine;
}

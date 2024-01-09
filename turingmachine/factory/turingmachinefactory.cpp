#include <iostream>
#include <fstream>
#include "turingmachinefactory.h"
#include "../machines/regularturingmachine.h"
#include "../machines/compositionturingmachine.h"
#include "../machines/conditionalturingmachine.h"
#include "../machines/iterationturingmachine.h"
#include "../machines/multitapeturingmachine.h"

/**
* Default constructor
*/
TuringMachineFactory::TuringMachineFactory() = default;

/**
* Opens the input files, and based on the first line of the input, returns the needed machine type
*/
TuringMachine* TuringMachineFactory::getMachine(const std::string &fileName) {
    std::ifstream tmData(fileName);
    if (!tmData.is_open()) {
        std::cerr << "Unable to open file: " << fileName << std::endl;
        return nullptr;
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
        // machine = new MultiTapeTuringMachine();
    }

    // Call init method after object creation to properly initialize it
    if (machine != nullptr) {
        machine->init(tmData);
    }

    return machine;
}

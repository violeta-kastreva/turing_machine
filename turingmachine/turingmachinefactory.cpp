#include <iostream>
#include <fstream>
#include "turingmachinefactory.h"
#include "turingmachine.h"
#include "compositionturingmachine.h"
#include "conditionalturingmachine.h"
#include "iterationturingmachine.h"
#include "multitapeturingmachine.h"

TuringMachineFactory::TuringMachineFactory() = default;

TuringMachine* TuringMachineFactory::getMachine(const std::string &fileName) {
    std::ifstream tmData(fileName);
    std::string machineType;
    std::getline(tmData, machineType);

    if (!tmData.is_open()) {
        std::cerr << "Unable to open file: " << fileName << std::endl;
        return nullptr;
    }


    if(machineType == "REGULAR"){
        return new TuringMachine(fileName);
    } else if (machineType == "COMPOSITION"){
       // return new CompositionTuringMachine(fileName);
    } else if (machineType == "CONDITIONAL"){
       // return new ConditionalTuringMachine(fileName);
    } else if (machineType == "LOOP"){
       // return new IterationLoopTuringMachine(fileName);
    } else if (machineType == "MULTITAPE"){
       // return new MultiTapeTuringMachine(fileName);
    }

    tmData.close();
    return nullptr;
}
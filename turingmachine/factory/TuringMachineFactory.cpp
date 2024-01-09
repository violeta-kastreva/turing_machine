#include <iostream>
#include <fstream>
#include "TuringMachineFactory.h"
#include "../machines/RegularTuringMachine.h"
#include "../machines/CompositionTuringMachine.h"
#include "../machines/ConditionalTuringMachine.h"
#include "../machines/IterationTuringMachine.h"
#include "../machines/MultitapeTuringMachine.h"

/**
 * @brief Default constructor for TuringMachineFactory.
 */
TuringMachineFactory::TuringMachineFactory() = default;

/**
 * @brief Creates and returns a Turing machine instance based on the input file.
 * @param fileName The name of the file containing the Turing machine specifications.
 * @return A pointer to the created Turing machine instance.
 * @exception std::runtime_error Thrown if the file cannot be opened or the machine type is unknown.
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
        machine = new MultiTapeTuringMachine();
    } else {
        throw std::runtime_error("Unknown machine type: " + machineType);
    }


    // Call init method after object creation to properly initialize it
    if (machine != nullptr) {
        machine->init(tmData);
    }

    return machine;
}

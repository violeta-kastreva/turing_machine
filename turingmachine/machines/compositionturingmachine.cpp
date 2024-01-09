/**
 * @file CompositionTuringMachine.cpp
 * @brief Implementation of the CompositionTuringMachine class.
 *
 * This file contains the implementation of the CompositionTuringMachine class, including methods to initialize
 * and run the composed machines.
 */

#include "compositionturingmachine.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>
#include "turingmachine.h"
#include "../parsers/compositionparser.h"

#include "CompositionTuringMachine.h"
#include <fstream>

CompositionTuringMachine::CompositionTuringMachine() {
    // Empty constructor
}

CompositionTuringMachine::CompositionTuringMachine(std::istream& inputStream) {
    init(inputStream);
}

void CompositionTuringMachine::init(std::istream& inputStream) {
    CompositionMachineParser parser(inputStream);
    parser.parse();
    machine1 = parser.getFirstMachine();
    machine2 = parser.getSecondMachine();
    machine1->setTape(parser.getTape());
    machine1->setCurrentPosition(1);

}

void CompositionTuringMachine::run(const std::string &outputFileName) {
    // Assuming machine1 and machine2 are correctly initialized
    if (machine1 && machine2) {
        machine1->run(outputFileName);  // Run the first machine

        std::string intermediateTape = machine1->getTape();
        machine2->setTape(intermediateTape);  // Set the tape for the second machine

        machine2->setCurrentPosition(machine1->getCurrentPosition());  // Reset position for the second machine
        machine2->run(outputFileName);  // Run the second machine
    } else {
        std::cerr << "Error: Machines not initialized properly in CompositionTuringMachine." << std::endl;
    }
}

void CompositionTuringMachine::setMachines(std::unique_ptr<RegularTuringMachine> m1, std::unique_ptr<RegularTuringMachine> m2) {
    machine1 = std::move(m1);
    machine2 = std::move(m2);
}


/**
 * @file ConditionalCompositionTuringMachine.cpp
 * @brief Implementation of the ConditionalCompositionTuringMachine class.
 *
 * This file contains the implementation of the ConditionalCompositionTuringMachine class, including methods to initialize
 * and run the conditional sequence of machines.
 */
#include <memory>
#include <iostream>
#include <fstream>
#include <filesystem>
#include "ConditionalTuringMachine.h"
#include "../parsers/ConditionalParser.h"

/**
 * @brief Initializes the Turing machine with input data from an input stream.
 *
 * Uses the ConditionalCompositionMachineParser to parse the configuration of three Turing machines
 * and sets up the initial state for the first machine. The first machine (machine1) is set with the tape
 * of the third machine (machine3) and its initial position is set to 1.
 *
 * @param inputStream The input stream to read data from.
 */
void ConditionalCompositionTuringMachine::init(std::istream& inputStream) {
    ConditionalCompositionMachineParser parser(inputStream);
    parser.parse();

    machine1 = parser.getFirstMachine();
    machine2 = parser.getSecondMachine();
    machine3 = parser.getThirdMachine();
    machine1->setTape(machine3->getTape());
    machine1->setCurrentPosition(1);
}

/**
 * @brief Runs the conditional composition Turing machine and outputs the result to a file.
 *
 * Executes the first machine (machine1) and based on the current symbol in the tape, decides whether to
 * run the second machine (machine2) or the third machine (machine3). The output is written to the specified file.
 *
 * @param outputFileName Name of the file to write the output to.
 */
void ConditionalCompositionTuringMachine::run(const std::string& outputFileName) {
    machine1->run(outputFileName);

    std::string intermediateTape = machine1->getTape();
    char currentSymbol = intermediateTape[machine1->getCurrentPosition()];

    if (conditionalSymbols.find(currentSymbol) != conditionalSymbols.end()) {
        machine2->setTape(intermediateTape);
        machine2->setCurrentPosition(machine1->getCurrentPosition());
        machine2->run(outputFileName);
    } else {
        machine3->setTape(intermediateTape);
        machine3->setCurrentPosition(machine1->getCurrentPosition());
        machine3->run(outputFileName);
    }
}

/**
 * @brief Default constructor for ConditionalCompositionTuringMachine.
 */
ConditionalCompositionTuringMachine::ConditionalCompositionTuringMachine() {
    // Implementation for default constructor
}

/**
 * @brief Constructor that initializes the ConditionalCompositionTuringMachine with an input stream.
 *
 * This constructor uses the given input stream to initialize the Turing machine by parsing
 * the machine's configuration.
 *
 * @param inputStream The input stream to read configuration data from.
 */
ConditionalCompositionTuringMachine::ConditionalCompositionTuringMachine(std::istream& inputStream) {
    init(inputStream);
}

/**
 * @file CompositionTuringMachine.cpp
 * @brief Implementation of the CompositionTuringMachine class.
 *
 * This file contains the implementation of the CompositionTuringMachine class, including methods to initialize
 * and run the composed machines.
 */

#include "CompositionTuringMachine.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>
#include "TuringMachine.h"
#include "../parsers/CompositionParser.h"

#include "CompositionTuringMachine.h"
#include <fstream>
/**
 * @brief Default constructor for CompositionTuringMachine.
 *
 * Constructs a CompositionTuringMachine without initializing its member machines.
 */
CompositionTuringMachine::CompositionTuringMachine() {
    // Empty constructor
}

/**
 * @brief Constructor that initializes the CompositionTuringMachine with an input stream.
 *
 * This constructor uses the given input stream to initialize the Turing machine by parsing
 * the machine's configuration through a CompositionMachineParser.
 *
 * @param inputStream The input stream to read configuration data from.
 */
CompositionTuringMachine::CompositionTuringMachine(std::istream& inputStream) {
    init(inputStream);
}

/**
 * @brief Initializes the Turing machine with input data from an input stream.
 *
 * Uses a CompositionMachineParser to parse the configuration of two Turing machines that form
 * the composition. This method sets up the first machine with the parsed tape and initializes
 * its position.
 *
 * @param inputStream The input stream to read data from.
 */
void CompositionTuringMachine::init(std::istream& inputStream) {
    CompositionMachineParser parser(inputStream);
    parser.parse();
    machine1 = parser.getFirstMachine();
    machine2 = parser.getSecondMachine();
    machine1->setTape(parser.getTape());
    machine1->setCurrentPosition(1);
}

/**
 * @brief Runs the Composition Turing machine and outputs the result to a file.
 *
 * Executes the first machine (machine1) and, upon its completion, runs the second machine (machine2)
 * with the tape state resulting from machine1. The output is written to the specified file.
 *
 * @param outputFileName Name of the file to write the output to.
 */
void CompositionTuringMachine::run(const std::string &outputFileName) {
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

/**
 * @brief Sets the Turing machines to be used in the composition.
 *
 * Assigns the provided Turing machines as the first and second machines in the composition.
 *
 * @param m1 Unique pointer to the first RegularTuringMachine.
 * @param m2 Unique pointer to the second RegularTuringMachine.
 */
void CompositionTuringMachine::setMachines(std::unique_ptr<RegularTuringMachine> m1, std::unique_ptr<RegularTuringMachine> m2) {
    machine1 = std::move(m1);
    machine2 = std::move(m2);
}

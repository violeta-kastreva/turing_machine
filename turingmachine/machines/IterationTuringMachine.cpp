/**
 * @file IterationLoopTuringMachine.cpp
 * @brief Implementation of the IterationLoopTuringMachine class.
 *
 * This file contains the implementation of the IterationLoopTuringMachine class, including constructors,
 * initialization, and the logic for running the iteration loop Turing machine.
 */
#include <filesystem>
#include "IterationTuringMachine.h"
#include "TuringMachine.h"
#include "../parsers/IterationParser.h"
/**
 * @brief Constructor that initializes the IterationLoopTuringMachine with an input stream.
 *
 * This constructor uses the given input stream to initialize the Turing machine by parsing
 * the machine's configuration.
 *
 * @param inputStream The input stream to read configuration data from.
 */
IterationLoopTuringMachine::IterationLoopTuringMachine(std::istream& inputStream) {
    init(inputStream);
}

/**
 * @brief Default constructor for IterationLoopTuringMachine.
 *
 * Constructs an IterationLoopTuringMachine without immediately initializing it.
 */
IterationLoopTuringMachine::IterationLoopTuringMachine() {
    // Implementation for default constructor
}

/**
 * @brief Initializes the Turing machine with input data from an input stream.
 *
 * Uses an IterationLoopMachineParser to parse the configuration of the Turing machine,
 * including the loop machine, post-loop machine, and the loop condition symbol.
 *
 * @param inputStream The input stream to read data from.
 */
void IterationLoopTuringMachine::init(std::istream& inputStream) {
    IterationLoopMachineParser parser(inputStream);
    parser.parse();

    loopMachine = parser.getLoopMachine();
    postLoopMachine = parser.getPostLoopMachine();
    loopConditionSymbol = parser.getLoopConditionSymbol();
}

/**
 * @brief Runs the Turing machine and outputs the result to a file.
 *
 * Executes the loop machine iteratively until the loop condition is not met, at which point
 * the post-loop machine is executed. The output is written to the specified file.
 *
 * @param outputFileName Name of the file to write the output to.
 */
void IterationLoopTuringMachine::run(const std::string &outputFileName) {
    char lastSymbol;
    std::string initialState = loopMachine->getCurrentState();
    do {
        loopMachine->setCurrentState(initialState);
        loopMachine->run(outputFileName);

        lastSymbol = loopMachine->getTape()[loopMachine->getCurrentPosition()];

        if (lastSymbol == loopConditionSymbol) {
            postLoopMachine->setTape(loopMachine->getTape());
            postLoopMachine->setCurrentPosition(loopMachine->getCurrentPosition());
            postLoopMachine->run(outputFileName);
        }
    } while (lastSymbol == loopConditionSymbol);
}
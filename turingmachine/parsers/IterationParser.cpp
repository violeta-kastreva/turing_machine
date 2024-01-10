/**
 * @file IterationLoopMachineParser.cpp
 * @brief Implementation of the IterationLoopMachineParser class.
 *
 * This file contains the implementation of the IterationLoopMachineParser class, including the logic
 * for parsing the configuration of Iteration Loop Turing Machines.
 */
#include <limits>
#include "IterationParser.h"
#include "RegularParser.h"

/**
 * @brief Parses the configuration for an Iteration Loop Turing Machine.
 *
 * Parses two Regular Turing Machines and a loop condition symbol from the input stream.
 * The first machine is the loop machine, which will run iteratively based on the loop condition.
 * The second machine is the post-loop machine, which will run after the loop machine under certain conditions.
 * This method sets the initial state and tape for the loop machine from the post-loop machine's configuration.
 */
void IterationLoopMachineParser::parse() {
    RegularMachineParser loopMachineParser(inputStream);
    loopMachine = loopMachineParser.parse();

    RegularMachineParser postLoopMachineParser(inputStream);
    postLoopMachine = postLoopMachineParser.parse();

    // Parse the loop condition symbol
    inputStream >> std::noskipws >> loopConditionSymbol;
    loopMachine->setTape(postLoopMachine->getTape());
    loopMachine->setCurrentPosition(1);
}

/**
 * @brief Retrieves the parsed loop Turing Machine.
 *
 * @return A unique pointer to the Regular Turing Machine that is designated as the loop machine.
 */
std::unique_ptr<RegularTuringMachine> IterationLoopMachineParser::getLoopMachine() {
    return std::move(loopMachine);
}

/**
 * @brief Retrieves the parsed post-loop Turing Machine.
 *
 * @return A unique pointer to the Regular Turing Machine that is designated as the post-loop machine.
 */
std::unique_ptr<RegularTuringMachine> IterationLoopMachineParser::getPostLoopMachine() {
    return std::move(postLoopMachine);
}

/**
 * @brief Retrieves the loop condition symbol.
 *
 * @return The character symbol that dictates the looping condition.
 */
char IterationLoopMachineParser::getLoopConditionSymbol() {
    return loopConditionSymbol;
}

/**
 * @brief Retrieves the tape data for the Iteration Loop Turing Machine.
 *
 * @note This method may not be used if the tape is set during the parsing process.
 * @return The tape data as a string.
 */
std::string IterationLoopMachineParser::getTape() {
    return tape;
}

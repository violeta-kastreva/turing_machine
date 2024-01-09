/**
 * @file IterationLoopMachineParser.cpp
 * @brief Implementation of the IterationLoopMachineParser class.
 *
 * This file contains the implementation of the IterationLoopMachineParser class, including the logic
 * for parsing the configuration of Iteration Loop Turing Machines.
 */
#include <limits>
#include "iterationparser.h"
#include "regularparser.h"

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

std::unique_ptr<RegularTuringMachine> IterationLoopMachineParser::getLoopMachine() {
    return std::move(loopMachine);
}

std::unique_ptr<RegularTuringMachine> IterationLoopMachineParser::getPostLoopMachine() {
    return std::move(postLoopMachine);
}

char IterationLoopMachineParser::getLoopConditionSymbol() {
    return loopConditionSymbol;
}

std::string IterationLoopMachineParser::getTape() {
    return tape;
}

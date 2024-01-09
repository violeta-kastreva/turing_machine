/**
 * @file ConditionalCompositionMachineParser.cpp
 * @brief Implementation of the ConditionalCompositionMachineParser class.
 *
 * This file contains the implementation of the ConditionalCompositionMachineParser class, including methods to parse
 * the configuration for Conditional Composition Turing Machines.
 */
#include <memory>
#include <limits>
#include "ConditionalParser.h"
#include "../machines/RegularTuringMachine.h"
#include "ConditionalParser.h"
#include "RegularParser.h"

void ConditionalCompositionMachineParser::parse() {
    RegularMachineParser machine1Parser(inputStream);
    machine1 = machine1Parser.parse();
    inputStream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    RegularMachineParser machine2Parser(inputStream);
    machine2 = machine2Parser.parse();
    inputStream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    RegularMachineParser machine3Parser(inputStream);
    machine3 = machine3Parser.parse();

    // Parse the number of conditional symbols
    int numConditionalSymbols;
    inputStream >> numConditionalSymbols;
    char symbol;
    for (int i = 0; i < numConditionalSymbols; ++i) {
        inputStream >> std::noskipws >> symbol;
        conditionalSymbols.insert(symbol);
    }
    inputStream.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Skip to the next line

    // Parse the tape
    parseTape(tape);
}

std::unique_ptr<RegularTuringMachine> ConditionalCompositionMachineParser::getFirstMachine() {
    return std::move(machine1);
}

std::unique_ptr<RegularTuringMachine> ConditionalCompositionMachineParser::getSecondMachine() {
    return std::move(machine2);
}

std::unique_ptr<RegularTuringMachine> ConditionalCompositionMachineParser::getThirdMachine() {
    return std::move(machine3);
}

const std::set<char>& ConditionalCompositionMachineParser::getConditionalSymbols() {
    return conditionalSymbols;
}
std::string ConditionalCompositionMachineParser::getTape() {
    return tape;
}
#include "baseparser.h"

#include "compositionparser.h"
#include "regularparser.h"

void CompositionMachineParser::parse() {
    RegularMachineParser machine1Parser(inputStream);
    machine1 = machine1Parser.parse();

    RegularMachineParser machine2Parser(inputStream);
    machine2 = machine2Parser.parse();

    // Parse the tape
    this->tape = machine2->getTape();
}

std::unique_ptr<RegularTuringMachine> CompositionMachineParser::getFirstMachine() {
    return std::move(machine1);
}

std::unique_ptr<RegularTuringMachine> CompositionMachineParser::getSecondMachine() {
    return std::move(machine2);
}

std::string CompositionMachineParser::getTape() {
    return tape;
}

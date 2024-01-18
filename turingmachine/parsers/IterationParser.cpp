#include <limits>
#include "IterationParser.h"
#include "RegularParser.h"

void IterationLoopMachineParser::parse() {
    RegularMachineParser loopMachineParser(inputStream);
    loopMachine = loopMachineParser.parse();

    RegularMachineParser postLoopMachineParser(inputStream);
    postLoopMachine = postLoopMachineParser.parse();

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

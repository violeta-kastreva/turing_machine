#include <filesystem>
#include "IterationTuringMachine.h"
#include "TuringMachine.h"
#include "../parsers/IterationParser.h"

IterationLoopTuringMachine::IterationLoopTuringMachine(std::istream& inputStream) {
    init(inputStream);
}

IterationLoopTuringMachine::IterationLoopTuringMachine() {
    // Implementation for default constructor
}

void IterationLoopTuringMachine::init(std::istream& inputStream) {
    IterationLoopMachineParser parser(inputStream);
    parser.parse();

    loopMachine = parser.getLoopMachine();
    postLoopMachine = parser.getPostLoopMachine();
    loopConditionSymbol = parser.getLoopConditionSymbol();
}

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
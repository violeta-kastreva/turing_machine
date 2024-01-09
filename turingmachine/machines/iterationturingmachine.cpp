#include <filesystem>
#include "iterationturingmachine.h"
#include "turingmachine.h"
#include "../parsers/iterationparser.h"

IterationLoopTuringMachine::IterationLoopTuringMachine(std::istream& inputStream) {
    init(inputStream);
}

IterationLoopTuringMachine::IterationLoopTuringMachine() {
}


void IterationLoopTuringMachine::init(std::istream& inputStream) {
    IterationLoopMachineParser parser(inputStream);
    parser.parse();

    loopMachine = parser.getLoopMachine();
    postLoopMachine = parser.getPostLoopMachine();
    loopConditionSymbol = parser.getLoopConditionSymbol();



    // The postLoopMachine's initial tape state is not set here; it will be set in the run method
}

void IterationLoopTuringMachine::run(const std::string &outputFileName) {
    char lastSymbol;
    std::string initialState = loopMachine->getCurrentState();
    do {
        // Run the loop machine
        loopMachine->setCurrentState(initialState);
        loopMachine->run(outputFileName);

        lastSymbol = loopMachine->getTape()[loopMachine->getCurrentPosition()];

        // Run the post-loop machine if the last symbol matches the condition
        if (lastSymbol == loopConditionSymbol) {
            postLoopMachine->setTape(loopMachine->getTape()); // Set the current tape from loopMachine to postLoopMachine
            postLoopMachine->setCurrentPosition(loopMachine->getCurrentPosition()); // Reset position
            postLoopMachine->run(outputFileName); // Run post-loop machine
        }
    } while (lastSymbol == loopConditionSymbol);
}

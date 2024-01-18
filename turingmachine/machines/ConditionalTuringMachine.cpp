#include <memory>
#include <iostream>
#include <fstream>
#include <filesystem>
#include "ConditionalTuringMachine.h"
#include "../parsers/ConditionalParser.h"


void ConditionalCompositionTuringMachine::init(std::istream& inputStream) {
    ConditionalCompositionMachineParser parser(inputStream);
    parser.parse();

    machine1 = parser.getFirstMachine();
    machine2 = parser.getSecondMachine();
    machine3 = parser.getThirdMachine();
    machine1->setTape(machine3->getTape());
    machine1->setCurrentPosition(1);
}

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


ConditionalCompositionTuringMachine::ConditionalCompositionTuringMachine() {
}

ConditionalCompositionTuringMachine::ConditionalCompositionTuringMachine(std::istream& inputStream) {
    init(inputStream);
}

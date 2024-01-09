//
// Created by Vily on 8.1.2024 г..
//

#ifndef TURING_MACHINE_ITERATIONPARSER_H
#define TURING_MACHINE_ITERATIONPARSER_H


#include <memory>
#include "baseparser.h"

class IterationLoopMachineParser : public BaseParser {
public:
    using BaseParser::BaseParser;  // Inherit the constructor

    void parse();

    std::unique_ptr<RegularTuringMachine> getLoopMachine();
    std::unique_ptr<RegularTuringMachine> getPostLoopMachine();
    char getLoopConditionSymbol();
    std::string getTape();

private:
    std::unique_ptr<RegularTuringMachine> loopMachine;
    std::unique_ptr<RegularTuringMachine> postLoopMachine;
    char loopConditionSymbol;
    std::string tape;
};

#endif //TURING_MACHINE_ITERATIONPARSER_H

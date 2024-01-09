//
// Created by Vily on 8.1.2024 г..
//

#ifndef TURING_MACHINE_COMPOSITIONPARSER_H
#define TURING_MACHINE_COMPOSITIONPARSER_H

#include <memory>
#include "baseparser.h"
#include "../machines/compositionturingmachine.h"


class CompositionMachineParser : public BaseParser {
public:
    using BaseParser::BaseParser;  // Inherit the constructor

    void parse();

    std::unique_ptr<RegularTuringMachine> getFirstMachine();
    std::unique_ptr<RegularTuringMachine> getSecondMachine();
    std::string getTape();

private:
    std::unique_ptr<RegularTuringMachine> machine1;
    std::unique_ptr<RegularTuringMachine> machine2;
    std::string tape;
};

#endif //TURING_MACHINE_COMPOSITIONPARSER_H

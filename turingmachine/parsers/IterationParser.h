/**
 * @file IterationLoopMachineParser.h
 * @brief Parser class for Iteration Loop Turing Machines.
 *
 * This file contains the definition of the IterationLoopMachineParser class, which extends BaseParser
 * to specifically parse configurations for Iteration Loop Turing Machines.
 */
#ifndef TURING_MACHINE_ITERATIONPARSER_H
#define TURING_MACHINE_ITERATIONPARSER_H


#include <memory>
#include "BaseParser.h"
/**
 * @class IterationLoopMachineParser
 * @brief Parser for Iteration Loop Turing Machines.
 *
 * Inherits from BaseParser and provides functionality to parse the configuration for
 * Iteration Loop Turing Machines, which consist of a loop machine and a post-loop machine,
 * executing based on a loop condition symbol.
 */
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

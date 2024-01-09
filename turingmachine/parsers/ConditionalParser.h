/**
 * @file ConditionalCompositionMachineParser.h
 * @brief Parser class for Conditional Composition Turing Machines.
 *
 * This file contains the definition of the ConditionalCompositionMachineParser class, which is used to parse the configuration
 * of a Conditional Composition Turing Machine from an input stream.
 */
#ifndef TURING_MACHINE_CONDITIONALPARSER_H
#define TURING_MACHINE_CONDITIONALPARSER_H

#include <memory>
#include "BaseParser.h"
/**
 * @class ConditionalCompositionMachineParser
 * @brief Parser for Conditional Composition Turing Machines.
 *
 * ConditionalCompositionMachineParser extends BaseParser to parse configurations specific to Conditional
 * Composition Turing Machines. It parses three Turing machines and their conditional execution symbols.
 */
class ConditionalCompositionMachineParser : public BaseParser {
public:
    using BaseParser::BaseParser; // Inherit the constructor

    void parse();

    std::unique_ptr<RegularTuringMachine> getFirstMachine();
    std::unique_ptr<RegularTuringMachine> getSecondMachine();
    std::unique_ptr<RegularTuringMachine> getThirdMachine();
    const std::set<char>& getConditionalSymbols();
    std::string getTape();

private:
    std::unique_ptr<RegularTuringMachine> machine1;
    std::unique_ptr<RegularTuringMachine> machine2;
    std::unique_ptr<RegularTuringMachine> machine3;
    std::set<char> conditionalSymbols;
    std::string tape;
};

#endif //TURING_MACHINE_CONDITIONALPARSER_H

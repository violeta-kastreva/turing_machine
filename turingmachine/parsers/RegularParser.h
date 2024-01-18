/**
 * @file RegularMachineParser.h
 * @brief Parser class for Regular Turing Machines.
 *
 * This file contains the definition of the RegularMachineParser class, which is used to parse the configuration
 * of a Regular Turing Machine from an input stream.
 */
#ifndef TURING_MACHINE_REGULARPARSER_H
#define TURING_MACHINE_REGULARPARSER_H


#include "BaseParser.h"
#include <istream>
#include <memory>
#include "../machines/RegularTuringMachine.h"

/**
 * @class RegularMachineParser
 * @brief Parser for Regular Turing Machines.
 *
 * RegularMachineParser extends BaseParser to provide functionalities specific to parsing Regular Turing Machines.
 * It parses the configuration file and constructs a RegularTuringMachine instance.
 */
class RegularMachineParser : public BaseParser {
public:
    using BaseParser::BaseParser;

    std::unique_ptr<RegularTuringMachine> parse();

private:
    std::string initialState;
    int initialTapePosition;
};


#endif //TURING_MACHINE_REGULARPARSER_H

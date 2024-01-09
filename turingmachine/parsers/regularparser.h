//
// Created by Vily on 5.1.2024 г..
//

#ifndef TURING_MACHINE_REGULARPARSER_H
#define TURING_MACHINE_REGULARPARSER_H


#include "BaseParser.h"
#include <istream>
#include <memory>
#include "../machines/regularturingmachine.h"

class RegularMachineParser : public BaseParser {
public:
    using BaseParser::BaseParser;  // Inherit the constructor

    // Parses the configuration file and returns a configured RegularTuringMachine.
    std::unique_ptr<RegularTuringMachine> parse();
    // Getter methods

private:
    std::string initialState;
    int initialTapePosition;
};


#endif //TURING_MACHINE_REGULARPARSER_H

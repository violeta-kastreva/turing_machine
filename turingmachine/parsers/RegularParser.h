#ifndef TURING_MACHINE_REGULARPARSER_H
#define TURING_MACHINE_REGULARPARSER_H


#include "BaseParser.h"
#include <istream>
#include <memory>
#include "../machines/RegularTuringMachine.h"

class RegularMachineParser : public BaseParser {
public:
    using BaseParser::BaseParser;

    std::unique_ptr<RegularTuringMachine> parse();

private:
    std::string initialState;
    int initialTapePosition;
};


#endif //TURING_MACHINE_REGULARPARSER_H

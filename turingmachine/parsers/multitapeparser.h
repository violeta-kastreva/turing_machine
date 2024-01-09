#pragma once
#ifndef TURING_MACHINE_MULTITAPEPARSER_H
#define TURING_MACHINE_MULTITAPEPARSER_H


#include "baseparser.h"
#include "../machines/multitapeturingmachine.h"
#include "BaseParser.h"
#include <vector>
#include <string>
#include <memory>

class MultiTapeMachineParser : public BaseParser {
public:
    explicit MultiTapeMachineParser(std::istream& input);

    // Parses the configuration file and returns a configured MultiTapeTuringMachine.
    std::unique_ptr<MultiTapeTuringMachine> parse();

private:
    std::unordered_map<MultiTapeTuringMachine::TransitionKey, MultiTapeTuringMachine::TransitionValue, MultiTapeTuringMachine::TransitionKeyHash> parseTransitions();
    std::vector<std::string> parseHaltingStates();
    std::vector<std::string> parseTapes();
    bool parseTransitionLine(const std::string& line, MultiTapeTuringMachine::TransitionKey& key, MultiTapeTuringMachine::TransitionValue& value);
};

#endif //TURING_MACHINE_MULTITAPEPARSER_H

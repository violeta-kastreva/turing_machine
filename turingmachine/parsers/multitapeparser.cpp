#include <limits>
#include <sstream>
#include "multitapeparser.h"
#include <sstream>
#include <string>
#include <vector>

MultiTapeMachineParser::MultiTapeMachineParser(std::istream& input) : BaseParser(input) {}

std::unique_ptr<MultiTapeTuringMachine> MultiTapeMachineParser::parse() {
    auto machine = std::make_unique<MultiTapeTuringMachine>();

    auto transitions = parseTransitions();
    machine->setTransitions(transitions);

    auto haltingStates = parseHaltingStates();
    machine->setHaltingStates(haltingStates);

    auto tapes = parseTapes();
    machine->setTapes(tapes);

    return machine;
}

std::unordered_map<MultiTapeTuringMachine::TransitionKey, MultiTapeTuringMachine::TransitionValue, MultiTapeTuringMachine::TransitionKeyHash> MultiTapeMachineParser::parseTransitions() {
    std::unordered_map<MultiTapeTuringMachine::TransitionKey, MultiTapeTuringMachine::TransitionValue, MultiTapeTuringMachine::TransitionKeyHash> transitions;
    std::string line;

    while (std::getline(inputStream, line) && !line.empty()) {
        MultiTapeTuringMachine::TransitionKey key;
        MultiTapeTuringMachine::TransitionValue value;

        if (parseTransitionLine(line, key, value)) {
            transitions[key] = value;
        }
    }

    return transitions;
}

std::vector<std::string> MultiTapeMachineParser::parseHaltingStates() {
    std::vector<std::string> haltingStates;
    std::string line;
    std::getline(inputStream, line); // Read the count of halting states

    int count = std::stoi(line);
    for (int i = 0; i < count; ++i) {
        std::getline(inputStream, line);
        haltingStates.push_back(line);
    }

    return haltingStates;
}

std::vector<std::string> MultiTapeMachineParser::parseTapes() {
    std::vector<std::string> tapes;
    std::string line;

    while (std::getline(inputStream, line) && !line.empty()) {
        tapes.push_back(line);
    }

    return tapes;
}

bool MultiTapeMachineParser::parseTransitionLine(const std::string& line, MultiTapeTuringMachine::TransitionKey& key, MultiTapeTuringMachine::TransitionValue& value) {
    std::istringstream stream(line);
    char tempBracket;
    std::string temp;

    // Parse current symbol combination and state
    if (!(stream >> temp >> tempBracket && tempBracket == '{')) {
        return false;
    }
    key.currentSymbolCombination = temp;
    if (!std::getline(stream, key.currentState, '}')) {
        return false;
    }

    // Parse arrow and newSymbolCombination, newState
    if (!(stream >> temp) || temp != "->") {
        return false;
    }

    if (!(stream >> temp >> tempBracket && tempBracket == '{')) {
        return false;
    }
    value.newSymbolCombination = temp;
    if (!std::getline(stream, value.newState, '}')) {
        return false;
    }

    if (!(stream >> value.command)) {
        return false;
    }

    return true;
}

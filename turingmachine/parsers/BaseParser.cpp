#include <limits>
#include <sstream>
#include "BaseParser.h"

void BaseParser::parseTransitions(std::unordered_map<RegularTuringMachine::TransitionKey, RegularTuringMachine::TransitionValue, RegularTuringMachine::TransitionKeyHash>& transitions) {
    alphabet.insert(' ');
    alphabet.insert('>');
    std::string line;
    bool firstTransition = true;
    while (std::getline(inputStream, line)) {
        if (line.empty()) {
            continue;
        }

        RegularTuringMachine::TransitionKey key;
        RegularTuringMachine::TransitionValue value;

        if (!parseTransitionLine(line, key, value)) {
            break;
        }

        transitions[key] = value;

        states.insert(key.currentState);
        states.insert(value.newState);
        alphabet.insert(key.currentSymbol);
        alphabet.insert(value.newSymbol);

        if (firstTransition) {
            this->initialState = key.currentState;
            firstTransition = false;
        }
    }
}

void BaseParser::parseTape(std::string& tape) {
    std::getline(inputStream, tape);
    findInitialTapePosition(tape);
}

const std::string& BaseParser::getInitialState() const {
    return initialState;
}

int BaseParser::getInitialTapePosition() const {
    return 1;
}

void BaseParser::findInitialState(const std::string& line) {
    auto start = line.find('{');
    auto end = line.find('}');
    if (start != std::string::npos && end != std::string::npos) {
        this->initialState = line.substr(start + 1, end - start - 1);
    }
}

void BaseParser::findInitialTapePosition(const std::string& tape) {
    initialTapePosition = tape[1];
}

bool BaseParser::parseTransitionLine(const std::string& line, RegularTuringMachine::TransitionKey& key, RegularTuringMachine::TransitionValue& value) {
    std::istringstream stream(line);
    char arrow, tempBracket;

    if (!(stream >>  std::noskipws >> key.currentSymbol >> tempBracket && tempBracket == '{')) return false;
    std::getline(stream, key.currentState, '}');

    if (!(stream >> arrow >> arrow && arrow == '>')) return false;

    if (!(stream >>  std::noskipws >> value.newSymbol >> tempBracket && tempBracket == '{')) return false;
    std::getline(stream, value.newState, '}');

    if (!(stream >> value.command)) return false;

    return isValidCommand(value.command);
}


void BaseParser::parseHaltingStates(std::set<std::string>& haltingStates) {
    std::string line;
    while (std::getline(inputStream, line)) {
        if (!line.empty() && (line[0] == '>' || isupper(line[0]))) {
            inputStream.putback('\n');
            for (auto it = line.rbegin(); it != line.rend(); ++it) inputStream.putback(*it);
            break;
        }
        haltingStates.insert(line);
    }
}

const std::set<std::string>& BaseParser::getStates() const {
    return states;
}

const std::set<char>& BaseParser::getAlphabet() const {
    return alphabet;
}

bool BaseParser::isValidCommand(const char command) {
    return command == 'L' || command == 'R' || command == 'S';
}

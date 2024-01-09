//
// Created by Vily on 5.1.2024 г..
//

#ifndef TURING_MACHINE_BASEPARSER_H
#define TURING_MACHINE_BASEPARSER_H

#include <istream>
#include <unordered_map>
#include <set>
#include <string>
#include "../machines/regularturingmachine.h"

class BaseParser {
public:
    explicit BaseParser(std::istream& input) : inputStream(input){}

    virtual ~BaseParser() = default;

    void parseTransitions(std::unordered_map<RegularTuringMachine::TransitionKey, RegularTuringMachine::TransitionValue, RegularTuringMachine::TransitionKeyHash>& transitions);
    void parseHaltingStates(std::set<std::string>& haltingStates);
    void parseTape(std::string& tape);

    const std::set<std::string>& getStates() const;
    const std::set<char>& getAlphabet() const;
    const std::string& getInitialState() const;
    int getInitialTapePosition() const;
protected:
    std::istream& inputStream;
    std::set<std::string> states;  // Add this line
    std::set<char> alphabet;
    std::string initialState;  // Add this line
    int initialTapePosition;
private:
    bool isValidCommand(const char command);
    bool parseTransitionLine(const std::string& line, RegularTuringMachine::TransitionKey& key, RegularTuringMachine::TransitionValue& value);
    void findInitialState(const std::string& line);
    void findInitialTapePosition(const std::string& tape);};

#endif //TURING_MACHINE_BASEPARSER_H

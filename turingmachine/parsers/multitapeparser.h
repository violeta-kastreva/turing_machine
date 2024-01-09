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
    using BaseParser::BaseParser;

    MultiTapeMachineParser(std::istream &input);

    std::unique_ptr<MultiTapeTuringMachine> parse();

    const std::unordered_map<MultiTapeTuringMachine::TransitionKey, MultiTapeTuringMachine::TransitionValue, MultiTapeTuringMachine::TransitionKeyHash>& getTransitions() const;
    const std::set<std::string>& getHaltingStates() const;
    DoublyLinkedList<char> getCombinedTape() const;
    const std::vector<typename DoublyLinkedList<char>::Iterator>& getInitialTapePositions() const;

    const std::set<std::string> getAlphabetCombinations() const;

private:
    bool parseTransitionLine(const std::string& line, MultiTapeTuringMachine::TransitionKey& key, MultiTapeTuringMachine::TransitionValue& value);
    std::set<std::string> parseHaltingStates();
    std::string parseTapes();
    std::set<std::string> alphabetCombination;
    std::string combinedTape;
    std::set<std::string> haltingStates;
    std::unordered_map<MultiTapeTuringMachine::TransitionKey, MultiTapeTuringMachine::TransitionValue, MultiTapeTuringMachine::TransitionKeyHash> transitions;
    std::vector<typename DoublyLinkedList<char>::Iterator> initialTapePositions;

    //void initializeIterators(const std::string &combinedTape, const std::vector<std::string> &tapes);

    std::unordered_map<MultiTapeTuringMachine::TransitionKey, MultiTapeTuringMachine::TransitionValue, MultiTapeTuringMachine::TransitionKeyHash>
    parseTransitions();

    void initializeIterators(const DoublyLinkedList<char> &combinedTapeList, const std::vector<std::string> &tapes);

    DoublyLinkedList<char> getCombinedTape(const std::string &currTape) const;
};

#endif //TURING_MACHINE_MULTITAPEPARSER_H

#pragma once
#ifndef TURING_MACHINE_MULTITAPETURINGMACHINE_H
#define TURING_MACHINE_MULTITAPETURINGMACHINE_H

#include "RegularTuringMachine.h"
#include "TuringMachine.h"


#include "TuringMachine.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <set>

class MultiTapeTuringMachine : public TuringMachine {
public:
    MultiTapeTuringMachine();
    MultiTapeTuringMachine(std::istream& inputStream);
    virtual void init(std::istream& inputStream) override;
    virtual void run(const std::string& outputFileName) override;

    struct TransitionKey {
        std::string currentSymbolCombination;
        std::string currentState;
        bool operator==(const TransitionKey& other) const;
    };

    struct TransitionValue {
        std::string newSymbolCombination;
        std::string newState;
        std::string command;
    };

    struct TransitionKeyHash {
        std::size_t operator()(const TransitionKey& key) const;
    };

    void setTransitions(const std::unordered_map<TransitionKey, TransitionValue, TransitionKeyHash> &transitions);
    void setTape(const std::string &combinedTape);
    void setHaltingStates(const std::set<std::string> &haltingStates);
    void setInitialTapePositions(const std::vector<typename DoublyLinkedList<char>::Iterator>& positions);
    const std::set<std::string> &getStates() const;
    void setStates(const std::set<std::string> &states);
    const std::vector<DoublyLinkedList<char>::Iterator> &getTapeIterators() const;
    void setTapeIterators(const std::vector<DoublyLinkedList<char>::Iterator> &tapeIterators);
    const std::set<std::string> &getAlphabetCombination() const;
    void setAlphabetCombination(const std::set<std::string> &alphabet);
private:
    std::unordered_map<TransitionKey, TransitionValue, TransitionKeyHash> transitions;
    std::set<std::string> states;
    std::set<std::string> haltingStates;
    std::set<std::string> alphabetCombination;
    std::string currentState;
    DoublyLinkedList<char> tape;
    std::vector<typename DoublyLinkedList<char>::Iterator> tapeIterators;
    std::vector<typename DoublyLinkedList<char>::Iterator> initialTapePositions;

    void processTape(const std::string& tapeData);
    void outputTape(const std::string& outFile);
    bool isValidTape(const std::string& tape) const;
    bool isValidCommand(const std::string command);
    void outputTape(std::ofstream &outFile) const;
};

#endif //TURING_MACHINE_MULTITAPETURINGMACHINE_H

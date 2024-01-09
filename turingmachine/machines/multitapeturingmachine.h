#pragma once
#ifndef TURING_MACHINE_MULTITAPETURINGMACHINE_H
#define TURING_MACHINE_MULTITAPETURINGMACHINE_H

#include "regularturingmachine.h"
#include "turingmachine.h"


#include "TuringMachine.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <set>

class MultiTapeTuringMachine : public TuringMachine {
public:
    MultiTapeTuringMachine();
    MultiTapeTuringMachine(const std::string& file);
    void init(std::istream& inputStream) override;
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

    void setTransitions(const std::unordered_map<TransitionKey, TransitionValue, TransitionKeyHash>& transitions);
    void setHaltingStates(const std::vector<std::string>& haltingStates);
    void setTapes(const std::vector<std::string>& tapes);

private:
    std::unordered_map<TransitionKey, TransitionValue, TransitionKeyHash> transitions;
    std::set<std::string> haltingStates;
    std::set<std::string> states;
    std::set<char> alphabet;
    std::vector<std::string> tapes;
    std::vector<int> currentPositions;
    std::string currentState;

    void processTape(const std::string& tapeData);
    bool isValidTape(const std::string& tape) const;
    static bool isValidCommand(const char command);
};

#endif //TURING_MACHINE_MULTITAPETURINGMACHINE_H

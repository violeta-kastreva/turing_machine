/**
 * @file MultiTapeMachineParser.h
 * @brief Parser class for Multi-Tape Turing Machines (Under Implementation).
 *
 * This file contains the definition of the MultiTapeMachineParser class. It is intended
 * to parse configurations for Multi-Tape Turing Machines. The implementation of this class
 * is still in progress and should not be used or looked at until it is complete.
 */
#pragma once
#ifndef TURING_MACHINE_MULTITAPETURINGMACHINE_H
#define TURING_MACHINE_MULTITAPETURINGMACHINE_H

#include "../machines/RegularTuringMachine.h"
#include "../machines/TuringMachine.h"


#include "../machines/TuringMachine.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <set>


/**
 * @class MultiTapeMachineParser
 * @brief Parser for Multi-Tape Turing Machines (Under Implementation).
 *
 * Inherits from BaseParser and provides functionality to parse the configuration for
 * Multi-Tape Turing Machines. This class is currently under implementation and should not be
 * used until the implementation is complete.
 */
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

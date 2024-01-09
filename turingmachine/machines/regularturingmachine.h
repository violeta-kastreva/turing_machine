#pragma once
#ifndef TURING_MACHINE_REGULARTURINGMACHINE_H
#define TURING_MACHINE_REGULARTURINGMACHINE_H

#include <unordered_map>
#include <string>
#include <set>
#include "turingmachine.h"
#include "../tape/doublylinkedlist.hpp"

/**
 * @class RegularTuringMachine
 * @brief Represents a standard Turing machine with a doubly linked list as the tape.
 *
 * This class extends the TuringMachine class, implementing the functionality for a regular Turing machine.
 * It uses a doubly linked list to represent the tape, allowing for efficient operations at both ends.
 */
class RegularTuringMachine : public TuringMachine {
public:
    RegularTuringMachine();
    RegularTuringMachine(const std::string& fileName);

    virtual void init(std::istream& inputStream) override;
    virtual void run(const std::string& outputFileName) override;
    std::string getTape();
    void setTape(const std::string& tape);
    void setCurrentState(const std::string& state);


    struct TransitionKey {
        char currentSymbol;
        std::string currentState;
        bool operator==(const TransitionKey& other) const;
    };

    struct TransitionValue {
        char newSymbol;
        std::string newState;
        char command;
    };

    struct TransitionKeyHash {
        std::size_t operator()(const TransitionKey& key) const;
    };

    void setTransitions(const std::unordered_map<TransitionKey, TransitionValue, TransitionKeyHash> &transitions);

    void setHaltingStates(const std::set<std::string> &haltingStates);

    void setCurrentPosition(int position);

    int getCurrentPosition();

    std::string getCurrentState();

    void setStates(const std::set<std::string> &states);

    void setAlphabet(const std::set<char> &alphabet);

private:

    std::set<std::string> states;
    std::set<std::string> haltingStates;
    std::unordered_map<TransitionKey, TransitionValue, TransitionKeyHash> transitions;
    std::set<char> alphabet;

    std::string currentState;
    DoublyLinkedList<char> tape;
    typename DoublyLinkedList<char>::Iterator currentPosition;

    void outputTape(const std::string& outFile);
    bool isValidTape(const std::string& tape);
    static bool isValidCommand(const char command);
    void processTape(const std::string& tapeData);

    void setInitialTapePosition(int position);

};

#endif // TURING_MACHINE_REGULARTURINGMACHINE_H

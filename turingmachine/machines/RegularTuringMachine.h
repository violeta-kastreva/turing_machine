#pragma once
#ifndef TURING_MACHINE_REGULARTURINGMACHINE_H
#define TURING_MACHINE_REGULARTURINGMACHINE_H

#include <unordered_map>
#include <string>
#include <set>
#include "TuringMachine.h"
#include "../tape/DoublyLinkedList.h"

class RegularTuringMachine : public TuringMachine {
public:
    // Constructors
    RegularTuringMachine();
    RegularTuringMachine(const std::string& fileName);

    // Overridden methods from TuringMachine
    virtual void init(std::istream& inputStream) override;
    virtual void run(const std::string& outputFileName) override;

    // Additional public methods
    std::string getTape();
    void setTape(const std::string& tape);
    void setCurrentState(const std::string& state);

    void setHaltingStates(const std::set<std::string> &haltingStates);

    void setCurrentPosition(int position);

    int getCurrentPosition();

    std::string getCurrentState();

    void setStates(const std::set<std::string> &states);

    void setAlphabet(const std::set<char> &alphabet);


    struct TransitionKey {
        char currentSymbol; ///< The current symbol on the tape.
        std::string currentState; ///< The current state of the Turing Machine.


        bool operator==(const TransitionKey& other) const;
    };


    struct TransitionValue {
        char newSymbol; ///< The symbol to write on the tape.
        std::string newState; ///< The new state to transition to.
        char command; ///< The movement command ('L' for left, 'R' for right, 'S' for stay).
    };


    struct TransitionKeyHash {

        std::size_t operator()(const TransitionKey& key) const;
    };

    void setTransitions(const std::unordered_map<TransitionKey, TransitionValue, TransitionKeyHash> &transitions);

private:
    // Private member variables
    std::set<std::string> states;
    std::set<std::string> haltingStates;
    std::unordered_map<TransitionKey, TransitionValue, TransitionKeyHash> transitions;
    std::set<char> alphabet;

    std::string currentState;
    DoublyLinkedList<char> tape;
    typename DoublyLinkedList<char>::Iterator currentPosition;

    // Private methods including error checks and utility functions
    void outputTape(const std::string& outFile);
    bool isValidTape(const std::string& tape);
    static bool isValidCommand(const char command);
    void processTape(const std::string& tapeData);

    // Additional private methods
    void setInitialTapePosition(int position);
};


#endif // TURING_MACHINE_REGULARTURINGMACHINE_H

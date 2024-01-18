#pragma once
#ifndef TURING_MACHINE_REGULARTURINGMACHINE_H
#define TURING_MACHINE_REGULARTURINGMACHINE_H

#include <unordered_map>
#include <string>
#include <set>
#include "TuringMachine.h"
#include "../tape/DoublyLinkedList.hpp"

/**
 * @class RegularTuringMachine
 * @brief Represents a standard Turing machine using a doubly linked list as the tape.
 *
 * Inherits from TuringMachine and implements the functionality for a regular Turing machine.
 * Utilizes a doubly linked list to represent the tape, enabling efficient operations.
 */
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

    /**
  * @struct TransitionKey
  * @brief Represents a key in the transition function of a Turing Machine.
  *
  * This structure is used as a key in the mapping of transitions, identifying the current symbol
  * and state of the Turing Machine.
  */
    struct TransitionKey {
        char currentSymbol; ///< The current symbol on the tape.
        std::string currentState; ///< The current state of the Turing Machine.

        /**
         * @brief Compares this key with another for equality.
         * @param other The other TransitionKey to compare with.
         * @return True if both keys are equal, false otherwise.
         */
        bool operator==(const TransitionKey& other) const;
    };

    /**
     * @struct TransitionValue
     * @brief Represents a value in the transition function of a Turing Machine.
     *
     * This structure defines the action of the Turing Machine for a given key (current state and symbol).
     * It specifies the new symbol to write, the new state to transition to, and the movement command.
     */
    struct TransitionValue {
        char newSymbol; ///< The symbol to write on the tape.
        std::string newState; ///< The new state to transition to.
        char command; ///< The movement command ('L' for left, 'R' for right, 'S' for stay).
    };

    /**
     * @struct TransitionKeyHash
     * @brief Hash function for TransitionKey, used in unordered_map.
     *
     * Provides a custom hash function for TransitionKey objects, allowing them to be used
     * effectively in an unordered_map.
     */
    struct TransitionKeyHash {
        /**
         * @brief Generates a hash value for a given TransitionKey.
         * @param key The TransitionKey to generate the hash for.
         * @return The generated hash value.
         */
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

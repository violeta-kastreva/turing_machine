#pragma once
#ifndef TURING_MACHINE_REGULARTURINGMACHINE_H
#define TURING_MACHINE_REGULARTURINGMACHINE_H

#include <unordered_map>
#include <cstring>
#include <string>
#include <set>
#include <vector>
#include <tuple>
#include "turingmachine.h"

/**
 * @class RegularTuringMachine
 * @brief The RegularTuringMachine class derives from the TuringMachine class and represents a regular Turing machine.
 *
 * This class provides functionality to initialize, run, and manipulate the state of a regular Turing machine.
 * It allows for processing input tapes, executing defined transitions, and managing the machine's current state.
 *
 * @note This class should be used when working with standard Turing machine operations.
 */
class RegularTuringMachine : public TuringMachine {
public:
    /**
     * @brief Default constructor for the RegularTuringMachine.
     */
    RegularTuringMachine();

    /**
     * @brief Constructor for the RegularTuringMachine that initializes the machine with a file.
     * @param fileName Name of the file containing the machine's initial configuration.
     */
    RegularTuringMachine(const std::string& fileName);

    /**
     * @brief Initializes the Turing machine with the specified file.
     * @param fileName Name of the file to initialize the machine with.
     */
    virtual void init(const std::string& fileName) override;

    /**
     * @brief Runs the Turing machine and outputs the result to a file.
     * @param outputFileName Name of the output file to store the machine's final tape state.
     */
    virtual void run(const std::string& outputFileName) override;

    /**
     * @brief Retrieves the current tape of the Turing machine.
     * @return Current tape as a string.
     */
    std::string getTape();

    /**
     * @brief Sets the tape of the Turing machine.
     * @param tape New tape to be set.
     */
    void setTape(const std::string& tape);

    /**
     * @brief Retrieves the current position of the Turing machine's head on the tape.
     * @return Current position as an integer.
     */
    int getCurrentPosition();

    /**
     * @brief Sets the current position of the Turing machine's head on the tape.
     * @param position New position to be set.
     */
    void setCurrentPosition(int position);

protected:
    /**
     * @struct TransitionKey
     * @brief Key for the transition map, containing the current symbol and state.
     */
    struct TransitionKey {
        char currentSymbol;
        std::string currentState;

        /**
         * @brief Compares two TransitionKey objects for equality.
         * @param other The other TransitionKey to compare with.
         * @return True if equal, otherwise false.
         */
        bool operator==(const TransitionKey& other) const;
    };

    /**
     * @struct TransitionValue
     * @brief Value for the transition map, containing the new symbol, new state, and command.
     */
    struct TransitionValue {
        char newSymbol;
        std::string newState;
        char command;
    };

    /**
     * @struct TransitionKeyHash
     * @brief Custom hash function for TransitionKey objects.
     */
    struct TransitionKeyHash {
        /**
         * @brief Generates a hash value for a given TransitionKey.
         * @param key The TransitionKey to hash.
         * @return Hash value as size_t.
         */
        std::size_t operator()(const TransitionKey& key) const;
    };

    std::set<std::string> states; ///< Set of all states of the Turing machine.
    std::set<std::string> haltingStates; ///< Set of halting states of the Turing machine.
    std::unordered_map<TransitionKey, TransitionValue, TransitionKeyHash> transitions; ///< Transition map of the Turing machine.
    std::set<char> alphabet; ///< Alphabet used by the Turing machine.

    std::string currentState; ///< Current state of the Turing machine.
    int currentPosition = 0; ///< Current position of the Turing machine head on the tape.
    std::string tape; ///< Current tape of the Turing machine.

    /**
     * @brief Outputs the current tape to a file.
     * @param outFile Name of the file to output the tape to.
     */
    void outputTape(const std::string& outFile);

    /**
     * @brief Checks if a given tape string is valid.
     * @param tape The tape string to validate.
     * @return True if valid, otherwise false.
     */
    bool isValidTape(const std::string& tape);

    /**
     * @brief Checks if a given command character is valid.
     * @param command The command character to validate.
     * @return True if valid, otherwise false.
     */
    static bool isValidCommand(const char command);

    /**
     * @brief Parses a single transition line from the configuration file.
     *
     * This method reads and validates a transition line, extracting the current symbol,
     * current state, new symbol, new state, and command. The extracted values are used
     * to populate the transitions map of the Turing Machine.
     *
     * @param line The transition line from the configuration file.
     * @param currentSymbol Reference to store the current symbol.
     * @param currentState Reference to store the current state.
     * @param newSymbol Reference to store the new symbol.
     * @param newState Reference to store the new state.
     * @param command Reference to store the command.
     * @return True if the transition is parsed successfully, false otherwise.
     */
    bool parseTransition(const std::string& line, char& currentSymbol, std::string& currentState,char& newSymbol,std::string& newState,char& command);

    /**
     * @brief Processes the initial tape data for the Turing Machine.
     *
     * Sets the machine's tape to the provided string and checks if it is valid
     * by ensuring all characters are part of the machine's alphabet.
     *
     * @param tapeData The initial tape data as a string.
     */
    void processTape(const std::string& tapeData);

    /**
     * @brief Reads and processes transition rules from a configuration file.
     *
     * Iterates through each line of the provided file stream, parsing and adding
     * the transitions to the Turing machine's transition map. Continues until
     * a non-transition line is encountered.
     *
     * @param file Reference to the ifstream of the configuration file.
     * @param line String to store the current line being processed.
     */
    void processTransitions(std::ifstream& file, std::string& line);
};

#endif //TURING_MACHINE_REGULARTURINGMACHINE_H

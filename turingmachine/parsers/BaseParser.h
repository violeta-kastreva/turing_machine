/**
 * @file BaseParser.h
 * @brief Base parser class for Turing Machine configurations.
 *
 * This file contains the definition of the BaseParser class, which is used to parse the configuration
 * of a Turing Machine from an input stream. It serves as a base class for more specific parsers.
 */
#ifndef TURING_MACHINE_BASEPARSER_H
#define TURING_MACHINE_BASEPARSER_H

#include <istream>
#include <unordered_map>
#include <set>
#include <string>
#include "../machines/RegularTuringMachine.h"

/**
 * @class BaseParser
 * @brief Base class for parsing Turing Machine configurations.
 *
 * BaseParser provides fundamental functionalities to parse transitions, halting states, and the tape of a Turing Machine.
 * It also extracts the initial state and tape position.
 */
class BaseParser {
public:
    /**
   * @brief Constructs a BaseParser with a given input stream.
   * @param input Reference to the input stream for parsing.
   */
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
    std::istream& inputStream; ///< Input stream from which the configuration is read.
    std::set<std::string> states; ///< Set of states found in the Turing Machine.
    std::set<char> alphabet; ///< Alphabet used by the Turing Machine.
    std::string initialState; ///< Initial state of the Turing Machine.
    int initialTapePosition; ///< Initial position on the Turing Machine's tape.

private:
    bool isValidCommand(const char command);
    bool parseTransitionLine(const std::string& line, RegularTuringMachine::TransitionKey& key, RegularTuringMachine::TransitionValue& value);
    void findInitialState(const std::string& line);
    void findInitialTapePosition(const std::string& tape);
};

#endif //TURING_MACHINE_BASEPARSER_H

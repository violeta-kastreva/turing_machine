#include <limits>
#include <sstream>
#include "BaseParser.h"

/**
 * @brief Parses transitions for a Turing Machine from the input stream.
 *
 * Reads lines from the input stream and parses each line as a transition for the Turing Machine.
 * The parsed transitions are stored in the provided transitions map. This method also updates
 * the alphabet and states of the Turing Machine based on the transitions.
 *
 * @param transitions Reference to a map where parsed transitions will be stored.
 */
void BaseParser::parseTransitions(std::unordered_map<RegularTuringMachine::TransitionKey, RegularTuringMachine::TransitionValue, RegularTuringMachine::TransitionKeyHash>& transitions) {
    alphabet.insert(' ');
    alphabet.insert('>');
    std::string line;
    bool firstTransition = true;
    while (std::getline(inputStream, line)) {
        if (line.empty()) {
            // Skip empty lines
            continue;
        }

        RegularTuringMachine::TransitionKey key;
        RegularTuringMachine::TransitionValue value;

        if (!parseTransitionLine(line, key, value)) {
            // If the line cannot be parsed as a transition, break the loop
            break;
        }

        // Add the parsed transition to the transitions map
        transitions[key] = value;

        // Add states and symbols to sets
        states.insert(key.currentState);
        states.insert(value.newState);
        alphabet.insert(key.currentSymbol);
        alphabet.insert(value.newSymbol);

        if (firstTransition) {
            // Set the initial state from the first valid transition
            this->initialState = key.currentState;
            firstTransition = false;
        }
    }
}

/**
 * @brief Parses the tape from the input stream and stores it in the provided string.
 *
 * Reads the tape data from the input stream and stores it in the given string.
 * Also determines the initial position on the tape.
 *
 * @param tape Reference to a string where the tape data will be stored.
 */
void BaseParser::parseTape(std::string& tape) {
    std::getline(inputStream, tape);
    findInitialTapePosition(tape);
}
/**
 * @brief Gets the initial state of the Turing Machine.
 *
 * Returns the initial state of the Turing Machine as determined during the parsing process.
 *
 * @return The initial state as a string.
 */
const std::string& BaseParser::getInitialState() const {
    return initialState;
}
/**
 * @brief Gets the initial tape position.
 *
 * Returns the initial position on the tape as determined during the parsing process.
 *
 * @return The initial tape position as an integer.
 */
int BaseParser::getInitialTapePosition() const {
    return 1;
}
/**
 * @brief Finds the initial state from a given line.
 *
 * Parses a line to find and set the initial state of the Turing Machine.
 *
 * @param line The line from which the initial state is to be extracted.
 */
void BaseParser::findInitialState(const std::string& line) {
    auto start = line.find('{');
    auto end = line.find('}');
    if (start != std::string::npos && end != std::string::npos) {
        this->initialState = line.substr(start + 1, end - start - 1);
    }
}
/**
 * @brief Finds the initial tape position from the tape data.
 *
 * Parses the tape data to determine the initial position on the tape.
 *
 * @param tape The tape data from which the initial position is to be extracted.
 */
void BaseParser::findInitialTapePosition(const std::string& tape) {
    initialTapePosition = tape[1];
}

/**
 * @brief Parses a single line to extract a Turing Machine transition.
 *
 * Extracts and returns a Turing Machine transition from a given line.
 * The transition includes the current symbol, current state, new symbol, new state, and command.
 *
 * @param line The line to parse.
 * @param key Reference to the TransitionKey to store the parsed current symbol and state.
 * @param value Reference to the TransitionValue to store the parsed new symbol, new state, and command.
 * @return True if the line was successfully parsed as a transition, false otherwise.
 */
bool BaseParser::parseTransitionLine(const std::string& line, RegularTuringMachine::TransitionKey& key, RegularTuringMachine::TransitionValue& value) {
    std::istringstream stream(line);
    char arrow, tempBracket;

    if (!(stream >>  std::noskipws >> key.currentSymbol >> tempBracket && tempBracket == '{')) return false;
    std::getline(stream, key.currentState, '}');

    if (!(stream >> arrow >> arrow && arrow == '>')) return false;

    if (!(stream >>  std::noskipws >> value.newSymbol >> tempBracket && tempBracket == '{')) return false;
    std::getline(stream, value.newState, '}');

    if (!(stream >> value.command)) return false;

    return isValidCommand(value.command);
}

/**
 * @brief Parses halting states for the Turing Machine from the input stream.
 *
 * Reads lines from the input stream and stores each line as a halting state.
 * Stops parsing when a line starts with '>' or an uppercase letter, indicating the end of halting states.
 *
 * @param haltingStates Reference to a set where parsed halting states will be stored.
 */
void BaseParser::parseHaltingStates(std::set<std::string>& haltingStates) {
    std::string line;
    while (std::getline(inputStream, line)) {
        if (!line.empty() && (line[0] == '>' || isupper(line[0]))) {
            inputStream.putback('\n');
            for (auto it = line.rbegin(); it != line.rend(); ++it) inputStream.putback(*it);
            break;
        }
        haltingStates.insert(line);
    }
}
/**
 * @brief Gets the set of states of the Turing Machine.
 *
 * Returns the set of states as determined during the parsing process.
 *
 * @return Set of states as strings.
 */
const std::set<std::string>& BaseParser::getStates() const {
    return states;
}
/**
 * @brief Gets the alphabet of the Turing Machine.
 *
 * Returns the set of symbols (alphabet) as determined during the parsing process.
 *
 * @return Set of characters representing the alphabet.
 */
const std::set<char>& BaseParser::getAlphabet() const {
    return alphabet;
}
/**
 * @brief Checks if a given command is valid.
 *
 * Validates if a character represents a valid command for a Turing Machine ('L', 'R', or 'S').
 *
 * @param command The command character to validate.
 * @return True if the command is valid, false otherwise.
 */
bool BaseParser::isValidCommand(const char command) {
    return command == 'L' || command == 'R' || command == 'S';
}

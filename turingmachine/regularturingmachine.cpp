#include "regularturingmachine.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>

/**
 * @brief Outputs the tape to a file.
 *
 * Writes the current state of the machine's tape to the specified output file.
 * This function is typically called after the machine reaches a halting state.
 *
 * @param outputFileName Name of the file where the tape will be written.
 */
void RegularTuringMachine::outputTape(const std::string &outputFileName){
    std::ofstream outFile(outputFileName, std::ios::out);

    if (outFile.is_open()) {
        outFile << tape;
        outFile.close();
        std::cout << "Tape successfully written to " << outputFileName << std::endl;
    } else {
        std::cerr << "Unable to open or create file: " << outputFileName << std::endl;
    }

}

/**
 * @brief Executes the Turing machine.
 *
 * Runs the machine using its current configuration and tape. It processes the tape
 * according to the defined transitions until it reaches a halting state. After
 * halting, it calls outputTape to write the final tape state to a file.
 *
 * @param outputFileName Name of the file to write the final tape state.
 */
void RegularTuringMachine::run(const std::string &outputFileName) {
    while (true) {
        if(haltingStates.find(currentState) != haltingStates.end()) break;

        if (currentPosition <= 0) {
            std::cerr << "Machine reached invalid position on the tape";

        } else if (currentPosition >= tape.length()) {
            tape += " ";
        }

        char currentSymbol = tape[currentPosition];
        TransitionKey key{currentSymbol, currentState};

        auto it = transitions.find(key);
        if (it == transitions.end()) {
            std::cerr << "Machine reached invalid state: " << currentSymbol << ",  " << currentState << std::endl;
            break;
        }

        TransitionValue transition = it->second;
        tape[currentPosition] = transition.newSymbol;
        currentState = transition.newState;

        if (transition.command == 'L') currentPosition--;
        else if (transition.command == 'R') currentPosition++;
    }

    outputTape(outputFileName);
}

/**
 * @brief Checks if a tape is valid based on the machine's alphabet.
 *
 * Validates that all characters in the input tape are part of the machine's
 * alphabet. It is a prerequisite for the tape to be processed.
 *
 * @param inputTape The tape string to be validated.
 * @return True if the tape only contains symbols from the machine's alphabet, false otherwise.
 */
bool RegularTuringMachine::isValidTape(const std::string& inputTape) {
    return std::all_of(inputTape.begin(), inputTape.end(), [this](char symbol) {
        return alphabet.find(symbol) != alphabet.end();
    });
}

/**
 * @brief Validates a command character.
 *
 * Checks if the provided command character is among the valid commands ('L', 'R', 'S').
 *
 * @param command The command character to be validated.
 * @return True if the command is valid, false otherwise.
 */
bool RegularTuringMachine::isValidCommand(const char command) {
    return command == 'L' || command == 'R' || command == 'S';
}

/**
 * @brief Parses a single transition line from the configuration file.
 *
 * Reads and validates a transition line, extracting the current symbol, current state,
 * new symbol, new state, and command. The extracted values are used to populate the
 * transitions map.
 *
 * @param line The transition line from the configuration file.
 * @param currentSymbol Reference to store the current symbol.
 * @param currentTransitionState Reference to store the current state.
 * @param newSymbol Reference to store the new symbol.
 * @param newState Reference to store the new state.
 * @param command Reference to store the command.
 * @return True if the transition is parsed successfully, false otherwise.
 */
bool RegularTuringMachine::parseTransition(const std::string& line, char& currentSymbol, std::string& currentTransitionState, char& newSymbol, std::string& newState, char& command) {
    std::istringstream stream(line);
    char arrow, tempBracket;

    if (stream >> std::noskipws >> currentSymbol >> tempBracket && tempBracket == '{' &&
        std::getline(stream, currentTransitionState, '}') &&
        stream >> arrow >> arrow &&
        stream >> std::noskipws >> newSymbol >> tempBracket && tempBracket == '{' &&
        std::getline(stream, newState, '}') &&
        stream >> command) {

        if (arrow != '>' || !isValidCommand(command)) {
            return false;
        }

        return true;
    }
    return false;
}

/**
 * @brief Processes the transition rules from the configuration file.
 *
 * Reads the transition rules line by line from the provided file stream, parses each
 * line, and adds the transitions to the machine's transition map.
 *
 * @param file Reference to the ifstream of the configuration file.
 * @param line String to store the current line being processed.
 */
void RegularTuringMachine::processTransitions(std::ifstream& file, std::string& line) {
    currentPosition = 1;
    alphabet.insert('>');
    haltingStates.insert("halt");
    bool firstTransition = true;
    while (std::getline(file, line) && !line.empty()) {
        char currentSymbol;
        std::string currentTransitionState, newState;
        char newSymbol, command;
        //! checking if the given row is a valid transition
        if (parseTransition(line, currentSymbol, currentTransitionState, newSymbol, newState, command)) {
            TransitionKey key{currentSymbol, currentTransitionState};
            TransitionValue value{newSymbol, newState, command};
            //! adding the transition
            transitions[key] = value;
            //! adding the states
            states.insert(currentTransitionState);
            states.insert(newState);
            //! adding the alphabet symbols
            alphabet.insert(currentSymbol);
            alphabet.insert(newSymbol);
            //! assuming the first given state (in the first transition) is the starting one, sets the currentState (the initial one)
            if (firstTransition) {
                currentState = currentTransitionState;
                firstTransition = false;
            }
        } else {
            //! No more transitions, break the loop
            break;
        }
    }
}

/**
 * @brief Processes the initial tape data.
 *
 * Sets the machine's tape to the provided string and validates it.
 *
 * @param tapeData The initial tape data.
 */
void RegularTuringMachine::processTape(const std::string& tapeData) {
    tape = tapeData;
    if (!isValidTape(tape)) {
        std::cerr << "Invalid tape: contains symbols not in the alphabet" << std::endl;
    }
}

/**
 * @brief Initializes the Turing machine from a configuration file.
 *
 * Reads and processes the transitions and initial tape data from the given file.
 * Sets up the machine for running.
 *
 * @param fileName The name of the file containing the machine's configuration.
 */
void RegularTuringMachine::init(const std::string &fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << fileName << std::endl;
        return;
    }

    // Skip the first line that specifies the type of the machine
    std::string line; //if is regular ->grymni
    std::getline(file, line);

    // Process transitions
    processTransitions(file, line);

    // Process the initial tape
    if(isValidTape(line)){
        processTape(line);
    }


    file.close();
}

/**
 * @brief Constructor that initializes the Turing machine with a configuration file.
 *
 * Creates a Turing machine instance and initializes it using the specified file.
 *
 * @param fileName Name of the file containing the machine's initial configuration.
 */
RegularTuringMachine::RegularTuringMachine(const std::string& fileName) {
    init(fileName);
}

/**
 * @brief Default constructor.
 *
 * Constructs a RegularTuringMachine object without initializing it with a file.
 * Suitable for scenarios where the machine is configured later.
 */
RegularTuringMachine::RegularTuringMachine() {
}

/**
 * @brief Getter for the current tape.
 *
 * @return The current tape of the machine as a string.
 */
std::string RegularTuringMachine::getTape() {
    return this->tape;
}

/**
 * @brief Setter for the tape.
 *
 * Sets the machine's tape to the specified string.
 *
 * @param tape The new tape to be set.
 */
void RegularTuringMachine::setTape(const std::string& tape){
    this->tape = tape;
}

/**
* Returns the read head
*/
int RegularTuringMachine::getCurrentPosition() {
    return this->currentPosition;
}

/**
 * @brief Setter for the position of the machine's head.
 *
 * Sets the position of the machine's head to the specified value.
 *
 * @param position The new position of the head on the tape.
 */
void RegularTuringMachine::setCurrentPosition(int position) {
    this->currentPosition = position;
}

/**
 * @brief Custom hash function for the TransitionKey struct.
 *
 * Provides a hash function for TransitionKey objects, enabling their use as keys in an unordered_map.
 *
 * @param key The TransitionKey object to hash.
 * @return The hash value.
 */
std::size_t RegularTuringMachine::TransitionKeyHash::operator()(const TransitionKey& key) const {
    return std::hash<std::string>()(key.currentState) ^ std::hash<char>()(key.currentSymbol);
}

/**
 * @brief Equality comparison for TransitionKey objects.
 *
 * Compares two TransitionKey objects for equality.
 *
 * @param other The TransitionKey object to compare with.
 * @return True if both objects are equal, false otherwise.
 */
bool RegularTuringMachine::TransitionKey::operator==(const TransitionKey& other) const {
    return currentSymbol == other.currentSymbol && currentState == other.currentState;
}
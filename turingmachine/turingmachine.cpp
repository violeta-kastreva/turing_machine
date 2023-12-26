#include "turingmachine.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>

/**
* Writing the modified tape into a specified file from the user (if the machine halts)
*/
void TuringMachine::outputTape(const std::string &outputFileName){
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
* Running the Turing Machine on the given input (tape and machine data)
*/
void TuringMachine::run(const std::string &outputFileName) {
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
* Checking if the tape consists of characters from the alphabet only (the alphabet of the machine)
*/
bool TuringMachine::isValidTape(const std::string& inputTape) {
    return std::all_of(inputTape.begin(), inputTape.end(), [this](char symbol) {
        return alphabet.find(symbol) != alphabet.end();
    });
}

/**
* Checking if the given command is valid (left, right, stay)
*/
bool TuringMachine::isValidCommand(const char command) {
    return command == 'L' || command == 'R' || command == 'S';
}

/**
* Parsing the given transition, modifies the given variables to that they be reused, returns true if parsed correctly
*/
bool TuringMachine::parseTransition(const std::string& line, char& currentSymbol, std::string& currentTransitionState, char& newSymbol, std::string& newState, char& command) {
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
* Iterating over each row until a non-transition one occurs
*/
void TuringMachine::processTransitions(std::ifstream& file, std::string& line) {
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
* Processing the tape input
*/
void TuringMachine::processTape(const std::string& tapeData) {
    tape = tapeData;
    if (!isValidTape(tape)) {
        std::cerr << "Invalid tape: contains symbols not in the alphabet" << std::endl;
    }
}

/**
* Initializes the machine, parsing the transitions and validating the tape
*/
void TuringMachine::init(const std::string &fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << fileName << std::endl;
        return;
    }

    // Skip the first line that specifies the type of the machine
    std::string line;
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
* Constructor of a Turing Machine by a given input file, calls the initializing method
*/
TuringMachine::TuringMachine(const std::string& fileName) {
    init(fileName);
}

/**
* Empty constructor for the Factory class
*/
TuringMachine::TuringMachine() {
}

/**
* Returns the current tape
*/
std::string TuringMachine::getTape() {
    return this->tape;
}

/**
* Modifies the current tape
*/
void TuringMachine::setTape(const std::string& tape){
    this->tape = tape;
}

/**
* Returns the read head
*/
int TuringMachine::getCurrentPosition() {
    return this->currentPosition;
}

/**
* Changes the position of the read head
*/
void TuringMachine::setCurrentPosition(int position) {
    this->currentPosition = position;
}

/**
* Custom hashing function for the transition map
*/
std::size_t TuringMachine::TransitionKeyHash::operator()(const TransitionKey& key) const {
    return std::hash<std::string>()(key.currentState) ^ std::hash<char>()(key.currentSymbol);
}

bool TuringMachine::TransitionKey::operator==(const TransitionKey& other) const {
    return currentSymbol == other.currentSymbol && currentState == other.currentState;
}
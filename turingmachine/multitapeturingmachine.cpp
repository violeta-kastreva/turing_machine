#include "MultiTapeTuringMachine.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>

/**
* Writing the modified tape into a specified file from the user (if the machine halts)
*/
void MultiTapeTuringMachine::outputTape(const std::string &outputFileName){
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
void MultiTapeTuringMachine::run(const std::string &outputFileName) {
//    while (true) {
//        if(haltingStates.find(currentState) != haltingStates.end()) break;
//
//        if (currentPosition <= 0) {
//            std::cerr << "Machine reached invalid position on the tape";
//
//        } else if (currentPosition >= tape.length()) {
//            tape += " ";
//        }
//
//        char currentSymbol = tape[currentPosition];
//        TransitionKey key{currentSymbol, currentState};
//
//        auto it = transitions.find(key);
//        if (it == transitions.end()) {
//            std::cerr << "Machine reached invalid state: " << currentSymbol << ",  " << currentState << std::endl;
//            break;
//        }
//
//        TransitionValue transition = it->second;
//        tape[currentPosition] = transition.newSymbol;
//        currentState = transition.newState;
//
//        if (transition.command == 'L') currentPosition--;
//        else if (transition.command == 'R') currentPosition++;
//    }
//
//    outputTape(outputFileName);
}

/**
* Checking if the tape consists of characters from the alphabet only (the alphabet of the machine)
*/
bool MultiTapeTuringMachine::isValidTape(const std::string& inputTape) {
    return std::all_of(inputTape.begin(), inputTape.end(), [this](char symbol) {
        return alphabet.find(symbol) != alphabet.end();
    });
}

/**
* Checking if the given command is valid (left, right, stay)
*/
bool MultiTapeTuringMachine::isValidCommand(const char command) {
    return command == 'L' || command == 'R' || command == 'S';
}

/**
* Parsing the given transition, modifies the given variables to that they be reused, returns true if parsed correctly
*/
bool MultiTapeTuringMachine::parseTransition(const std::string& line,
                                             std::string& currentSymbolCombination,
                                             std::string& currentTransitionState,
                                             std::string& newSymbolCombination,
                                             std::string& newState,
                                             std::string& commands) {
    std::istringstream stream(line);
    char arrow, tempBracket;

    // Read current symbols
    if (!(stream >> std::noskipws >> currentSymbolCombination >> tempBracket)) {
        return false;
    }
    int s = currentSymbolCombination.size();
    for(int i = 1; i < s; ++i){
        if(currentSymbolCombination[i] == '>') currentSymbolCombination = '#';
    }

    if (tempBracket != '{') {
        return false;
    }

    // Read current transition state
    if (!std::getline(stream, currentTransitionState, '}')) {
        return false;
    }

    // Read arrow
    if (!(stream >> arrow >> arrow) || arrow != '>') {
        return false;
    }

    // Read new symbols
    if (!(stream >> std::noskipws >> newSymbolCombination >> tempBracket)) {
        return false;
    }
    if (tempBracket != '{') {
        return false;
    }

    s = newSymbolCombination.size();
    for(int i = 1; i < s; ++i){
        if(newSymbolCombination[i] == '>') newSymbolCombination = '#';
    }

    // Read new state
    if (!std::getline(stream, newState, '}')) {
        return false;
    }

    // Read commands
    if (!(stream >> commands)) {
        return false;
    }

    return true; // Successfully parsed the transition
}


/**
* Iterating over each row until a non-transition one occurs
*/
void MultiTapeTuringMachine::processTransitions(std::ifstream& file, std::string& line) {
    currentPositions[0] = 1;
    alphabet.insert('>');
    haltingStates.insert("halt");
    bool firstTransition = true;
    while (std::getline(file, line) && !line.empty()) {
        //char currentSymbol;
        std::string currentSymbolCombination, currentTransitionState, newState, newSymbolCombination, command;
        //char command;
        //! checking if the given row is a valid transition
        if (parseTransition(line, currentSymbolCombination, currentTransitionState, newSymbolCombination, newState, command)) {
            TransitionKey key{currentSymbolCombination, currentTransitionState};
            TransitionValue value{newSymbolCombination, newState, command};
            //! adding the transition
            transitions[key] = value;
            //! adding the states
            states.insert(currentTransitionState);
            states.insert(newState);
            //! adding the alphabet symbols
            for (char letter : currentSymbolCombination){
                alphabet.insert(letter);
            }
            for (char letter : newSymbolCombination){
                alphabet.insert(letter);
            }
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
void MultiTapeTuringMachine::processTape(const std::string& tapeData) {
    std::stringstream ss(tapeData);
    std::string singleTape;
    std::string line;

    tape.clear(); // Clear the existing tape content

    while (std::getline(ss, line)) {
        if (!isValidTape(line)) {
            std::cerr << "Invalid tape: contains symbols not in the alphabet" << std::endl;
            return;
        }

        // Append this tape to the combined tape
        if (!tape.empty()) {
            line[0] = '#';
        }
        tape += line;
    }

    // Now, tape contains the combined content of all tapes, separated by '#'
}


/**
* Initializes the machine, parsing the transitions and validating the tape
*/
void MultiTapeTuringMachine::init(const std::string &fileName) {
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
* Constructor of a Turing Machine by a given input file, calls the initializing method
*/
MultiTapeTuringMachine::MultiTapeTuringMachine(const std::string& fileName) {
    init(fileName);
}

/**
* Empty constructor for the Factory class
*/
MultiTapeTuringMachine::MultiTapeTuringMachine() {
}

/**
* Returns the current tape
*/
std::string MultiTapeTuringMachine::getTape() {
    return this->tape;
}

/**
* Modifies the current tape
*/
void MultiTapeTuringMachine::setTape(const std::string& tape){
    this->tape = tape;
}

/**
* Returns the read head
*/
int MultiTapeTuringMachine::getCurrentPosition(int index) {
    return this->currentPositions[index];
}

/**
* Changes the position of the read head
*/
void MultiTapeTuringMachine::setCurrentPosition(int index, int position) {
    this->currentPositions[index] = position;
}

/**
* Custom hashing function for the transition map
*/
std::size_t MultiTapeTuringMachine::TransitionKeyHash::operator()(const TransitionKey& key) const {
    return std::hash<std::string>()(key.currentState) ^ std::hash<std::string>()(key.currentSymbolCombination);
}

bool MultiTapeTuringMachine::TransitionKey::operator==(const TransitionKey& other) const {
    return currentSymbolCombination == other.currentSymbolCombination && currentState == other.currentState;
}
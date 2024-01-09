#include "regularturingmachine.h"
#include "../parsers/regularparser.h"
#include <fstream>
#include <iostream>
#include <algorithm>

RegularTuringMachine::RegularTuringMachine() {
}

RegularTuringMachine::RegularTuringMachine(const std::string& fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << fileName << std::endl;
        return;
    }

    init(file);
}

bool RegularTuringMachine::isValidTape(const std::string& inputTape) {
    return std::all_of(inputTape.begin(), inputTape.end(), [this](char symbol) {
        return alphabet.find(symbol) != alphabet.end();
    });
}

void RegularTuringMachine::setTape(const std::string& tapeString){
    tape.free();
    for (char ch : tapeString) {
        tape.push_back(ch);
    }
    currentPosition = tape.begin();
}
void RegularTuringMachine::init(std::istream& inputStream) {
    RegularMachineParser parser(inputStream);
    auto machineConfig = parser.parse();

    this->transitions = std::move(machineConfig->transitions);
    this->haltingStates = std::move(machineConfig->haltingStates);
    this->setTape(machineConfig->getTape());
    this->currentState = machineConfig->currentState;
    this->states = machineConfig->states;
    this->alphabet = machineConfig->alphabet;
    // Set initial state and tape position
    this->currentState = parser.getInitialState();
    setInitialTapePosition(parser.getInitialTapePosition());
}

void RegularTuringMachine::setInitialTapePosition(int position) {
    // Convert the integer position to an iterator position in the doubly linked list tape
    auto it = tape.begin();
    while (position > 0){
        position--;
        it++;
    }
    this->currentPosition = it;
}
void RegularTuringMachine::run(const std::string &outputFileName) {
    while (true) {
        // Check if the current state is a halting state
        if (haltingStates.find(currentState) != haltingStates.end()) {
            break;
        }

        // Get the current symbol from the tape at the current position
        char currentSymbol = *currentPosition;

        // Find the transition for the current state and symbol
        TransitionKey key{currentSymbol, currentState};
        auto it = transitions.find(key);
        if (it == transitions.end()) {
            std::cerr << "Machine reached invalid state: " << currentSymbol << ", " << currentState << std::endl;
            break;
        }

        TransitionValue transition = it->second;

        // Write the new symbol to the tape at the current position
        *currentPosition = transition.newSymbol;

        // Update the current state
        currentState = transition.newState;

        // Move the head (current position) based on the command
        if (transition.command == 'L') {
            if (currentPosition != tape.begin()) {
                --currentPosition;
            }
        } else if (transition.command == 'R') {
            ++currentPosition;
            if (currentPosition == tape.end()) {
                // Append a blank space if at the end of the tape
                tape.push_back(' ');
                currentPosition = tape.last(); // Update currentPosition to the new end
            }
        }
    }

    outputTape(outputFileName);
}

void RegularTuringMachine::outputTape(const std::string &outputFileName){
    std::ofstream outFile(outputFileName, std::ios::out);
    if (outFile.is_open()) {
        for (auto it = tape.begin(); it != tape.end(); ++it) {
            outFile << *it;
        }
        outFile.close();
        std::cout << "Tape successfully written to " << outputFileName << std::endl;
    } else {
        std::cerr << "Unable to open or create file: " << outputFileName << std::endl;
    }
}


std::string RegularTuringMachine::getTape() {
    std::string tapeString;
    for (auto it = tape.begin(); it != tape.end(); ++it) {
        tapeString += *it;
    }
    return tapeString;
}
int RegularTuringMachine::getCurrentPosition() {
    int pos = 0;
    for (auto it = tape.begin(); it != currentPosition; ++it) {
        ++pos;
    }
    return pos;
}



void RegularTuringMachine::setCurrentPosition(int position) {
    currentPosition = tape.begin();
    for (int i = 0; i < position && currentPosition != tape.end(); ++i) {
        ++currentPosition;
    }

}

bool RegularTuringMachine::isValidCommand(const char command) {
    return command == 'L' || command == 'R' || command == 'S';
}

void RegularTuringMachine::processTape(const std::string& tapeData) {
    setTape(tapeData); // Set the tape using the provided data
}

std::size_t RegularTuringMachine::TransitionKeyHash::operator()(const TransitionKey& key) const {
    return std::hash<std::string>()(key.currentState) ^ std::hash<char>()(key.currentSymbol);
}

bool RegularTuringMachine::TransitionKey::operator==(const TransitionKey& other) const {
    return currentSymbol == other.currentSymbol && currentState == other.currentState;
}

void RegularTuringMachine::setTransitions(const std::unordered_map<TransitionKey, TransitionValue, TransitionKeyHash>& transitions) {
    this->transitions = transitions;
}

void RegularTuringMachine::setHaltingStates(const std::set<std::string>& haltingStates) {
    this->haltingStates = haltingStates;
}

void RegularTuringMachine::setStates(const std::set<std::string>& states) {
    this->states = states;
}


void RegularTuringMachine::setAlphabet(const std::set<char>& alphabet) {
    this->alphabet = alphabet;
}

void RegularTuringMachine::setCurrentState(const std::string& state) {
    if (states.find(state) != states.end()) {
        currentState = state;
    } else {
        std::cerr << "Invalid state: " << state << std::endl;
    }
}
std::string RegularTuringMachine::getCurrentState() {
    return currentState;
}
#include "multitapeturingmachine.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>
MultiTapeTuringMachine::MultiTapeTuringMachine() {}

MultiTapeTuringMachine::MultiTapeTuringMachine(const std::string& file) {
    // If initialization from a file is required
}

void MultiTapeTuringMachine::init(std::istream& inputStream) {
    // Initialize machine from input stream
    // Specific logic to set up the machine's initial state and tapes
    // Example: inputStream >> currentState >> ...;
}

void MultiTapeTuringMachine::run(const std::string& outputFileName) {
    std::ofstream outFile(outputFileName, std::ios::out);
    if (!outFile.is_open()) {
        std::cerr << "Unable to open or create file: " << outputFileName << std::endl;
        return;
    }

    while (true) {
        if (haltingStates.find(currentState) != haltingStates.end()) {
            break;
        }

        std::string currentSymbols;
        for (int pos : currentPositions) {
            currentSymbols.push_back(tape[pos]);
        }

        TransitionKey key{currentSymbols, currentState};
        auto it = transitions.find(key);

        if (it == transitions.end()) {
            std::cerr << "Machine reached invalid state: " << currentSymbols << ", " << currentState << std::endl;
            break;
        }

        const TransitionValue& transition = it->second;
        int tapeIndex = 0;
        for (char newSymbol : transition.newSymbolCombination) {
            tape[currentPositions[tapeIndex]] = newSymbol;
            tapeIndex++;
        }
        currentState = transition.newState;

        // Apply movement commands to each tape head
        for (size_t i = 0; i < transition.command.size(); ++i) {
            switch (transition.command[i]) {
                case 'L': --currentPositions[i]; break;
                case 'R': ++currentPositions[i]; break;
                case 'S': break; // Do nothing
            }
        }
    }

    // Write final tape state to file
    outFile << tape;
    outFile.close();
}

void MultiTapeTuringMachine::setTransitions(const std::unordered_map<TransitionKey, TransitionValue, TransitionKeyHash>& transitions) {
    this->transitions = transitions;
}

void MultiTapeTuringMachine::setHaltingStates(const std::vector<std::string>& haltingStates) {
    for (const auto& state : haltingStates) {
        this->haltingStates.insert(state);
    }
}

void MultiTapeTuringMachine::setTapes(const std::vector<std::string>& tapes) {
    // Concatenate all tapes into one tape with a separator
    std::ostringstream tapeStream;
    for (const auto& singleTape : tapes) {
        tapeStream << singleTape << '#';
    }
    tape = tapeStream.str();

    // Update initial positions for each tape
    currentPositions.clear();
    size_t pos = 0;
    for (const auto& singleTape : tapes) {
        currentPositions.push_back(pos);
        pos += singleTape.size() + 1; // +1 for the separator
    }
}

bool MultiTapeTuringMachine::TransitionKey::operator==(const TransitionKey& other) const {
    return currentSymbolCombination == other.currentSymbolCombination && currentState == other.currentState;
}

std::size_t MultiTapeTuringMachine::TransitionKeyHash::operator()(const TransitionKey& key) const {
    // Custom hash combining state and symbol combination
    return std::hash<std::string>()(key.currentState) ^ std::hash<std::string>()(key.currentSymbolCombination);
}

void MultiTapeTuringMachine::processTape(const std::string& tapeData) {
    // Processing and validating the tape data
}

bool MultiTapeTuringMachine::isValidTape(const std::string& tape) const {
    // Check if the tape is valid
    return std::all_of(tape.begin(), tape.end(), [this](char symbol) {
        return alphabet.find(symbol) != alphabet.end() || symbol == '#';
    });
}

bool MultiTapeTuringMachine::isValidCommand(const char command) {
    return command == 'L' || command == 'R' || command == 'S';
}
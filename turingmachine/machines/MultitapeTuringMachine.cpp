#include "MultitapeTuringMachine.h"
#include "../parsers/MultitapeParser.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>


MultiTapeTuringMachine::MultiTapeTuringMachine() {}

MultiTapeTuringMachine::MultiTapeTuringMachine(std::istream& inputStream) {
    init(inputStream);
}


void MultiTapeTuringMachine::outputTape(std::ofstream& outFile) const {
    for (const auto& it : tape) {
        outFile << it;
    }
}

void MultiTapeTuringMachine::init(std::istream& inputStream) {
    // Assume the parser has been implemented and returns the combined tape and initial iterators
    // parser.parse() should fill transitions, haltingStates, and the combined tape
    MultiTapeMachineParser parser(inputStream);
    parser.parse();
    this->transitions = parser.getTransitions();
    this->haltingStates = parser.getHaltingStates();
    this->tape = parser.getCombinedTape();
    this->tapeIterators = parser.getInitialTapePositions();
    this->states = parser.getStates();
    this->alphabetCombination = parser.getAlphabetCombinations();
    this->currentState = parser.getInitialState();
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
        for (auto it : tapeIterators) {
            currentSymbols.push_back(*it);
        }

        TransitionKey key{currentSymbols, currentState};
        auto it = transitions.find(key);
        if (it == transitions.end()) {
            std::cerr << "Machine reached invalid state: " << currentSymbols << ", " << currentState << std::endl;
            break;
        }

        const TransitionValue& transition = it->second;
        for (size_t i = 0; i < tapeIterators.size(); ++i) {
            if (transition.command[i] != 'S') {
                *tapeIterators[i] = transition.newSymbolCombination[i];
            }

            switch (transition.command[i]) {
                case 'L': --tapeIterators[i]; break;
                case 'R': ++tapeIterators[i]; break;
                case 'S': break; // Do nothing
            }
        }

        currentState = transition.newState;
    }

    // Write final tape state to file
    outputTape(outFile);
}


void MultiTapeTuringMachine::setTransitions(const std::unordered_map<TransitionKey, TransitionValue, TransitionKeyHash>& transitions) {
    this->transitions = transitions;
}

void MultiTapeTuringMachine::setHaltingStates(const std::set<std::string>& haltingStates) {
    for (const auto& state : haltingStates) {
        this->haltingStates.insert(state);
    }
}


void MultiTapeTuringMachine::setTape(const std::string& combinedTapeStr) {
    // Clear existing data
    tapeIterators.clear();

    // Convert the combined tape string into a DoublyLinkedList
    for (char c : combinedTapeStr) {
        tape.push_back(c);
    }

    // Set iterators for each tape segment
    auto it = tape.begin();
    while (it != tape.end()) {
        tapeIterators.push_back(it);

        // Move iterator to the next separator or end of the list
        while (it != tape.end() && *it != '#') {
            ++it;
        }

        // Skip the separator and move to the next segment
        if (it != tape.end() && *it == '#') {
            ++it;
        }
    }
}

void MultiTapeTuringMachine::outputTape(const std::string& outFile) {
    std::ofstream outFileStream(outFile, std::ios::out);
    if (outFileStream.is_open()) {
        // Iterate through the DoublyLinkedList<char> and write to file
        for (auto it = tape.begin(); it != tape.end(); ++it) {
            outFileStream << *it; // Assuming the DoublyLinkedList node has a 'data' member
        }
        outFileStream.close();
    } else {
        std::cerr << "Unable to open or create file: " << outFile << std::endl;
    }
}




void MultiTapeTuringMachine::setInitialTapePositions(const std::vector<typename DoublyLinkedList<char>::Iterator>& positions) {
    tapeIterators = positions;
}


bool MultiTapeTuringMachine::isValidTape(const std::string& tape) const {
    return true;
}

bool MultiTapeTuringMachine::isValidCommand(const std::string command) {
    // Validate the command string (e.g., "RRR", "LLL", "SRS")
    return std::all_of(command.begin(), command.end(), [](char cmd) {
        return cmd == 'L' || cmd == 'R' || cmd == 'S';
    });
}

bool MultiTapeTuringMachine::TransitionKey::operator==(const TransitionKey& other) const {
    return this->currentSymbolCombination == other.currentSymbolCombination &&
           this->currentState == other.currentState;
}

std::size_t MultiTapeTuringMachine::TransitionKeyHash::operator()(const TransitionKey& key) const {
    return std::hash<std::string>()(key.currentState) ^ std::hash<std::string>()(key.currentSymbolCombination);
}

void MultiTapeTuringMachine::processTape(const std::string& tapeData) {
    // Processing and validating the tape data
}

const std::set<std::string> &MultiTapeTuringMachine::getStates() const {
    return states;
}

void MultiTapeTuringMachine::setStates(const std::set<std::string> &states) {
    MultiTapeTuringMachine::states = states;
}

const std::set<std::string> &MultiTapeTuringMachine::getAlphabetCombination() const {
    return alphabetCombination;
}

void MultiTapeTuringMachine::setAlphabetCombination(const std::set<std::string> &alphabet) {
    MultiTapeTuringMachine::alphabetCombination = alphabetCombination;
}

const std::vector<DoublyLinkedList<char>::Iterator> &MultiTapeTuringMachine::getTapeIterators() const {
    return tapeIterators;
}

void MultiTapeTuringMachine::setTapeIterators(const std::vector<DoublyLinkedList<char>::Iterator> &tapeIterators) {
    MultiTapeTuringMachine::tapeIterators = tapeIterators;
}


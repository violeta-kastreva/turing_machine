#include "turingmachine.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>

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

void TuringMachine::run(const std::string &outputFileName) {
    while (true) {
        if(currentState == "halt") break;

        if (currentPosition <= 0) {
            std::cerr << "Machine reached invalid position on the tape";

        } else if (currentPosition >= tape.length()) {
            tape += " ";
        }

        char currentSymbol = tape[currentPosition];
        TransitionKey key{currentSymbol, currentState};

        auto it = transitions.find(key);
        if (it == transitions.end()) {
            std::cerr << "Machine reached invalid state";
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



bool TuringMachine::isValidTape(const std::string& tape) {
    for (char symbol : tape) {
        if (alphabet.find(symbol) == alphabet.end()) {
            return false;
        }
    }

    //return std::all_of(tape, alphabet, alphabet.con); redo with this
    return true;
}

bool TuringMachine::isValidCommand(const char command) {
    return command == 'L' || command == 'R' || command == 'S';
}

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

void TuringMachine::initMultiTape(const std::string &fileName) {}

void TuringMachine::initIterationLoop(const std::string &fileName) {}

void TuringMachine::initConditionalComposition(const std::string &fileName) {}

void TuringMachine::initComposition(const std::string &fileName) {}

void TuringMachine::initRegular(const std::string &fileName) {
    std::ifstream file(fileName);
    std::string line;
    // Skip the first line that specifies the type of the machine
    std::getline(file, line);
    currentPosition = 1;
    alphabet.insert('>');
    bool firstTransition = true;
    while (std::getline(file, line) && !line.empty()) {
        char currentSymbol;
        std::string currentTransitionState, newState;
        char newSymbol, command;
        if (parseTransition(line, currentSymbol, currentTransitionState, newSymbol, newState, command)) {
            TransitionKey key{currentSymbol, currentTransitionState};
            TransitionValue value{newSymbol, newState, command};
            transitions[key] = value;
            states.insert(currentTransitionState);
            states.insert(newState);
            alphabet.insert(currentSymbol);
            alphabet.insert(newSymbol);
            if(firstTransition) {
                currentState = currentTransitionState; firstTransition = false;
            }
        } else {
            tape = line;
            if (!isValidTape(tape)) {
                std::cerr << "Invalid tape: contains symbols not in the alphabet" << std::endl;
            }
            break;
        }
    }

    std::string initialTape;
    if (std::getline(file, initialTape)) {
        tape = initialTape;
    }

    file.close();
}

void TuringMachine::init(const std::string& fileName){
    std::ifstream tmData(fileName);
    std::string machineType;
    std::getline(tmData, machineType);

    if (!tmData.is_open()) {
        std::cerr << "Unable to open file: " << fileName << std::endl;
        return;
    }


    if(machineType == "REGULAR"){
        initRegular(fileName);
    } else if (machineType == "COMPOSITION"){
        initComposition(fileName);
    } else if (machineType == "CONDITIONAL"){
        initConditionalComposition(fileName);
    } else if (machineType == "LOOP"){
        initIterationLoop(fileName);
    } else if (machineType == "MULTITAPE"){
        initMultiTape(fileName);
    }

    tmData.close();

}

TuringMachine::TuringMachine(const std::string& fileName) {
    init(fileName);
}


std::size_t TuringMachine::TransitionKeyHash::operator()(const TransitionKey& key) const {
    return std::hash<std::string>()(key.currentState) ^ std::hash<char>()(key.currentSymbol);
}


bool TuringMachine::TransitionKey::operator==(const TransitionKey& other) const {
    return currentSymbol == other.currentSymbol && currentState == other.currentState;
}
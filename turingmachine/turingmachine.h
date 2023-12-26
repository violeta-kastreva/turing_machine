#pragma once
#ifndef TURING_MACHINE_TURINGMACHINE_H
#define TURING_MACHINE_TURINGMACHINE_H

#include <unordered_map>
#include <cstring>
#include <string>
#include <set>
#include <vector>
#include <tuple>

/**
* Interface for the Turing Machine class
*/


class TuringMachine{
public:
    TuringMachine();
    TuringMachine(const std::string& fileName);
    virtual void init(const std::string& fileName);
    virtual void run(const std::string& outputFileName);
    std::string getTape();
    void setTape(const std::string& tape);
    int getCurrentPosition();
    void setCurrentPosition(int position);

protected:
    /**
     * Custom Key for the transition map
     */
    struct TransitionKey {
        char currentSymbol;
        std::string currentState;
        bool operator==(const TransitionKey& other) const;
    };
    /**
     * Custom Value for the transition map
     */
    struct TransitionValue {
        char newSymbol;
        std::string newState;
        char command;
    };
    /**
     * Custom Hash for the transition map
     */
    struct TransitionKeyHash {
        std::size_t operator()(const TransitionKey& key) const;
    };


    std::set<std::string> states;
    std::set<std::string> haltingStates;
    //! transition map with custom attributes
    std::unordered_map<TransitionKey, TransitionValue, TransitionKeyHash> transitions;
    std::set<char> alphabet;

    std::string currentState;
    int currentPosition = 0; //on the tape
    std::string tape;

    void outputTape(const std::string& outFile);
    bool isValidTape(const std::string& tape);
    static bool isValidCommand(const char command);
    bool parseTransition(const std::string& line, char& currentSymbol, std::string& currentState,char& newSymbol,std::string& newState,char& command);
    void processTape(const std::string& tapeData);
    void processTransitions(std::ifstream& file, std::string& line);
};

#endif //TURING_MACHINE_TURINGMACHINE_H

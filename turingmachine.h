#pragma once
#ifndef TURING_MACHINE_TURINGMACHINE_H
#define TURING_MACHINE_TURINGMACHINE_H

#include <unordered_map>
#include <cstring>
#include <string>
#include <set>
#include <vector>
#include <tuple>


class TuringMachine{
public:
    TuringMachine(const std::string& fileName);
    void init(const std::string& fileName);
    void run(const std::string& outputFileName);

private:
    struct TransitionKey {
        char currentSymbol;
        std::string currentState;
        bool operator==(const TransitionKey& other) const;
    };

    struct TransitionValue {
        char newSymbol;
        std::string newState;
        char command;
    };

    struct TransitionKeyHash {
        std::size_t operator()(const TransitionKey& key) const;
    };

    std::set<std::string> states; //final?
    std::unordered_map<TransitionKey, TransitionValue, TransitionKeyHash> transitions;
    std::set<char> alphabet;

    std::string currentState;
    int currentPosition = 0; //on the tape
    std::string tape;


    void outputTape(const std::string& outFile);
    bool isValidTape(const std::string& tape);
    static bool isValidCommand(const char command);
    bool parseTransition(const std::string& line, char& currentSymbol, std::string& currentState,char& newSymbol,std::string& newState,char& command);
    void initRegular(const std::string& fileName);

    void initIterationLoop(const std::string& fileName);
    void initComposition(const std::string& fileName);
    void initConditionalComposition(const std::string& fileName);
    void initMultiTape(const std::string& fileName);

};


#endif //TURING_MACHINE_TURINGMACHINE_H

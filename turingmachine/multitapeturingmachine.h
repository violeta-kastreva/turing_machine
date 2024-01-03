#ifndef TURING_MACHINE_MULTITAPETURINGMACHINE_H
#define TURING_MACHINE_MULTITAPETURINGMACHINE_H

#include "regularturingmachine.h"
#include "turingmachine.h"
/********************************************//**
 *
 ***********************************************/
class MultiTapeTuringMachine : public TuringMachine {
    MultiTapeTuringMachine();
    MultiTapeTuringMachine(const std::string& file);
    virtual void init(const std::string& fileName);
    virtual void run(const std::string& outputFileName);
private:
    struct TransitionKey {
        std::string currentSymbolCombination;
        std::string currentState;
        bool operator==(const TransitionKey& other) const;
    };
    /**
     * Custom Value for the transition map
     */
    struct TransitionValue {
        std::string newSymbolCombination;
        std::string newState;
        std::string command;
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
    std::vector<int> currentPositions = {0}; //on the tape
    std::string tape;

    void outputTape(const std::string& outFile);
    bool isValidTape(const std::string& tape);
    static bool isValidCommand(const char command);
    bool parseTransition(const std::string& line, std::string& currentSymbolCombination, std::string& currentTransitionState, std::string& newSymbols, std::string& newSymbolCombination, std::string& commands);
    void processTape(const std::string& tapeData);
    void processTransitions(std::ifstream& file, std::string& line);
    void appendNextTapeToTape(const std::string& outFile);

    int getCurrentPosition(int index);
    void setCurrentPosition(int index, int position);
    std::string getTape();
    void setTape(const std::string& tape);

};

#endif //TURING_MACHINE_MULTITAPETURINGMACHINE_H

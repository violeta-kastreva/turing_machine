#ifndef TURING_MACHINE_ITERATIONTURINGMACHINE_H
#define TURING_MACHINE_ITERATIONTURINGMACHINE_H


#include "regularturingmachine.h"
#include "turingmachine.h"
#include <memory>
#include <fstream>
#include <iostream>
class IterationLoopTuringMachine : public TuringMachine {
public:
    IterationLoopTuringMachine(std::istream& inputStream);
    IterationLoopTuringMachine();
    void init(std::istream& inputStream) override;
    void run(const std::string& outputFileName) override;

private:
    std::unique_ptr<RegularTuringMachine> loopMachine;
    std::unique_ptr<RegularTuringMachine> postLoopMachine;
    char loopConditionSymbol;
};


#endif //TURING_MACHINE_ITERATIONTURINGMACHINE_H

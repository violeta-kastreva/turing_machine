

#ifndef TURING_MACHINE_ITERATIONTURINGMACHINE_H
#define TURING_MACHINE_ITERATIONTURINGMACHINE_H


#include "RegularTuringMachine.h"
#include "TuringMachine.h"
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
    std::unique_ptr<RegularTuringMachine> loopMachine;        ///< Turing machine to be run in the loop.
    std::unique_ptr<RegularTuringMachine> postLoopMachine;    ///< Turing machine to be run after the loop.
    char loopConditionSymbol;                                ///< Symbol that dictates the looping condition.
};

#endif //TURING_MACHINE_ITERATIONTURINGMACHINE_H

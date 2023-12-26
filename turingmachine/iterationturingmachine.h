#ifndef TURING_MACHINE_ITERATIONTURINGMACHINE_H
#define TURING_MACHINE_ITERATIONTURINGMACHINE_H


#include "turingmachine.h"
#include "TuringMachine.h"
#include <memory>
#include <fstream>
#include <iostream>

class IterationLoopTuringMachine : public TuringMachine {
public:
    IterationLoopTuringMachine(const std::string& fileName);
    IterationLoopTuringMachine();
    void init(const std::string& fileName);
    void run(const std::string &outputFileName);


private:
    std::unique_ptr<TuringMachine> loopMachine;    //! Machine to be run as a loop
    std::unique_ptr<TuringMachine> postLoopMachine; //! Machine to be run in the loop

    std::string createTempFile(const std::vector<std::string>& inputLines, int index);

};


#endif //TURING_MACHINE_ITERATIONTURINGMACHINE_H

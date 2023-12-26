#ifndef TURING_MACHINE_COMPOSITIONTURINGMACHINE_H
#define TURING_MACHINE_COMPOSITIONTURINGMACHINE_H

#include <memory>
#include "turingmachine.h"

/**
* Interface for the Composition Turing Machine class (composition of two machines)
*/
class CompositionTuringMachine : public TuringMachine{
public:
    CompositionTuringMachine();
    CompositionTuringMachine(const std::string &fileName);
    void init(const std::string& fileName);
    void run(const std::string &outputFileName);

private:
    //! first machine to be executed
    std::unique_ptr<TuringMachine> machine1;
    //! second machine to be executed
    std::unique_ptr<TuringMachine> machine2;

    std::string createTempFile(const std::vector<std::string>& inputLines, int index);
};


#endif //TURING_MACHINE_COMPOSITIONTURINGMACHINE_H

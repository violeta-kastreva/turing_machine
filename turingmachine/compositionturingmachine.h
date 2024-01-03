#ifndef TURING_MACHINE_COMPOSITIONTURINGMACHINE_H
#define TURING_MACHINE_COMPOSITIONTURINGMACHINE_H

#include <memory>
#include "regularturingmachine.h"
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
    std::unique_ptr<RegularTuringMachine> machine1;
    //! second machine to be executed
    std::unique_ptr<RegularTuringMachine> machine2;
    std::string createTempFile(const std::vector<std::string>& inputLines, int index);
};


#endif //TURING_MACHINE_COMPOSITIONTURINGMACHINE_H

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
    CompositionTuringMachine(std::istream& inputStream);
    void init(std::istream& inputStream) override;
    void run(const std::string &outputFileName);
    void setMachines(std::unique_ptr<RegularTuringMachine> m1, std::unique_ptr<RegularTuringMachine> m2);
    void setTape(const std::string& tape);

private:
    //! first machine to be executed
    std::unique_ptr<RegularTuringMachine> machine1;
    //! second machine to be executed
    std::unique_ptr<RegularTuringMachine> machine2;
    std::string createTempFile(const std::vector<std::string>& inputLines, int index);
};


#endif //TURING_MACHINE_COMPOSITIONTURINGMACHINE_H

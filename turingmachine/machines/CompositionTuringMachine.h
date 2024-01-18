#ifndef TURING_MACHINE_COMPOSITIONTURINGMACHINE_H
#define TURING_MACHINE_COMPOSITIONTURINGMACHINE_H

#include <memory>
#include "RegularTuringMachine.h"
#include "TuringMachine.h"

class CompositionTuringMachine : public TuringMachine{
public:
    CompositionTuringMachine();
    CompositionTuringMachine(std::istream& inputStream);
    void init(std::istream& inputStream) override;
    void run(const std::string &outputFileName);
    void setMachines(std::unique_ptr<RegularTuringMachine> m1, std::unique_ptr<RegularTuringMachine> m2);
    void setTape(const std::string& tape);

private:
    std::unique_ptr<RegularTuringMachine> machine1; ///< First machine to be executed
    std::unique_ptr<RegularTuringMachine> machine2; ///< Second machine to be executed
    std::string createTempFile(const std::vector<std::string>& inputLines, int index);
};


#endif //TURING_MACHINE_COMPOSITIONTURINGMACHINE_H

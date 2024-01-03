#ifndef TURING_MACHINE_CONDITIONALTURINGMACHINE_H
#define TURING_MACHINE_CONDITIONALTURINGMACHINE_H

#include "regularturingmachine.h"
#include "turingmachine.h"


class ConditionalCompositionTuringMachine : public TuringMachine {
public:
    ConditionalCompositionTuringMachine();
    ConditionalCompositionTuringMachine(const std::string& fileName);
    void init(const std::string& fileName);
    void run(const std::string &outputFileName);

private:
    std::unique_ptr<RegularTuringMachine> machine1;
    std::unique_ptr<RegularTuringMachine> machine2;
    std::unique_ptr<RegularTuringMachine> machine3;

    std::string createTempFile(const std::vector<std::string>& inputLines, int index);
};

#endif //TURING_MACHINE_CONDITIONALTURINGMACHINE_H

#ifndef TURING_MACHINE_CONDITIONALTURINGMACHINE_H
#define TURING_MACHINE_CONDITIONALTURINGMACHINE_H

#include "RegularTuringMachine.h"
#include "TuringMachine.h"

class ConditionalCompositionTuringMachine : public TuringMachine {
public:
    ConditionalCompositionTuringMachine();
    ConditionalCompositionTuringMachine(std::istream& inputStream);
    void init(std::istream& inputStream) override;
    void run(const std::string &outputFileName);

private:
    std::unique_ptr<RegularTuringMachine> machine1;
    std::unique_ptr<RegularTuringMachine> machine2;
    std::unique_ptr<RegularTuringMachine> machine3;

    std::string createTempFile(const std::vector<std::string>& inputLines, int index);
    std::set<char> conditionalSymbols;

};

#endif //TURING_MACHINE_CONDITIONALTURINGMACHINE_H

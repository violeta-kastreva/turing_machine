/**
 * @file ConditionalCompositionTuringMachine.h
 * @brief Defines the ConditionalCompositionTuringMachine class.
 *
 * This file contains the definition of the ConditionalCompositionTuringMachine class, which represents a Turing machine
 * that executes one of two Turing machines based on a condition determined by the output of a preceding machine.
 */

#ifndef TURING_MACHINE_CONDITIONALTURINGMACHINE_H
#define TURING_MACHINE_CONDITIONALTURINGMACHINE_H

#include "regularturingmachine.h"
#include "turingmachine.h"

/**
 * @class ConditionalCompositionTuringMachine
 * @brief A Turing machine that executes one of two machines based on a conditional symbol.
 *
 * ConditionalCompositionTuringMachine executes a primary Turing Machine and then, based on the symbol
 * encountered at the end of its execution, decides which of the other two Turing Machines to execute next.
 */
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

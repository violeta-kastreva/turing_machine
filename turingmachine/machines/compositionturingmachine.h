/**
 * @file CompositionTuringMachine.h
 * @brief Defines the CompositionTuringMachine class.
 *
 * This file contains the definition of the CompositionTuringMachine class, which represents a Turing machine
 * that executes two regular Turing machines in sequence on the same tape.
 */


#ifndef TURING_MACHINE_COMPOSITIONTURINGMACHINE_H
#define TURING_MACHINE_COMPOSITIONTURINGMACHINE_H

#include <memory>
#include "regularturingmachine.h"
#include "turingmachine.h"


/**
 * @class CompositionTuringMachine
 * @brief A Turing machine that composes two Regular Turing Machines.
 *
 * CompositionTuringMachine executes two Regular Turing Machines sequentially on the same tape. It initializes
 * and runs each machine in turn, passing the output tape of the first machine as the input tape to the second.
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
    std::unique_ptr<RegularTuringMachine> machine1; ///< First machine to be executed
    std::unique_ptr<RegularTuringMachine> machine2; ///< Second machine to be executed
    std::string createTempFile(const std::vector<std::string>& inputLines, int index);
};


#endif //TURING_MACHINE_COMPOSITIONTURINGMACHINE_H

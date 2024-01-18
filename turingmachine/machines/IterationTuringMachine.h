/**
 * @file IterationLoopTuringMachine.h
 * @brief Defines the IterationLoopTuringMachine class.
 *
 * This file contains the definition of the IterationLoopTuringMachine class. It represents a Turing machine
 * that executes a loop Turing machine repeatedly until a specified condition is met, followed by the execution
 * of a post-loop Turing machine.
 */

#ifndef TURING_MACHINE_ITERATIONTURINGMACHINE_H
#define TURING_MACHINE_ITERATIONTURINGMACHINE_H


#include "RegularTuringMachine.h"
#include "TuringMachine.h"
#include <memory>
#include <fstream>
#include <iostream>
/**
 * @class IterationLoopTuringMachine
 * @brief A Turing machine that executes a loop machine followed by a post-loop machine based on a condition.
 *
 * Inherits from TuringMachine and provides functionality specific to Turing machines with iterative loops.
 * This machine runs a "loop" machine repeatedly until a specific condition is no longer met, at which point
 * a "post-loop" machine is executed.
 */
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

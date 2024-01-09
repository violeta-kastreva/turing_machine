#pragma once
#ifndef TURING_MACHINE_TURINGMACHINEFACTORY_H
#define TURING_MACHINE_TURINGMACHINEFACTORY_H

#include <string>
#include "../machines/regularturingmachine.h"
/**
 * @class TuringMachineFactory
 * @brief Factory for creating Turing Machine instances.
 *
 * This class is responsible for creating instances of different types of Turing machines based on the
 * specifications provided in an input file.
 */
class TuringMachineFactory {
public:
    /**
     * @brief Default constructor for TuringMachineFactory.
     */
    TuringMachineFactory();

    /**
     * @brief Creates and returns a Turing machine instance based on the input file.
     * @param fileName The name of the file containing the Turing machine specifications.
     * @return A pointer to the created Turing machine instance.
     * @exception std::runtime_error Thrown if the file cannot be opened or the machine type is unknown.
     */
    TuringMachine* getMachine(const std::string& fileName);
};


#endif //TURING_MACHINE_TURINGMACHINEFACTORY_H

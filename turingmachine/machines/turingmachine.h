//
// Created by Vily on 31.12.2023 г..
//

#ifndef TURING_MACHINE_TURINGMACHINE_H
#define TURING_MACHINE_TURINGMACHINE_H

#include <string>
/**
 * @class TuringMachine
 * @brief Abstract base class representing a Turing Machine.
 *
 * This class defines the basic interface for Turing machines. Specific types of Turing machines
 * will inherit from this class and implement the init and run methods.
 */
class TuringMachine {
public:
    /**
     * @brief Initializes the Turing machine with input data.
     * @param inputStream The input stream to read data from.
     * @exception std::runtime_error Thrown if initialization fails.
     */
    virtual void init(std::istream& inputStream) = 0;

    /**
     * @brief Runs the Turing machine and outputs the result to a file.
     * @param outputFileName Name of the file to write the output to.
     * @exception std::runtime_error Thrown if the machine encounters an error during execution.
     */
    virtual void run(const std::string& outputFileName) = 0;
};


#endif //TURING_MACHINE_TURINGMACHINE_H

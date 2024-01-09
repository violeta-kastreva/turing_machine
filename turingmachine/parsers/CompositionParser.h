/**
 * @file CompositionMachineParser.h
 * @brief Parser class for Composition Turing Machines.
 *
 * This file contains the definition of the CompositionMachineParser class, which extends BaseParser
 * to specifically parse configurations for Composition Turing Machines.
 * These machines are composed of two Regular Turing Machines executing sequentially.
 */

#ifndef TURING_MACHINE_COMPOSITIONPARSER_H
#define TURING_MACHINE_COMPOSITIONPARSER_H

#include <memory>
#include "BaseParser.h"
#include "../machines/CompositionTuringMachine.h"


/**
 * @class CompositionMachineParser
 * @brief Parser for Composition Turing Machines.
 *
 * Inherits from BaseParser and provides functionality to parse the configuration for
 * Composition Turing Machines, which are composed of two Regular Turing Machines.
 */
class CompositionMachineParser : public BaseParser {
public:
    using BaseParser::BaseParser;  // Inherit the constructor

    /**
     * @brief Parses the configuration for two Regular Turing Machines and their tape.
     *
     * Parses two separate Turing Machines and their shared tape data from the input stream.
     */
    void parse();

    /**
     * @brief Retrieves the first parsed Regular Turing Machine.
     *
     * @return A unique pointer to the first Regular Turing Machine.
     */
    std::unique_ptr<RegularTuringMachine> getFirstMachine();

    /**
     * @brief Retrieves the second parsed Regular Turing Machine.
     *
     * @return A unique pointer to the second Regular Turing Machine.
     */
    std::unique_ptr<RegularTuringMachine> getSecondMachine();

    /**
     * @brief Retrieves the shared tape data of the parsed Turing Machines.
     *
     * @return The tape data as a string.
     */
    std::string getTape();
private:
    std::unique_ptr<RegularTuringMachine> machine1;
    std::unique_ptr<RegularTuringMachine> machine2;
    std::string tape;
};

#endif //TURING_MACHINE_COMPOSITIONPARSER_H

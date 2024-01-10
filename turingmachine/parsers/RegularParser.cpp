

#include "../machines/RegularTuringMachine.h"
#include "RegularParser.h"
/**
 * @brief Parses a Regular Turing Machine configuration and constructs the machine.
 *
 * Parses transitions, halting states, and tape from the input stream and uses them
 * to construct a RegularTuringMachine. It sets the transitions, halting states, tape,
 * set of states, and alphabet for the machine. Additionally, it sets the initial state
 * and initial tape position for the Turing Machine based on the parsed data.
 *
 * @return A unique pointer to the constructed RegularTuringMachine.
 */
std::unique_ptr<RegularTuringMachine> RegularMachineParser::parse() {
    auto machine = std::make_unique<RegularTuringMachine>();

    // Parse transitions and set them in the machine
    std::unordered_map<RegularTuringMachine::TransitionKey, RegularTuringMachine::TransitionValue, RegularTuringMachine::TransitionKeyHash> transitions;
    parseTransitions(transitions);
    machine->setTransitions(transitions);

    // Parse halting states and set them in the machine
    std::set<std::string> haltingStates;
    parseHaltingStates(haltingStates);
    machine->setHaltingStates(haltingStates);

    // Parse the tape and set it in the machine
    std::string tape;
    parseTape(tape);
    machine->setTape(tape);

    // Set the states and alphabet in the machine
    machine->setStates(getStates());
    machine->setAlphabet(getAlphabet());

    // Set the initial state and tape position for the machine
    machine->setCurrentState(getInitialState());
    machine->setCurrentPosition(getInitialTapePosition());

    return machine;
}

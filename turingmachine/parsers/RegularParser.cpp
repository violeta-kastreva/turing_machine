#include "../machines/RegularTuringMachine.h"
#include "RegularParser.h"
std::unique_ptr<RegularTuringMachine> RegularMachineParser::parse() {
    try {
        auto machine = std::make_unique<RegularTuringMachine>();

        std::unordered_map<RegularTuringMachine::TransitionKey, RegularTuringMachine::TransitionValue, RegularTuringMachine::TransitionKeyHash> transitions;
        parseTransitions(transitions);
        machine->setTransitions(transitions);

        std::set<std::string> haltingStates;
        parseHaltingStates(haltingStates);
        machine->setHaltingStates(haltingStates);

        std::string tape;
        parseTape(tape);
        machine->setTape(tape);

        machine->setStates(getStates());
        machine->setAlphabet(getAlphabet());

        machine->setCurrentState(getInitialState());
        machine->setCurrentPosition(getInitialTapePosition());

        return machine;
    } catch (const std::exception& e) {
        throw std::runtime_error("Error parsing Turing Machine: " + std::string(e.what()));
    }
}

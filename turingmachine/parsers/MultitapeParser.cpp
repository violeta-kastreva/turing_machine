#include <limits>
#include <sstream>
#include "MultitapeParser.h"
#include <sstream>
#include <string>
#include <vector>

MultiTapeMachineParser::MultiTapeMachineParser(std::istream& input) : BaseParser(input) {}

const std::set<std::string>& MultiTapeMachineParser::getHaltingStates() const {
    return haltingStates;
}

const std::unordered_map<MultiTapeTuringMachine::TransitionKey, MultiTapeTuringMachine::TransitionValue, MultiTapeTuringMachine::TransitionKeyHash>& MultiTapeMachineParser::getTransitions() const{
    return transitions;
}

DoublyLinkedList<char> MultiTapeMachineParser::getCombinedTape(const std::string& currTape) const {
    DoublyLinkedList<char> tapeList;
    for (char ch : currTape) {
        tapeList.push_back(ch);
    }
    return tapeList;
}
DoublyLinkedList<char> MultiTapeMachineParser::getCombinedTape() const {
    DoublyLinkedList<char> tapeList;
    for (char ch : combinedTape) {
        tapeList.push_back(ch);
    }
    return tapeList;
}


std::unordered_map<MultiTapeTuringMachine::TransitionKey, MultiTapeTuringMachine::TransitionValue, MultiTapeTuringMachine::TransitionKeyHash> MultiTapeMachineParser::parseTransitions() {
    std::unordered_map<MultiTapeTuringMachine::TransitionKey, MultiTapeTuringMachine::TransitionValue, MultiTapeTuringMachine::TransitionKeyHash> transitions;
    std::string line;
    bool firstTransition = true;
    while (std::getline(inputStream, line) && !line.empty()) {
        MultiTapeTuringMachine::TransitionKey key;
        MultiTapeTuringMachine::TransitionValue value;

        if (parseTransitionLine(line, key, value)) {
            transitions[key] = value;

            states.insert(key.currentState);
            states.insert(value.newState);
            alphabetCombination.insert(key.currentSymbolCombination);
            alphabetCombination.insert(value.newSymbolCombination);

            if (firstTransition) {
                // Set the initial state from the first valid transition
                this->initialState = key.currentState;
                firstTransition = false;
            }
        } else {
            //inputStream.putback('\n');
            break;
        }
    }

    return transitions;
}

const std::vector<typename DoublyLinkedList<char>::Iterator>& MultiTapeMachineParser::getInitialTapePositions() const {
    return this->initialTapePositions;
}
std::unique_ptr<MultiTapeTuringMachine> MultiTapeMachineParser::parse() {
    // Parse transitions, halting states, and tapes
    this->transitions = this->parseTransitions();
    this->haltingStates = this->parseHaltingStates();
    this->combinedTape = this->parseTapes();

    // Create a new MultiTapeTuringMachine and set its properties
    auto machine = std::make_unique<MultiTapeTuringMachine>();
    machine->setTransitions(this->transitions);
    machine->setHaltingStates(this->getHaltingStates());
    machine->setTape(this->combinedTape);
    machine->setInitialTapePositions(this->initialTapePositions);
    //machine->setTapeIterators();
    machine->setAlphabetCombination(this->alphabetCombination);
    machine->setStates(this->states);
    return machine;
}


std::set<std::string> MultiTapeMachineParser::parseHaltingStates() {
    //inputStream.putback('\n');

    std::set<std::string> haltingStates;
   // int count;
    //inputStream >> count; // Read number of halting states
    //inputStream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string line;

    while (std::getline(inputStream, line)) {
        if (!line.empty() && (line[0] == '>' || isupper(line[0]))) {
            inputStream.putback('\n');
            for (auto it = line.rbegin(); it != line.rend(); ++it) inputStream.putback(*it);
            break;
        }
        haltingStates.insert(line);
    }

//    std::string state;
//    while (count-- > 0 && std::getline(inputStream, state)) {
//        haltingStates.insert(state);
//    }
    return haltingStates;
}

void MultiTapeMachineParser::initializeIterators(const DoublyLinkedList<char>& combinedTapeList,
                                                 const std::vector<std::string>& tapes) {
    // Convert each tape to a DoublyLinkedList and store the start iterator of each
    initialTapePositions.clear();

    auto it = combinedTapeList.begin();
    for (const auto& tape : tapes) {
        initialTapePositions.push_back(it);

        // Move iterator to the end of the current tape segment
        for (size_t i = 0; i < tape.length(); ++i) {
            ++it;
        }

        // Skip the separator (assuming one character like '#')
        if (it != combinedTapeList.end()) {
            ++it;
        }
    }
}


std::string MultiTapeMachineParser::parseTapes() {
    std::string combinedTape;
    std::vector<std::string> tapes;
    std::string line;
   // int tapeCount;
   // inputStream >> tapeCount; // Read the number of tapes

    // Combine tapes using a separator
    while (std::getline(inputStream, line)) {
        tapes.push_back(line); // Store individual tapes for iterator initialization
        if (!combinedTape.empty()) {
            line[0] = '#'; // Separator
        }
        tapes.push_back(line);
        combinedTape += line;
    }

    // Initialize iterators based on the combined tape
    initializeIterators(getCombinedTape(combinedTape), tapes);

    return combinedTape;
}


bool MultiTapeMachineParser::parseTransitionLine(const std::string& line,
                                                 MultiTapeTuringMachine::TransitionKey& key,
                                                 MultiTapeTuringMachine::TransitionValue& value) {
    std::istringstream stream(line);
    char arrow;
    std::string currentSymbolCombination, newState, newSymbolCombination, commands;

    // Parse current state and symbol combination
    if (!std::getline(stream, currentSymbolCombination, '{')) return false;
    if (!std::getline(stream, key.currentState, '}')) return false;

    // Parse arrow
    if (!(stream >> arrow >> arrow) || arrow != '>') return false;

    // Parse new state and new symbol combination
    if (!std::getline(stream, newSymbolCombination, '{')) return false;
    if (!std::getline(stream, newState, '}')) return false;

    // Parse commands
    stream >> commands;

    // Assign parsed values to the key and value
    key.currentSymbolCombination = currentSymbolCombination;
    value.newSymbolCombination = newSymbolCombination;
    value.newState = newState;
    value.command = commands;

    return true;
}
const std::set<std::string> MultiTapeMachineParser::getAlphabetCombinations() const {
    return alphabetCombination;
}

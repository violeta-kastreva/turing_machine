#include "CompositionTuringMachine.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>


/**
* Method for creating a temporary file, used to create input files for the two turing machines
*/
std::string CompositionTuringMachine::createTempFile(const std::vector<std::string>& inputLines, int index) {
    try {
        //! Create a temporary file path in a known writable directory
        std::filesystem::path tempDir = std::filesystem::temp_directory_path();
        std::filesystem::path tempFile;
        index == 0 ? tempFile = tempDir / "temp_file0.txt" : tempFile = tempDir / "temp_file1.txt";

        std::ofstream outFile(tempFile);
        if (outFile.is_open()) {
            for (const auto& line : inputLines) {
                outFile << line << "\n";
            }
            outFile.close();
            return tempFile.string();
        } else {
            std::cerr << "Unable to create temporary file in: " << tempFile << std::endl;
        }
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
    }
}



/**
* Initializing the Composition Turing Machine, creating two input files for each of the machines to be initialized from
*/
void CompositionTuringMachine::init(const std::string &fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << fileName << std::endl;
        return;
    }

    std::string line;
    std::vector<std::string> machine1Input;
    std::vector<std::string> machine2Input;
    bool readingFirstMachine = true;

    while (std::getline(file, line)) {
        if (line == "SECOND MACHINE STATES") {
            readingFirstMachine = false;
            machine2Input.push_back(line);
            continue;
        }
        if (readingFirstMachine) {
            machine1Input.push_back(line);
        } else {
            machine2Input.push_back(line);
        }
    }
    file.close();

    machine1Input.push_back(machine2Input[machine2Input.size()-1]);
    //! Creating temporary files and writing input to them
    std::string machine1FilePath = createTempFile(machine1Input, 0);
    std::string machine2FilePath = createTempFile(machine2Input, 1);

    //! Initializes Turing Machines with temporary file paths
    machine1 = std::make_unique<TuringMachine>(machine1FilePath);
    machine2 = std::make_unique<TuringMachine>(machine2FilePath);
    //machine1->setTape(machine2->getTape());

    //! Deleting temporary files
    remove(machine1FilePath.c_str());
    remove(machine2FilePath.c_str());
}

/**
* Runs the first given machine, then the other one
*/
void CompositionTuringMachine::run(const std::string &outputFileName) {

    machine1->run(outputFileName);

    std::string intermediateTape = machine1->getTape();
    machine2->setTape(intermediateTape);
    machine2->setCurrentPosition(machine1->getCurrentPosition());
    // Run the second Turing Machine
    machine2->run(outputFileName);
}

/**
* Constructor of a Compotision Turing Machine by a given input file, calls the initializing method
*/
CompositionTuringMachine::CompositionTuringMachine(const std::string& fileName) {
    init(fileName);
}

/**
* Empty constructor for the Factory class
*/
CompositionTuringMachine::CompositionTuringMachine() {
}

#include <memory>
#include <iostream>
#include <fstream>
#include <filesystem>
#include "conditionalturingmachine.h"


/**
* Method for creating a temporary file, used to create input files for the three turing machines
*/
std::string ConditionalCompositionTuringMachine::createTempFile(const std::vector<std::string>& inputLines, int index) {
    try {
        //! Create a temporary file path in a known writable directory
        std::filesystem::path tempDir = std::filesystem::temp_directory_path();
        std::filesystem::path tempFile;
        if(index==0){
            tempFile = tempDir / "temp_file0.txt";
        } else if (index == 1){
            tempFile = tempDir / "temp_file1.txt";
        } else {
            tempFile = tempDir / "temp_file2.txt";
        }

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
void ConditionalCompositionTuringMachine::init(const std::string &fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << fileName << std::endl;
        return;
    }

    std::string line;
    std::vector<std::string> machine1Input;
    std::vector<std::string> machine2Input;
    std::vector<std::string> machine3Input;

    //! Flags to determine which machine we are currently reading
    bool readingFirstMachine = true;
    bool readingSecondMachine = false;

    while (std::getline(file, line)) {
        if (line == "SECOND MACHINE STATES") {
            readingFirstMachine = false;
            readingSecondMachine = true;
            machine2Input.push_back(line);
            continue;
        } else if (line == "THIRD MACHINE STATES") {
            readingSecondMachine = false;
            machine3Input.push_back(line);
            continue;
        }

        if (readingFirstMachine) {
            machine1Input.push_back(line);
        } else if (readingSecondMachine) {
            machine2Input.push_back(line);
        } else {
            machine3Input.push_back(line);
        }
    }
    file.close();

    //! Creating temporary files and writing input to them
    std::string machine1FilePath = createTempFile(machine1Input, 0);
    std::string machine2FilePath = createTempFile(machine2Input, 1);
    std::string machine3FilePath = createTempFile(machine3Input, 2);

    //! Initializes Turing Machines with temporary file paths
    machine1 = std::make_unique<RegularTuringMachine>(machine1FilePath);
    machine2 = std::make_unique<RegularTuringMachine>(machine2FilePath);
    machine3 = std::make_unique<RegularTuringMachine>(machine3FilePath);
    machine1->setTape(machine3->getTape());

    //! Deleting temporary files
    remove(machine1FilePath.c_str());
    remove(machine2FilePath.c_str());
    remove(machine3FilePath.c_str());
}


void ConditionalCompositionTuringMachine::run(const std::string &outputFileName) {

    machine1->run(outputFileName);
    if (machine1->getTape()[machine1->getCurrentPosition()] != '0'
        && machine1->getTape()[machine1->getCurrentPosition()] != 'n') {
        std::string intermediateTape = machine1->getTape();
        machine2->setTape(intermediateTape);
        machine2->setCurrentPosition(machine1->getCurrentPosition());
        //! Run the second Turing Machine
        machine2->run(outputFileName);
    } else {
        std::string intermediateTape = machine1->getTape();
        machine3->setTape(intermediateTape);
        machine3->setCurrentPosition(machine1->getCurrentPosition());
        //! Run the third Turing Machine
        machine3->run(outputFileName);
    }

}

ConditionalCompositionTuringMachine::ConditionalCompositionTuringMachine() {

}

ConditionalCompositionTuringMachine::ConditionalCompositionTuringMachine(const std::string &fileName) {
    init(fileName);
}

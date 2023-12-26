#include <filesystem>
#include "iterationturingmachine.h"


/**
* Method for creating a temporary file, used to create input files for the two turing machines
*/
std::string IterationLoopTuringMachine::createTempFile(const std::vector<std::string>& inputLines, int index) {
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




void IterationLoopTuringMachine::init(const std::string &fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << fileName << std::endl;
        return;
    }

    std::string line;
    std::vector<std::string> loopMachineInput;
    std::vector<std::string> postLoopMachineInput;
    bool readingLoopMachine = true;

    while (std::getline(file, line)) {
        if (line == "POST LOOP MACHINE STATES") {
            readingLoopMachine = false;
            postLoopMachineInput.push_back(line);
            continue;
        }
        if (readingLoopMachine) {
            loopMachineInput.push_back(line);
        } else {
            postLoopMachineInput.push_back(line);
        }
    }
    file.close();

    std::string loopMachineFilePath = createTempFile(loopMachineInput, 0);
    std::string postLoopMachineFilePath = createTempFile(postLoopMachineInput, 1);

    loopMachine = std::make_unique<TuringMachine>(loopMachineFilePath);
    postLoopMachine = std::make_unique<TuringMachine>(postLoopMachineFilePath);
    loopMachine->setTape(postLoopMachine->getTape());

    remove(loopMachineFilePath.c_str());
    remove(postLoopMachineFilePath.c_str());
}


void IterationLoopTuringMachine::run(const std::string &outputFileName) {

    do{
        loopMachine->run(outputFileName);
        std::string intermediateTape = loopMachine->getTape();
        postLoopMachine->setTape(intermediateTape);
        postLoopMachine->setCurrentPosition(loopMachine->getCurrentPosition());
        postLoopMachine->run(outputFileName);
    } while (loopMachine->getTape()[loopMachine->getCurrentPosition()] != '0'
    && loopMachine->getTape()[loopMachine->getCurrentPosition()] != 'n');

}

/**
* Constructor of a Loop Turing Machine by a given input file, calls the initializing method
*/
IterationLoopTuringMachine::IterationLoopTuringMachine(const std::string &fileName) {
    init(fileName);
}


IterationLoopTuringMachine::IterationLoopTuringMachine() {

}
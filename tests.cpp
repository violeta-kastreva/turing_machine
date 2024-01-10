#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <fstream>
#include <cstdlib>
#include <exception>
#include "turingmachine/machines/RegularTuringMachine.h"
#include "turingmachine/factory/TuringMachineFactory.h"
#include "turingmachine/tapevisualizer/TapeVisualizer.h"

std::string readFirstLine(const std::string& filename) {
    std::ifstream file(filename);
    std::string firstLine;
    if (file.is_open()) {
        std::getline(file, firstLine);
    }
    return firstLine;
}

TEST_CASE("Testing Factory Turing Machine") {
    auto* factory = new TuringMachineFactory();
    auto tm = factory->getMachine("../testFiles/regular.txt");
    tm->run("../testFiles/regular_output.txt");

    std::string expectedOutput = ">1001 ";
    REQUIRE(readFirstLine("../testFiles/regular_output.txt") == expectedOutput);
}

TEST_CASE("Testing Factory Composition Turing Machine") {
    auto* factory = new TuringMachineFactory();
    auto tm = factory->getMachine("../testFiles/composition2.txt");
    tm->run("../testFiles/composition_output_factory.txt");

    std::string expectedOutput = ">1001 ";
    REQUIRE(readFirstLine("../testFiles/composition_output_factory.txt") == expectedOutput);
}

TEST_CASE("Testing Conditional Composition Turing Machine") {
    auto* factory = new TuringMachineFactory();
    auto tm = factory->getMachine("../testFiles/conditional.txt");
    tm->run("../testFiles/conditional_output.txt");

    std::string expectedOutput = ">1 10";
    REQUIRE(readFirstLine("../testFiles/conditional_output.txt") == expectedOutput);
}

TEST_CASE("Testing Loop Turing Machine") {
    auto* factory = new TuringMachineFactory();
    auto tm = factory->getMachine("../testFiles/loop.txt");
    tm->run("../testFiles/loop_output.txt");

    std::string expectedOutput = ">01010 ";
    REQUIRE(readFirstLine("../testFiles/loop_output.txt") == expectedOutput);
}

//TEST_CASE("Testing Multitape Turing Machine") {
//    auto* factory = new TuringMachineFactory();
//    auto tm = factory->getMachine("../testFiles/multitape.txt");
//    tm->run("../testFiles/multitape_output.txt");
//}



TEST_CASE("Testing Tape Visualization") {
    // Assuming the tape file and expected output file paths are defined
    std::string tapeFilePath = "../testFiles/tape.txt";
    std::string outputGraphvizFilePath = "../testFiles/tape_graphviz.txt";

    // Create a dummy tape file for testing
    std::ofstream tapeFile(tapeFilePath);
    tapeFile << ">1001 "; // Sample tape content
    tapeFile.close();

    // Creating an instance of TapeVisualizer
    TapeVisualizer visualizer(tapeFilePath);

    // Use a try-catch block to catch any potential exceptions during file generation
    bool exceptionThrown = false;
    try {
        visualizer.generateGraphvizFile(outputGraphvizFilePath);
    } catch (const std::exception& e) {
        exceptionThrown = true;
    }

    // Check if no exceptions were thrown
    CHECK_FALSE(exceptionThrown);

    // Optionally, you can check if the output file exists and has content
    std::ifstream outputFile(outputGraphvizFilePath);
    CHECK(outputFile.good());
    std::string content;
    outputFile >> content;
    CHECK_FALSE(content.empty());
    outputFile.close();
}



TEST_CASE("Testing Tape Visualization with Graphviz") {
    std::string tapeFilePath = "../testFiles/tape.txt";
    std::string outputGraphvizFilePath = "../testFiles/tape_graphviz.dot";
    std::string outputPngFilePath = "../testFiles/tape_graphviz.png";

    // Create a dummy tape file for testing
    std::ofstream tapeFile(tapeFilePath);
    tapeFile << ">1001 "; // Sample tape content
    tapeFile.close();

    // Create an instance of TapeVisualizer and generate DOT file
    TapeVisualizer visualizer(tapeFilePath);
    bool exceptionThrown = false;
    try {
        visualizer.generateGraphvizFile(outputGraphvizFilePath);
    } catch (const std::exception& e) {
        exceptionThrown = true;
    }
    CHECK_FALSE(exceptionThrown);

    // Use the Graphviz dot tool to generate a PNG file from the DOT file
    std::string graphvizCommand = "dot -Tpng " + outputGraphvizFilePath + " -o " + outputPngFilePath;
    int result = std::system(graphvizCommand.c_str());

    // Check if the Graphviz command executed successfully
    CHECK(result == 0);

    // Optionally, check if the PNG file exists
    std::ifstream outputFile(outputPngFilePath);
    CHECK(outputFile.good());
    outputFile.close();
}

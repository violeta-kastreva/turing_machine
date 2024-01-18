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

TEST_CASE("Testing Regular Turing Machine") {
    auto* factory = new TuringMachineFactory();
    auto tm = factory->getMachine("../testFiles/input/basic_regular.txt");
    tm->run("../testFiles/output/basic_regular_output.txt");

    std::string expectedOutput = ">10";
    REQUIRE(readFirstLine("../testFiles/output/basic_regular_output.txt") == expectedOutput);
    delete factory;
}

TEST_CASE("Testing Complex Turing Machine") {
    auto* factory = new TuringMachineFactory();
    auto tm = factory->getMachine("../testFiles/input/regular.txt");
    tm->run("../testFiles/output/regular_output.txt");

    std::string expectedOutput = ">1001 ";
    REQUIRE(readFirstLine("../testFiles/output/regular_output.txt") == expectedOutput);
    delete factory;
}

TEST_CASE("Testing Composition Turing Machine") {
    auto* factory = new TuringMachineFactory();
    auto tm = factory->getMachine("../testFiles/input/composition.txt");
    tm->run("../testFiles/output/composition_output.txt");

    std::string expectedOutput = ">BBB BB";
    REQUIRE(readFirstLine("../testFiles/output/composition_output.txt") == expectedOutput);
    delete factory;
}

TEST_CASE("Testing Complex Composition Turing Machine") {
    auto* factory = new TuringMachineFactory();
    auto tm = factory->getMachine("../testFiles/input/composition2.txt");
    tm->run("../testFiles/output/composition_output_factory.txt");

    std::string expectedOutput = ">1001 ";
    REQUIRE(readFirstLine("../testFiles/output/composition_output_factory.txt") == expectedOutput);
    delete factory;
}

TEST_CASE("Testing Conditional Composition Turing Machine") {
    auto* factory = new TuringMachineFactory();
    auto tm = factory->getMachine("../testFiles/input/conditional.txt");
    tm->run("../testFiles/output/conditional_output.txt");

    std::string expectedOutput = ">1 10";
    REQUIRE(readFirstLine("../testFiles/output/conditional_output.txt") == expectedOutput);
    delete factory;
}

TEST_CASE("Testing Loop Turing Machine") {
    auto* factory = new TuringMachineFactory();
    auto tm = factory->getMachine("../testFiles/input/loop.txt");
    tm->run("../testFiles/output/loop_output.txt");

    std::string expectedOutput = ">01010 ";
    REQUIRE(readFirstLine("../testFiles/output/loop_output.txt") == expectedOutput);
    delete factory;
}

TEST_CASE("Testing Turing Machine with Wrong File Path") {
    TuringMachineFactory* factory = new TuringMachineFactory();
    CHECK_THROWS_WITH_AS(factory->getMachine("../testFiles/nonexistent/loop.txt"),
                         "Unable to open file: ../testFiles/nonexistent/loop.txt",
                         std::runtime_error);
    delete factory;
}


TEST_CASE("Testing Turing Machine with Invalid Machine Type") {
    TuringMachineFactory* factory = new TuringMachineFactory();
    CHECK_THROWS_AS(factory->getMachine("../testFiles/input/wrong_machine_type.txt"),
                    std::invalid_argument);
    delete factory;
}


TEST_CASE("Testing Tape Visualization with Graphviz") {
    std::string tapeFilePath = "../testFiles/tape/tape.txt";
    std::string outputGraphvizFilePath = "../testFiles/tape/tape_graphviz.dot";
    std::string outputPngFilePath = "../testFiles/tape/tape_graphviz.png";

    std::ofstream tapeFile(tapeFilePath);
    tapeFile << ">1001 ";
    tapeFile.close();

    TapeVisualizer visualizer(tapeFilePath);
    bool exceptionThrown = false;
    try {
        visualizer.generateGraphvizFile(outputGraphvizFilePath);
    } catch (const std::exception& e) {
        exceptionThrown = true;
    }
    CHECK_FALSE(exceptionThrown);

    std::ifstream outputFile(outputPngFilePath);
    CHECK(outputFile.good());
    outputFile.close();
}

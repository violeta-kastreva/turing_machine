#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "turingmachine/machines/regularturingmachine.h"
#include "turingmachine/factory/turingmachinefactory.h"
#include "turingmachine/machines/compositionturingmachine.h"
#include "turingmachine/machines/conditionalturingmachine.h"
#include "turingmachine/machines/iterationturingmachine.h"

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
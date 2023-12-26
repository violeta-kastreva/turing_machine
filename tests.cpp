#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "turingmachine/turingmachine.h"
#include "turingmachine/turingmachinefactory.h"
#include "turingmachine/compositionturingmachine.h"

TEST_CASE("Testing Basic Turing Machine") {
    TuringMachine tm("../testFiles/basic_regular.txt");
    tm.run("../testFiles/basic_regular_output.txt");
}

TEST_CASE("Testing Regular Turing Machine") {
    TuringMachine tm("../testFiles/regular.txt");
    tm.run("../testFiles/regular_output.txt");
}

TEST_CASE("Testing Factory Turing Machine") {
    auto* factory = new TuringMachineFactory();
    auto tm = factory->getMachine("../testFiles/regular.txt");
    tm->run("../testFiles/regular_output_factory.txt");
}

TEST_CASE("Testing Composition Turing Machine") {
    CompositionTuringMachine tm("../testFiles/composition2.txt");
    tm.run("../testFiles/composition_output.txt");
}

TEST_CASE("Testing Factory Composition Turing Machine") {
    auto* factory = new TuringMachineFactory();
    auto tm = factory->getMachine("../testFiles/composition2.txt");
    tm->run("../testFiles/composition_output_factory.txt");
}



#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "turingmachine/regularturingmachine.h"
#include "turingmachine/turingmachinefactory.h"
#include "turingmachine/compositionturingmachine.h"
#include "turingmachine/conditionalturingmachine.h"
#include "turingmachine/iterationturingmachine.h"

TEST_CASE("Testing Basic Turing Machine") {
    RegularTuringMachine tm("../testFiles/basic_regular.txt");
    tm.run("../testFiles/basic_regular_output.txt");
}

TEST_CASE("Testing Regular Turing Machine") {
    RegularTuringMachine tm("../testFiles/regular.txt");
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

TEST_CASE("Testing Conditional Composition Turing Machine") {
    ConditionalCompositionTuringMachine tm("../testFiles/conditional.txt");
    tm.run("../testFiles/conditional_output.txt");
}

TEST_CASE("Testing Loop Turing Machine") {
    IterationLoopTuringMachine tm("../testFiles/loop.txt");
    tm.run("../testFiles/loop_output.txt");
}
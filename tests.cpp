#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "turingmachine/machines/regularturingmachine.h"
#include "turingmachine/factory/turingmachinefactory.h"
#include "turingmachine/machines/compositionturingmachine.h"
#include "turingmachine/machines/conditionalturingmachine.h"
#include "turingmachine/machines/iterationturingmachine.h"


TEST_CASE("Testing Factory Turing Machine") {
    auto* factory = new TuringMachineFactory();
    auto tm = factory->getMachine("../testFiles/regular.txt");
    tm->run("../testFiles/regular_output.txt");
}
//
//TEST_CASE("Testing Composition Turing Machine") {
//    CompositionTuringMachine tm("../testFiles/composition2.txt");
//    tm.run("../testFiles/composition_output.txt");
//}

TEST_CASE("Testing Factory Composition Turing Machine") {
    auto* factory = new TuringMachineFactory();
    auto tm = factory->getMachine("../testFiles/composition2.txt");
    tm->run("../testFiles/composition_output_factory.txt");
}

TEST_CASE("Testing Conditional Composition Turing Machine") {
    auto* factory = new TuringMachineFactory();
    auto tm = factory->getMachine("../testFiles/conditional.txt");
    tm->run("../testFiles/conditional_output.txt");
}

TEST_CASE("Testing Loop Turing Machine") {
    auto* factory = new TuringMachineFactory();
    auto tm = factory->getMachine("../testFiles/loop.txt");
    tm->run("../testFiles/loop_output.txt");
}

//TEST_CASE("Testing Multitape Turing Machine") {
//    auto* factory = new TuringMachineFactory();
//    auto tm = factory->getMachine("../testFiles/multitape.txt");
//    tm->run("../testFiles/multitape_output.txt");
//}
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "turingmachine/turingmachine.h"
#include "turingmachine/turingmachinefactory.h"

TEST_CASE("Testing Basic Turing Machine") {
    TuringMachine tm("../testFiles/basic_regular.txt");
    tm.run("../testFiles/basic_regular_output.txt");

}

TEST_CASE("Testing Regular Turing Machine") {
    TuringMachine tm("../testFiles/regular.txt");
    tm.run("../testFiles/regular_output.txt");
}

TEST_CASE("Testing Factory Turing Machine") {
    TuringMachineFactory* factory = new TuringMachineFactory();
    auto tm = factory->getMachine("../testFiles/regular.txt");
    tm->run("../testFiles/regular_output_factory.txt");
}


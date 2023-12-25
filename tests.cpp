#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "TuringMachine.h"

TEST_CASE("Testing Basic Turing Machine") {
    TuringMachine tm("../testFiles/basic_regular.txt");
    tm.run("../testFiles/basic_regular_output.txt");

}

TEST_CASE("Testing Regular Turing Machine") {
    TuringMachine tm("../testFiles/regular.txt");
    tm.run("../testFiles/regular_output.txt");
}

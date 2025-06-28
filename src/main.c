#include <stdlib.h>
#include "TDD/tdd_macros.h"

#include "CHESS/test_chess.h"

RUN_TESTS(
    POPCNT_TEST_SUITE
)

int main(int argc, char** argv) {

    return (run_tests()) ? EXIT_FAILURE : EXIT_SUCCESS;

}

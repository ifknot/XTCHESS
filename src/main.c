#include <stdlib.h>
#include "TDD/tdd_macros.h"

//#include "CHESS/test_chess.h"
#include "BIOS/test_bios.h"


RUN_TESTS(
    //POPCNT_TEST_SUITE
    BIOS_VIDEO_TESTS
)

int main(int argc, char** argv) {

    return (run_tests()) ? EXIT_FAILURE : EXIT_SUCCESS;

}

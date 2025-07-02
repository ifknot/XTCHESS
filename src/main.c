#include <stdlib.h>
#include "TDD/tdd_macros.h"

//#include "CHESS/test_chess.h"
//#include "BIOS/test_bios.h"
#include "MDA/test_mda_context.h"

RUN_TESTS(
    //POPCNT_TEST_SUITE
    //BIOS_VIDEO_TESTS
    MDA_CONTEXT_TESTS
)

int main(int argc, char** argv) {

    return (run_tests()) ? EXIT_FAILURE : EXIT_SUCCESS;

}

cmake_minimum_required(VERSION 3.10)

# Warning: This skips critical compiler checks. Only use this if Watcom fails CMake's detection
# Necessary to suppress compiler checks for cross compilation using OW2 and C under ARM environments
set(CMAKE_C_COMPILER_WORKS 1)

project(
    statlib
    VERSION 0.1.0
    LANGUAGES C
)

# Ideally put in Toolchain-watcom.cmake
# set(CMAKE_TOOLCHAIN_FILE Toolchain-watcom.cmake)
# but for readability
set(CMAKE_SYSTEM_NAME DOS)      # Target DOS
set(CMAKE_C_COMPILER wcl)
set(CMAKE_CXX_COMPILER wcl)
set(CMAKE_LINKER wlink)         # Use Watcom's linker

# Watcom-specific flags
set(CMAKE_C_FLAGS "-bt=dos -l=dos")
set(CMAKE_EXE_LINKER_FLAGS "system dos")

# watcom compiler options
# https://users.pja.edu.pl/~jms/qnx/help/watcom/compiler-tools/cpopts.html
add_compile_options(
    -za99               # undocumented switch enable partial C99 compatibility
    -ml                 # memory model options - large model
    #-dNDEBUG
    #-ox         # Optimize for speed (optional)
    -bt=dos     # Target DOS
    -l=dos      # DOS library
)

# WARNING: Using GLOB for convenience. If adding new files, rerun:
#   ./cmk.sh
file(GLOB SOURCES
    CONFIGURE_DEPENDS
    *.c
    BIOS/*c
    CHESS/*.c
    MDA/*.c
    TDD/*.c
)

# message(Source list="${SOURCES}")

add_executable(chess ${SOURCES})

# Optional: Install target
install(TARGETS chess DESTINATION bin)

cmake_minimum_required(VERSION 3.5)

#suppress compiler checks for cross compilation using OW2 and C under ARM environments
set(CMAKE_C_COMPILER_WORKS 1)

project(
    statlib
    VERSION 0.1.0
    LANGUAGES C
)

# watcom compiler options
# https://users.pja.edu.pl/~jms/qnx/help/watcom/compiler-tools/cpopts.html
add_compile_options(
    -za99               # undocumented switch enable partial C99 compatibility
    -ml                 # memory model options - large model
    #-dNDEBUG
)

# Toolchain-watcom.cmake
set(CMAKE_SYSTEM_NAME DOS)  # Target DOS
set(CMAKE_C_COMPILER wcl)
set(CMAKE_CXX_COMPILER wcl)
set(CMAKE_LINKER wlink)  # Use Watcom's linker

# Watcom-specific flags
set(CMAKE_C_FLAGS "-bt=dos -l=dos")
set(CMAKE_EXE_LINKER_FLAGS "system dos")

file(GLOB SOURCES
    *.c
    BIOS/*c
    CHESS/*.c
    MDA/*.c
    TDD/*.c
)

message(Source list="${SOURCES}")

add_executable(chess ${SOURCES})

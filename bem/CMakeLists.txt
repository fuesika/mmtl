cmake_minimum_required (VERSION 2.6)
project("mmtl_bem")

enable_language(Fortran)
enable_language(CXX)


# g++
set (CMAKE_CXX_FLAGS_RELEASE "-O2 -g -Wall -Wextra")
#set (CMAKE_CXX_FLAGS_DEBUG   "-O0    -Wall -Wextra -Wshadow -fno-common -Werror -Wconversion -Wpointer-arith -Wcast-qual -Wcast-align -Wwrite-strings -fshort-enums -Wunused -Wuninitialized")
set (CMAKE_CXX_FLAGS_DEBUG   "-O0    -Wall -Wextra -Wshadow -fno-common -Werror -Wconversion                 -Wpointer-arith -Wcast-align -Wwrite-strings -fshort-enums -Wunused -Wuninitialized")

# gfortran
set (CMAKE_Fortran_FLAGS_RELEASE "-m64 -mcmodel=medium -O2 -cpp -ffree-line-length-0 -fopenmp -fno-realloc-lhs -fdefault-real-8")
set (CMAKE_Fortran_FLAGS_DEBUG   "-m64 -mcmodel=medium -O2 -cpp -ffree-line-length-0 -fopenmp -fno-realloc-lhs -fdefault-real-8")

# Debug is default
SET(CMAKE_BUILD_TYPE DEBUG CACHE STRING "default to debug")
# Provide compiler with build type information
add_definitions(-D__BUILDTYPE__=\"${CMAKE_BUILD_TYPE}\")

add_definitions(-DFORTRAN_UNDERBARS=1)

## Add source files to make-process ############################################
add_subdirectory(src)

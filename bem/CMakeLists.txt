cmake_minimum_required (VERSION 2.6)
project("mmtl_bem")

enable_language(Fortran)
enable_language(C)


# gfortran
set (CMAKE_Fortran_FLAGS_RELEASE "-m64 -mcmodel=medium -O2 -cpp -ffree-line-length-0 -fopenmp -fno-realloc-lhs")
set (CMAKE_Fortran_FLAGS_DEBUG   "-m64 -mcmodel=medium -fno-f2c  -fopenmp -O -g -ffree-line-length-0 -fimplicit-none -ffpe-trap=invalid,zero,overflow -fbounds-check -cpp -Wall -fbacktrace -Wuninitialized -fno-realloc-lhs -Wconversion-extra -Wextra -Wno-maybe-uninitialized -Wcharacter-truncation -faggressive-function-elimination -Wfunction-elimination -pedantic")
message(STATUS "Using gfortran")

# Debug is default
SET(CMAKE_BUILD_TYPE DEBUG CACHE STRING "default to debug")
# Provide compiler with build type information
add_definitions(-D__BUILDTYPE__=\"${CMAKE_BUILD_TYPE}\")

add_definitions(-DFORTRAN_UNDERBARS=1)

## Add source files to make-process ############################################
add_subdirectory(src)

cmake_minimum_required(VERSION 3.5)
project (AMazing VERSION 1.0.0 LANGUAGES CXX )

# Currently CMake (since 2.8.5) supports generation of compilation databases
# for Unix Makefile builds (Ninja builds in the works) with the option
# CMAKE_EXPORT_COMPILE_COMMANDS.
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

#=== FINDING PACKAGES ===#

#=== SETTING VARIABLES ===#
# Compiling flags
set( GCC_COMPILE_FLAGS "-Wall" )
set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COMPILE_FLAGS} ${PREPROCESSING_FLAGS}" )


#=== Main App ===
set( APP_NAME "amazing" )
include_directories( "core" )
# The sources.
add_executable(${APP_NAME}
    core/main.cpp
    core/maze.cpp)
# Choosing C++ version
target_compile_features( ${APP_NAME} PUBLIC cxx_std_11 )

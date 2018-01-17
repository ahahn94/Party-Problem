cmake_minimum_required(VERSION 3.8)
project(PartyProblem)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp Guest.cpp Guest.h main.h)
add_executable(PartyProblem ${SOURCE_FILES})
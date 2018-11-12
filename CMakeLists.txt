cmake_minimum_required(VERSION 3.12.0)

project(modern-cpp-challenge)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# project options
option(MCC_BUILD_TESTS "Turn on to build unit tests." ON)

if(MCC_BUILD_TESTS)
    find_package(GTest REQUIRED)
endif(MCC_BUILD_TESTS)

add_subdirectory(language-features)
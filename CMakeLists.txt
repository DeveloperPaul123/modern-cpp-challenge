cmake_minimum_required(VERSION 3.12.0)

project(modern-cpp-challenge)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# project options
option(MCC_BUILD_TESTS "Turn on to build unit tests." ON)
option(MCC_BUILD_DOCUMENTATION "Turn on to build documentation." OFF)

if(MCC_BUILD_TESTS)
    find_package(GTest REQUIRED)
endif(MCC_BUILD_TESTS)

if(MCC_BUILD_DOCUMENTATION)
    find_package(Doxygen REQUIRED doxygen OPTIONAL_COMPONENTS dot)
    set(documentation_dirs "language-features")
    doxygen_add_docs(documentation 
        ${documentation_dirs})
endif(MCC_BUILD_DOCUMENTATION)

add_subdirectory(language-features)
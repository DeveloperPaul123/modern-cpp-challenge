cmake_minimum_required(VERSION 3.12.0)

project(modern-cpp-challenge)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# project options
option(MCC_BUILD_TESTS "Turn on to build unit tests." ON)
option(MCC_BUILD_DOCUMENTATION "Turn on to build documentation." OFF)

if(MCC_BUILD_TESTS)
    set(CPM_DOWNLOAD_LOCATION "${CMAKE_BINARY_DIR}/cmake/CPM.cmake")
    set(CPM_VERSION 0.12)

    if(NOT EXISTS ${CPM_DOWNLOAD_LOCATION})
    message(STATUS "Downloading CPM.cmake")
    file(DOWNLOAD https://raw.githubusercontent.com/TheLartians/CPM/v${CPM_VERSION}/cmake/CPM.cmake ${CPM_DOWNLOAD_LOCATION})
    endif(NOT EXISTS ${CPM_DOWNLOAD_LOCATION})

    include(${CPM_DOWNLOAD_LOCATION})

    CPMAddPackage(
        NAME googletest
        GITHUB_REPOSITORY google/googletest
        GIT_TAG release-1.8.1
        VERSION 1.8.1
        OPTIONS
            "INSTALL_GTEST OFF"
            "gtest_force_shared_crt ON"
    )

    add_library(GTest::GTest ALIAS gtest)
    add_library(GTest::Main ALIAS gtest_main)
endif(MCC_BUILD_TESTS)

if(MCC_BUILD_DOCUMENTATION)
    find_package(Doxygen REQUIRED doxygen OPTIONAL_COMPONENTS dot)
    set(documentation_dirs "language-features")
    doxygen_add_docs(documentation 
        ${documentation_dirs})
endif(MCC_BUILD_DOCUMENTATION)

add_subdirectory(language-features)
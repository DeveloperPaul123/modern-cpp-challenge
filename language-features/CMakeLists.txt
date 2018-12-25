cmake_minimum_required(VERSION 3.12.0)

project(language-features)
include(ProjectHelpers)

set(ip_address_headers 
    include/ip_address.h
)

set(ip_address_sources
    src/ip_address.cpp)

set(ip_address_tests 
    test/ip_address_tests.cpp)

add_mcc_library(ip-address ${ip_address_sources} ${ip_address_headers} ${ip_address_tests})

set(matrix_headers include/matrix.h)
set(matrix_test test/matrix_tests.cpp)

add_mcc_header_library(matrix ${matrix_headers} ${matrix_test})
target_include_directories(matrix 
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)
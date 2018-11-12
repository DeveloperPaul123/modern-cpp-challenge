cmake_minimum_required(VERSION 3.12.0)

project(language-features)

set(ip_address_headers 
    include/ip_address.h)

set(ip_address_sources
    src/ip_address.cpp)

set(ip_address_tests 
    test/ip_address_tests.cpp)

include(ProjectHelpers)

add_mcc_library(ip-address ${ip_address_sources} ${ip_address_headers} ${ip_address_tests})
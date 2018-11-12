
function(add_mcc_library target_name sources headers tests)

add_library(${target_name} ${headers} ${sources})
target_include_directories(${target_name} PUBLIC include)

if(MCC_BUILD_TESTS)
    set(target_test_name "${target_name}.tests")
    add_executable(${target_test_name} ${tests})
    target_link_libraries(${target_test_name} 
        PUBLIC 
            GTest::GTest 
            GTest::Main 
            ${target_name})

endif(MCC_BUILD_TESTS)

endfunction()
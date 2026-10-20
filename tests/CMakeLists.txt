create_executable_project(tests)
target_link_libraries(tests gtest gtest_main)
add_test(NAME TESTS COMMAND TESTS)
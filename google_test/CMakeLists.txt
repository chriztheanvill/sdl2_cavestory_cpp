cmake_minimum_required(VERSION 3.16.3)

set(SOURCES test_file.cpp)

add_executable(GoogleTest_test ${SOURCES})

## This is when it will used on the libs

target_link_libraries(GoogleTest_test PUBLIC
	gtest_main
	Engine
)

add_test(
	NAME GoogleTest_test
	COMMAND GoogleTest_test
)
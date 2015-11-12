cmake_minimum_required(VERSION 2.8.4)
project(Test)

enable_testing()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

set(GTEST_DIR ../third-party/gtest-1.7.0)
set(GMOCK_DIR ../third-party/googlemock-1.7.0)

file(GLOB TESTS_FILES *.cpp)
file(GLOB SRC_FILES ../src/*.cpp)
file(GLOB DEP_FILES deps/*.cpp)

include_directories(
	deps
	../src
    ${GTEST_DIR}
    ${GTEST_DIR}/include
	${GMOCK_DIR}
    ${GMOCK_DIR}/include)

add_definitions(-DGTEST_HAS_PTHREAD=0)

add_executable(Tests
    ${TESTS_FILES}
	${SRC_FILES}
	${DEP_FILES}
    ${GTEST_DIR}/src/gtest-all.cc
	${GMOCK_DIR}/src/gmock-all.cc
    ${GMOCK_DIR}/src/gmock_main.cc)

target_link_libraries(Tests)

add_test(Test ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Tests)

cmake_minimum_required(VERSION 3.3)
project(diht_prog_sem4_task2_1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES CSyncContainer)
#add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Setup testing
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})
set(PROJECT_TEST_NAME diht_prog_sem4_task2_1_test)

add_executable(${PROJECT_TEST_NAME} testCSyncContainer ${SOURCE_FILES})

target_link_libraries(diht_prog_sem4_task2_1_test gtest gtest_main)
add_test(tests diht_prog_sem4_task2_1_test)
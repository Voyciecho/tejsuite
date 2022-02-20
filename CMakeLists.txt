cmake_minimum_required (VERSION 3.10)
project (TestExperimentenJoySuite VERSION 1.0)
set(CMAKE_CXX_STANDARD 11)

enable_testing()

add_subdirectory(googletest)
set(GTEST_INCLUDE_DIR googletest/googletest/include)
set(GTEST_LIBRARY googletest)
set(GTEST_MAIN_LIBRARY googletest)
include_directories(googletest googletest/googletest/include googletest/googlemock/include)

find_package(Threads REQUIRED)
find_package(GTest REQUIRED)

add_subdirectory(src)

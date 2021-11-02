cmake_minimum_required(VERSION 3.16)
project(DZ1)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage")
set(CMAKE_C_FLAGS "-g -O0 -Wall -W -fprofile-arcs -ftest-coverage")
set(CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")

file(GLOB SOURCE "${PROJECT_SOURCE_DIR}/bodies/*.c")
add_library(my_lib STATIC ${SOURCE})

target_include_directories(my_lib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/headers)

# main
add_executable(main
        ${CMAKE_CURRENT_SOURCE_DIR}/main.c)

target_include_directories(main PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/headers)

target_link_libraries(main my_lib)

# gtest
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

file(GLOB TESTS "${PROJECT_SOURCE_DIR}/tests/*.cpp")
add_executable(test_country ${TESTS})

target_include_directories(test_country PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/headers)
target_link_libraries(test_country gtest_main my_lib)

include(GoogleTest)
gtest_discover_tests(test_country)

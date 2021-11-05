cmake_minimum_required(VERSION 3.16)
project(DZ2)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage -Werror")
set(CMAKE_C_FLAGS "-g -O0 -Wall -W -fprofile-arcs -ftest-coverage -Werror")
set(CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage -pthread")

option(USE_STATIC "Use static library" ON)
message(STATUS "Compile with static library? ${USE_STATIC}")

add_executable(main main.c)

add_library(_file STATIC file_lib/file.c)
target_include_directories(_file PUBLIC ${PROJECT_SOURCE_DIR}/file_lib/)

target_link_libraries(main _file)

add_library(_consist SHARED library/consist.c)
target_include_directories(_consist PUBLIC ${PROJECT_SOURCE_DIR}/library/)

add_library(_parallel STATIC library/parallel.c)
target_include_directories(_parallel PUBLIC ${PROJECT_SOURCE_DIR}/library/)

if(USE_STATIC)
    target_link_libraries(main _consist)
else()
    target_link_libraries(main _parallel) 

endif()

#add_executable(cd create_double.c)
# gtest
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()



add_executable(consist_test tests/main_test.cpp tests/consist_tests.cpp)
target_include_directories(consist_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/library)
target_link_libraries(consist_test gtest_main _consist)

add_executable(parallel_test ${consist_lib_test} tests/parallel_tests.cpp)
target_include_directories(parallel_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/library)
target_link_libraries(parallel_test gtest_main _parallel)

add_executable(file_lib_test tests/file_tests.cpp tests/main_test.cpp)
target_include_directories(file_lib_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/file_lib)
target_link_libraries(file_lib_test gtest_main _file)

include(GoogleTest)
gtest_discover_tests(consist_test parallel_test file_lib_test)

cmake_minimum_required(VERSION 3.0.0)
project(TestBed VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(TestBed testBed/src/main.cpp)

find_package(Threads REQUIRED)
target_compile_options(TestBed PUBLIC -std=c++20)
# Useful to output intermediate assembly and preprocessed code.
# target_compile_options(TestBed PRIVATE -save-temps -fverbose-asm)
target_link_libraries(TestBed Threads::Threads)
target_link_options(TestBed PRIVATE -fuse-ld=gold -flto)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

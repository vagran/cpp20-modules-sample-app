cmake_minimum_required(VERSION 3.10)

project(water_valve)

set(CMAKE_VERBOSE_MAKEFILE ON)

file(GLOB_RECURSE SOURCES "impl/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.h")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcoroutines-ts -fmodules -stdlib=libc++ -std=c++20")
include_directories("include")

add_executable(${CMAKE_PROJECT_NAME} ${SOURCES} ${HEADERS})

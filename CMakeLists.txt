cmake_minimum_required(VERSION 3.1)
project(abz)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(abz SHARED src/chrono/thread_clock.cpp)
target_include_directories(abz PUBLIC include)

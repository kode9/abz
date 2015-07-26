cmake_minimum_required(VERSION 3.1)

add_library(abz SHARED src/chrono/thread_clock.cpp)
target_include_directories(abz PUBLIC include)
set_target_properties(abz PROPERTIES
  CXX_STANDARD 11
  CXX_EXTENSIONS OFF
  CXX_STANDARD_REQUIRED ON)

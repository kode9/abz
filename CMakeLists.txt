# Copyright (C) 2015, 2016 Pierre-Luc Perrier <pluc-dev@the-pluc.net>
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
cmake_minimum_required(VERSION 3.1)
project(abz VERSION 0.1.0 LANGUAGES CXX)


add_library(abz SHARED src/chrono/thread_clock.cpp)
set_target_properties(abz PROPERTIES
  CXX_STANDARD 11
  CXX_STANDARD_REQUIRED ON
  CXX_EXTENSIONS OFF)
target_compile_features(abz PUBLIC cxx_variable_templates)

target_include_directories(abz PUBLIC include)

# This file is part of RML 
# RML is licensed under the MIT LICENSE. See the LICENSE file for more info.

cmake_minimum_required(VERSION 2.8)
project(RML)

# Set up CMAKE settings
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_INSTALL_PREFIX "")

list(APPEND CMAKE_CXX_FLAGS "-std=c++11 -Wall -pedantic") 

# File all .cc files in the source dir and helpers dir
file(GLOB_RECURSE SOURCES "src/*.cc")

# Setup include path for the lib
include_directories(${CMAKE_SOURCE_DIR})

# Build the lib using the cc files found above.
add_executable(rml ${SOURCES})
target_link_libraries(rml pthread)

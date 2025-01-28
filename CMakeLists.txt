cmake_minimum_required(VERSION 3.25)
project(logger)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/out/lib/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/out/bin/)
include_directories(src)

add_library(
        logger STATIC
        src/logger.cpp
        src/logger.hpp
)

add_executable(
        example
        src/logger.cpp
        src/logger.hpp
        src/example/example.cpp
)
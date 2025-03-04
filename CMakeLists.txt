cmake_minimum_required(VERSION 3.25)
project(ssbl)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/out/lib/${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}-${CMAKE_BUILD_TYPE})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/out/bin/${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}-${CMAKE_BUILD_TYPE})
include_directories(src include)

set(
    LIBRARY_SOURCES
    src/Logger.cpp
    include/Logger.hpp
    include/Time.hpp
    src/Time.cpp
    include/Format.hpp
    src/Format.cpp
    include/Log.hpp
    src/Log.cpp
    include/Convert.hpp
    src/Convert.cpp
    include/StringOps.hpp
    src/StringOps.cpp
)

add_library(logger STATIC ${LIBRARY_SOURCES})
add_executable(example ${LIBRARY_SOURCES} src/example/example.cpp)
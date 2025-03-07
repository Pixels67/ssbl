cmake_minimum_required(VERSION 3.25)
project(ssbl)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/out/lib/${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}-${CMAKE_BUILD_TYPE})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/out/bin/${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}-${CMAKE_BUILD_TYPE})
include_directories(src include)

set(
    LIBRARY_SOURCES
    include/Logger.hpp
    src/Logger.cpp
    include/String.hpp
    src/String.cpp
    include/Convert.hpp
    src/Convert.cpp
    include/Time.hpp
    src/Time.cpp
    include/Format.hpp
    src/Format.cpp
    include/Console.hpp
    src/Console.cpp
)

add_library(ssbl STATIC ${LIBRARY_SOURCES})
add_executable(example src/Examples/Example.cpp)

target_link_libraries(example ssbl)
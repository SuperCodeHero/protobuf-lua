cmake_minimum_required(VERSION 3.14)
project(protobuf_lua)

set(CMAKE_CXX_STANDARD 17)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/out)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/out)

add_subdirectory(api)
add_executable(protobuf_lua main.cpp)

target_link_libraries(protobuf_lua api)
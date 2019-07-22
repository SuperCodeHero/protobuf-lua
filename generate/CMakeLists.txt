cmake_minimum_required(VERSION 3.14)
project(generate)

aux_source_directory(. SRC_FILES)

add_executable(generate ${SRC_FILES})
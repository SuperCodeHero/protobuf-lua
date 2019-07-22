cmake_minimum_required(VERSION 3.14)

aux_source_directory(. SRC_FILES)

include_directories("../lua-5.3.5/src")

add_library(api SHARED ${SRC_FILES})
target_link_libraries(api lua5.3)
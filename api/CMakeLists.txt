cmake_minimum_required(VERSION 3.14)

aux_source_directory(. SRC_FILES)

add_library(api SHARED ${SRC_FILES})
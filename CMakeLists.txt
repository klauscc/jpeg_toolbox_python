cmake_minimum_required(VERSION 2.8)

add_library(extract_dct SHARED jpeg_read.c )
target_link_libraries(extract_dct jpeg)
add_executable(test_jpeg_read test_jpeg_read.c)
target_link_libraries(test_jpeg_read extract_dct)
add_subdirectory(python)

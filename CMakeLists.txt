cmake_minimum_required(VERSION 2.8)


find_package(JPEG)
include_directories(BEFORE ${JPEG_INCLUDE_DIR})
link_directories(${JPEG_LIBRARIES})
message(${JPEG_INCLUDE_DIR}, ${JPEG_LIBRARIES})

add_library(extract_dct SHARED jpeg_read.c )
target_link_libraries(extract_dct ${JPEG_LIBRARIES})
add_executable(test_jpeg_read test_jpeg_read.c)
target_link_libraries(test_jpeg_read extract_dct)
add_custom_command(TARGET extract_dct POST_BUILD
								COMMAND cp $<TARGET_LINKER_FILE:extract_dct> "${PROJECT_SOURCE_DIR}/python/jpegtools"
								)

add_subdirectory(python)

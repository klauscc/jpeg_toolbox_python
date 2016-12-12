find_package(Boost REQUIRED python)
FIND_PACKAGE(PythonLibs 2.7 REQUIRED)
include_directories(${PROJECT_SOURCE_DIR} ${PYTHON_INCLUDE_DIR}  ${NUMPY_INCLUDE_DIR} ${Boost_INCLUDE_DIRS})
add_library(jpegtools SHARED jpegtools.cpp)
target_link_libraries(jpegtools extract_dct ${PYTHON_LIBRARIES} ${Boost_LIBRARIES})
set_target_properties(jpegtools PROPERTIES PREFIX "" OUTPUT_NAME "_jpegtools")
target_link_libraries(jpegtools extract_dct ${PYTHON_LIBRARIES} ${Boost_LIBRARIES})

set(__linkname "${PROJECT_SOURCE_DIR}/python/jpegtools/_jpegtools.so")
add_custom_command(TARGET jpegtools POST_BUILD
								COMMAND ln -sf $<TARGET_LINKER_FILE:jpegtools> "${__linkname}"
								)

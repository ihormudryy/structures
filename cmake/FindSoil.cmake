add_subdirectory(${EXTERNAL_SOURCE_DIR}/soil ${CMAKE_BINARY_DIR}/soil)
include_directories(${EXTERNAL_SOURCE_DIR}/soil/src)
set(SOIL_FOUND true PARENT_SCOPE)
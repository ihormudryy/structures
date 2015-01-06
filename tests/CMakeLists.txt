project(unittests)

set(GMOCK_SOURCE_DIR "${CMAKE_SOURCE_DIR}/3rd_party/gmock-1.7.0")

set(GMOCK_SOURCES
    "${GMOCK_SOURCE_DIR}/gtest/fused-src/gtest/gtest-all.cc"
    "${GMOCK_SOURCE_DIR}/gtest/fused-src/gtest/gtest_main.cc"
)

set(GTEST
    ${GMOCK_SOURCE_DIR}/gtest/include
    ${GMOCK_SOURCE_DIR}/include
)

set(CUSTOM_ALGORYTHMS_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

file(GLOB_RECURSE TEST_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/unittests/*.h")
file(GLOB_RECURSE TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/unittests/*.cpp")

set(SOURCES
    ${GMOCK_SOURCES}
    ${TEST_HEADERS}
    ${TEST_SOURCES}
)

include_directories(
    ${CUSTOM_ALGORYTHMS_INCLUDE_DIR}
    ${GTEST}
)

add_executable(unittests ${SOURCES})

target_link_libraries(
  unittests
	gmock
	structures
)

if(WIN32)
   
    if (CMAKE_BUILD_TYPE  STREQUAL "Release")
        set (BUILD "Release")
    else()
        set (BUILD "Debug")
    endif()
    execute_process(COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/tests/data 
                               ${PROJECT_BINARY_DIR}/${BUILD}/data
                    )
else()
    execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_SOURCE_DIR}/tests/data
														   ${PROJECT_BINARY_DIR}/data
    )
endif()
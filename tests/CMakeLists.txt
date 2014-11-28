project(unittests)

set(GMOCK_SOURCE_DIR "${CMAKE_SOURCE_DIR}/libs/gmock-1.7.0")

set(GMOCK_SOURCES
    "${GMOCK_SOURCE_DIR}/fused-src/gmock-gtest-all.cc"
    "${GMOCK_SOURCE_DIR}/fused-src/gmock_main.cc"
)

set(GTEST
    ${GMOCK_SOURCE_DIR}/gtest/include
    ${GMOCK_SOURCE_DIR}/gtest/include/gtest
)

set(GMOCK "${GTEST_HEADERS}"
    ${GMOCK_SOURCE_DIR}/include
    ${GMOCK_SOURCE_DIR}/include/gmock
)

file(GLOB_RECURSE GMOCK_HEADERS GMOCK)
file(GLOB_RECURSE GTEST_HEADERS GTEST)

set(GTEST_LIBRARIES
    ${GTEST_HEADERS}
    ${GMOCK_HEADERS}
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
    ${GMOCK}
)

add_executable(unittests ${SOURCES})

target_link_libraries(
    unittests
    ${GTEST_LIBRARIES}
)

project(testtools)

set(GLM
    ${CMAKE_SOURCE_DIR}/3rd_party/glm/glm
)

set(SOIL_DIR ${CMAKE_SOURCE_DIR}/3rd_party/soil)
file(GLOB_RECURSE SOIL_HEADERS "${SOIL_DIR}/*.*")
set(SOIL ${SOIL_HEADERS} ${SOIL_SOURCES} )

file(GLOB_RECURSE TEST_TOOLS_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
file(GLOB_RECURSE TEST_TOOLS_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

set(TOOLS_SOURCES
    ${TEST_TOOLS_HEADERS}
    ${TEST_TOOLS_SOURCES}
    ${GLM}
    ${SOIL}
)

include_directories(
	${GLM}
	${CMAKE_CURRENT_SOURCE_DIR}
)

add_library(testtools ${TOOLS_SOURCES})

target_link_libraries(
    testtools
)

set(TEST_TOOLS_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
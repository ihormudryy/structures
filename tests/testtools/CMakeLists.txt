project(Structures.TestTools)

if(NOT SOIL_FOUND)
	find_package(Soil REQUIRED)
endif()

if(NOT GLM_FOUND)
    find_package(Glm REQUIRED)
endif()

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
file(GLOB_RECURSE HEADERS "${INCLUDE_DIR}/*.h")
file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

set(ALL_SOURCES
    ${HEADERS}
    ${SOURCES}
)

add_library(${PROJECT_NAME} ${ALL_SOURCES})

target_include_directories(${PROJECT_NAME}
    PUBLIC ${INCLUDE_DIR}
    PRIVATE ${GLM_INCLUDE_DIRS}
    PRIVATE ${SOIL_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME}
    SOIL
)
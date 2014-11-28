project(structures)

file(GLOB_RECURSE HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/../include/*.h")
file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

set(SOURCES
    ${HEADERS}
    ${SOURCES}
)

include_directories(
    "${CMAKE_CURRENT_SOURCE_DIR}/../include"
)

add_executable(structures ${SOURCES})

target_link_libraries(
    structures
)

install(DIRECTORY ../include DESTINATION "${CMAKE_INSTALL_PREFIX}" COMPONENT dev)

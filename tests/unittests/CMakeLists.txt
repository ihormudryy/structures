project(unittests)

#find_package(TestTools REQUIRED)

set(GMOCK_SOURCE_DIR "${CMAKE_SOURCE_DIR}/3rd_party/gmock-1.7.0")

set(GMOCK_SOURCES
    "${GMOCK_SOURCE_DIR}/gtest/fused-src/gtest/gtest-all.cc"
    "${GMOCK_SOURCE_DIR}/gtest/fused-src/gtest/gtest_main.cc"
)

set(GTEST
    ${GMOCK_SOURCE_DIR}/gtest/include
    ${GMOCK_SOURCE_DIR}/include
)

set(GLM
    ${CMAKE_SOURCE_DIR}/3rd_party/glm/glm
)

set(CUSTOM_ALGORYTHMS_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

file(GLOB_RECURSE TEST_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
file(GLOB_RECURSE TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

set(SOURCES
    ${GMOCK_SOURCES}
    ${TEST_HEADERS}
    ${TEST_SOURCES}
    ${GLM}
)

if (EMSCRIPTEN)
    include_directories(
        ${CUSTOM_ALGORYTHMS_INCLUDE_DIR}
        ${GTEST}
        ${GLM}
        ${EMSC_INCLUDE}
        ${LIBCXXABI_INCLUDE}
    )

    add_executable(unittests ${SOURCES})

    target_link_libraries(
        unittests
        gmock
        structures
        ${EMSCRIPTEN_LIBS}
    )

elseif (ANDROID)
    set(EXTRA_PLATFORM_LIBRARIES android)
    set(ANDROID_GLUE "${CMAKE_SOURCE_DIR}/apps/android_tmp/app_glue.cpp")
    set(ANDROID_SOURCES
        ${GMOCK_SOURCES}
        ${TEST_HEADERS}
        ${TEST_SOURCES}
        ${TEST_TOOLS_HEADERS}
        ${ANDROID_GLUE}
    )

    add_library(unittests SHARED ${ANDROID_SOURCES})

    include_directories(
        ${CUSTOM_ALGORYTHMS_INCLUDE_DIR}
        ${GTEST}
        ${GLM}
        ${TEST_HEADERS}
        ${TEST_SOURCES}
        ${GMOCK_SOURCES}
        ${GMOCK_SOURCE_DIR}
    )

    set(ANDROID_TESTS ${ANDROID_TESTS} unittests PARENT_SCOPE)

    target_link_libraries(
        unittests
        gmock
        glm
        structures
        ${EXTRA_PLATFORM_LIBRARIES}
    )
    
    create_apk(unittests debug)
else()
    include_directories(
        ${CUSTOM_ALGORYTHMS_INCLUDE_DIR}
        ${GTEST}
        ${GLM}
        /usr/include
#        /usr/include/GLES2
    )

    link_directories(/usr/X11R6/lib)
    SET(EXTRA_LIBS GL X11)

    add_executable(unittests ${SOURCES})

    target_link_libraries(
        unittests
        gmock
        structures
        testtools
        ${EXTRA_LIBS}
    )
endif()

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

set_property(TARGET unittests PROPERTY FOLDER tests/unittests)
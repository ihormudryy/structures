project(Structures.UnitTests)

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

    add_executable(${PROJECT_NAME} ${SOURCES})

    target_link_libraries(
        ${PROJECT_NAME}
        gmock
        Structures
        ${EMSCRIPTEN_LIBS}
    )
endif()

if (ANDROID)
    set(EXTRA_PLATFORM_LIBRARIES android)
    set(ANDROID_GLUE "${CMAKE_SOURCE_DIR}/apps/android_unittest/app_glue.cpp")
    set(ANDROID_SOURCES
        ${GMOCK_SOURCES}
        ${TEST_HEADERS}
        ${TEST_SOURCES}
        ${TEST_TOOLS_HEADERS}
        ${ANDROID_GLUE}
    )

    add_library(${PROJECT_NAME} SHARED ${ANDROID_SOURCES})

    include_directories(
        ${CUSTOM_ALGORYTHMS_INCLUDE_DIR}
        ${GTEST}
        ${GLM}
        ${TEST_HEADERS}
        ${TEST_SOURCES}
        ${GMOCK_SOURCES}
        ${GMOCK_SOURCE_DIR}
    )

    set(ANDROID_TESTS ${ANDROID_TESTS} ${PROJECT_NAME} PARENT_SCOPE)

    target_link_libraries(
        ${PROJECT_NAME}
        gmock
        glm
        Structures
        ${EXTRA_PLATFORM_LIBRARIES}
    )
    
    create_apk(${PROJECT_NAME} debug)
endif()

if ((NOT ANDROID) AND (NOT EMSCRIPTEN))
    include_directories(
        ${CUSTOM_ALGORYTHMS_INCLUDE_DIR}
        ${GTEST}
        ${GLM}
        /usr/include
        /usr/include/GLES2
    )

    link_directories(/usr/X11R6/lib)
    SET(EXTRA_LIBS GL X11)

    add_executable(${PROJECT_NAME} ${SOURCES})

    target_link_libraries(
        ${PROJECT_NAME}
        gmock
        Structures
        Structures.TestTools
        ${EXTRA_LIBS}
    )
endif()

if(WIN32)
    if (CMAKE_BUILD_TYPE  STREQUAL "Release")
        set (BUILD "Release")
    else()
        set (BUILD "Debug")
    endif()
    execute_process(COMMAND ${CMAKE_COMMAND} -E copy_directory 
        ${CMAKE_SOURCE_DIR}/tests/data 
        ${PROJECT_BINARY_DIR}/${BUILD}/data
    )
else()
    execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink 
        ${CMAKE_SOURCE_DIR}/tests/data
        ${PROJECT_BINARY_DIR}/data
    )
endif()

#Add tests to "test" package
if (ANDROID)
    create_apk(${PROJECT_NAME} debug)
    #install(TARGETS Structures.UnitTests
    #    ARCHIVE DESTINATION "${CMAKE_INSTALL_PREFIX}/tests/geoviz"
    #    LIBRARY DESTINATION "${CMAKE_INSTALL_PREFIX}/tests/geoviz"
    #    COMPONENT tests
    #)
else()
    install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION "${CMAKE_INSTALL_PREFIX}/tests/Structures.UnitTests"
        COMPONENT tests
    )
endif()

#Add test to ctest test runner
if(EMSCRIPTEN)
    add_test(Structures.UnitTests node ${PROJECT_NAME})
else()
    foreach(testFile ${TEST_SOURCES})
        get_filename_component(testName ${testFile} NAME_WE)
        add_test(${testName} ${PROJECT_NAME})
    endforeach()
endif()

set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER tests/${PROJECT_NAME})
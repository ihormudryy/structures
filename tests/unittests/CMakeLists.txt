project(Structures.UnitTests)

if(NOT GTEST_FOUND)
    find_package(Gtest REQUIRED)
endif()

if(NOT GLM_FOUND)
    find_package(Glm REQUIRED)
endif()

set(CUSTOM_ALGORYTHMS_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

set(INCLUDES ${CMAKE_CURRENT_SOURCE_DIR})
file(GLOB_RECURSE HEADERS "${INCLUDES}/*.h")
file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

set(ALL_SOURCES
    ${HEADERS}
    ${SOURCES}
)

set(PLATFORM_SPECIFIC)
set(EXTRA_PLATFORM_LIBRARIES)

if (EMSCRIPTEN)
    set(PLATFORM_SPECIFIC 
        ${EMSC_INCLUDE}
        ${LIBCXXABI_INCLUDE}
    )
endif()

if (ANDROID)
    set(EXTRA_PLATFORM_LIBRARIES android)
    set(ANDROID_GLUE "${CMAKE_SOURCE_DIR}/apps/android_unittest/app_glue.cpp")
    set(ALL_SOURCES
        ${ANDROID_GLUE}
        ${ALL_SOURCES}
    )
endif()

if(UNIX)
    set(PLATFORM_SPECIFIC 
        /usr/include
        /usr/include/GLES2
    )
    set(EXTRA_PLATFORM_LIBRARIES
        GL
        X11
    )
endif()

if (ANDROID)
    add_library(${PROJECT_NAME} SHARED ${ALL_SOURCES})
else()
    add_executable(${PROJECT_NAME} ${ALL_SOURCES})
endif()

target_include_directories(${PROJECT_NAME}
    PUBLIC ${INCLUDES}
    PUBLIC ${CUSTOM_ALGORYTHMS_INCLUDE_DIR}
    PRIVATE ${TESTTOOLS_INCLUDE_DIR}
    PRIVATE ${PLATFORM_SPECIFIC}
)

target_link_libraries(${PROJECT_NAME}
    ${EXTRA_PLATFORM_LIBRARIES}
    gtest_main
    Structures
    Structures.TestTools
)

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
if(NOT ANDROID)
    install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION "${CMAKE_INSTALL_PREFIX}/tests/${PROJECT_NAME}"
        COMPONENT tests
    )
endif()

#Add test to ctest test runner
if(EMSCRIPTEN)
    add_test(Structures.UnitTests node ${PROJECT_NAME})
else()
    foreach(testFile ${SOURCES})
        get_filename_component(testName ${testFile} NAME_WE)
        add_test(${testName} ${PROJECT_NAME})
    endforeach()
endif()

set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER tests/unitests)

if(ANDROID)
    create_apk(${PROJECT_NAME} debug)
endif()
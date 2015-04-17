cmake_minimum_required(VERSION 2.8.11)

option(CODE_COVERAGE "Enable code coverage option" OFF)
option(EMSCRIPTEN "Emscripten crosscompilation mode " OFF)
option(ANDROID "Build Android aplication" OFF)
option(WARNINGS "Build project with warnings enabled" ON)
option(BUILD_TESTS "Create project files for building the unit tests" ON)

set(VERSION_MAJOR "0")
set(VERSION_MINOR "0")
set(VERSION_PATCH "1")
set(PACKAGE_VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
set(EXTERNAL_SOURCE_DIR ${CMAKE_SOURCE_DIR}/external)

set(CMAKE_CONFIGURATION_TYPES ${CMAKE_BUILD_TYPE})
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -std=c++11")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -std=c++11")

set(SUPPORTED_MODES 
	Android 
	Emscripten
	CodeCoverage
)

if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-std=gnu++0x)
endif()

foreach(mode ${SUPPORTED_MODES})
	set(${mode}_DIR ${CMAKE_MODULE_PATH})
	find_package(${mode})
endforeach()

add_subdirectory(src)

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()

message(STATUS "Building project: Structures and Algorithms")
message(STATUS "Package version: ${PACKAGE_VERSION}")

set(CPACK_USE_DESTDIR "ON")
set(CPACK_PACKAGE_NAME "Structures")
set(CPACK_PACKAGE_VENDOR "Ihor Mudryy")
set(CPACK_PACKAGE_CONTACT "Ihor Mudryy <ihor.mudryy@gmail.com>")
set(CPACK_PACKAGE_VERSION_MAJOR ${VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${VERSION_PATCH})
set(CPACK_DEB_COMPONENT_INSTALL ON)
include(CPack)
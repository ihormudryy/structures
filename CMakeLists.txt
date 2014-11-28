cmake_minimum_required(VERSION 2.8.11)

set(CMAKE_CONFIGURATION_TYPES ${CMAKE_BUILD_TYPE})
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")

if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-std=gnu++0x)
endif()

if(COMPILER_SUPPORTS_GCC_WARNING_FLAGS)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wno-unused-parameter -std=c++11")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-unused-parameter -std=c++11")
endif()

add_subdirectory(src)
add_subdirectory(3rd_party/gmock-1.7.0)

option(BUILD_TESTS "Create project files for building the unit tests" ON)
if(BUILD_TESTS)
    #add_subdirectory(tests)
endif()

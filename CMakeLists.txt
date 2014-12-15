cmake_minimum_required(VERSION 2.8.11)

set(CMAKE_CONFIGURATION_TYPES ${CMAKE_BUILD_TYPE})
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")

if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-std=gnu++0x)
endif()

option(CODE_COVERAGE "Enable code coverage option" OFF)

if(CODE_COVERAGE)
	set(COVERAGE "-fprofile-arcs -ftest-coverage")
	set(GCC_COVERAGE_LINK_FLAGS "-lgcov")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}" )
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0 -Wall -Wno-unused-parameter -std=c++11 ${COVERAGE}")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -Wall -Wno-unused-parameter -std=c++11 ${COVERAGE}")
endif()


add_subdirectory(src)


set(BUILD_SHARED_LIBS ON)

option(BUILD_TESTS "Create project files for building the unit tests" ON)
if(BUILD_TESTS)
	add_subdirectory(3rd_party/gmock-1.7.0)
    add_subdirectory(tests)
endif()

cmake_minimum_required(VERSION 2.8.11)

set(CMAKE_CONFIGURATION_TYPES ${CMAKE_BUILD_TYPE})
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -std=c++11")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -std=c++11")

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-std=gnu++0x)
endif()

option(CODE_COVERAGE "Enable code coverage option" OFF)
option(EMSCRIPTEN "Emscripten crosscompilation mode " OFF)
option(ANDROID "Build Android aplication" OFF)
option(BUILD_TESTS "Create project files for building the unit tests" ON)

if(CODE_COVERAGE)
	set(COVERAGE "-fprofile-arcs -ftest-coverage")
  	set(GCC_COVERAGE_LINK_FLAGS "-lgcov")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}" )
  	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0 -Wall -Wno-unused-parameter -std=c++11 ${COVERAGE} -w")
  	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -Wall -Wno-unused-parameter -std=c++11 ${COVERAGE} -w")
endif()

if(EMSCRIPTEN)
	set(EMMAKEN_CFLAGS "${CMAKE_C_FLAGS} -g -O0 -Wall -Wno-unused-parameter -std=c++11 -w")
	set(emscripten_DIR ${CMAKE_MODULE_PATH})
	find_package(emscripten)
endif()

if(ANDROID)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mfloat-abi=softfp -mfpu=neon -mfp16-format=ieee")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mfloat-abi=softfp -mfpu=neon -mfp16-format=ieee")
	set(Android_DIR ${CMAKE_MODULE_PATH})
	include(${CMAKE_MODULE_PATH}/CreateApk.cmake)
	find_package(Android)
endif()

add_subdirectory(src)

set(BUILD_SHARED_LIBS ON)
if(BUILD_TESTS)
	add_subdirectory(3rd_party/gmock-1.7.0)
	add_subdirectory(3rd_party/glm)
    add_subdirectory(tests)
endif()
if (NOT WARNINGS)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno")
endif()

if (NOT CODE_COVERAGE)
	return()
endif()

set(COVERAGE "-fprofile-arcs -ftest-coverage")
set(GCC_COVERAGE_LINK_FLAGS "-lgcov")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O3 -fno-rtti -Wall -Wno-unused-parameter -std=c++11 ${COVERAGE} -w")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O3 -fno-rtti -Wall -Wno-unused-parameter -std=c++11 ${COVERAGE} -w")
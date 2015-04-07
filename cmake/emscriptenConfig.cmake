message("emscripten mode" ${EMSCRIPTEN_PATH})
SET(EMSCRIPTEN_BUILD 1)

set(PLATFORM_EMSCRIPTEN TRUE)
add_definitions(-DNT_EMSCRIPTEN)
add_definitions(-DEMSCRIPTEN)

SET( THREADS_HAVE_PTHREAD_ARG TRUE CACHE BOOL "Cross-compiling force pthread library" )
SET( CMAKE_THREAD_LIBS_INIT "-lpthread" CACHE STRING "Cross-compiling force pthread library" )
SET( CMAKE_HAVE_THREADS_LIBRARY TRUE CACHE BOOL "Cross-compiling force pthread library" )

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s DISABLE_EXCEPTION_CATCHING=2 -Wno-warn-absolute-paths -g -O2 --bind -Wall -Wno-unused-parameter -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s DISABLE_EXCEPTION_CATCHING=2 -Wno-warn-absolute-paths -g -O2 --bind -Wall -Wno-unused-parameter -std=c++11")

set( EMSC_INCLUDE ${EMSCRIPTEN_PATH}/system/include )
set( LIBCXXABI_INCLUDE ${EMSCRIPTEN_PATH}/system/lib/libcxxabi/include )

include_directories(
	${EMSCRIPTEN_PATH}/system/lib
	${EMSCRIPTEN_PATH}/system/include
	${LIBCXXABI_INCLUDE}
)

link_directories( 
	${EMSCRIPTEN_PATH}/system
	${EMSCRIPTEN_PATH}/incoming
	${LIBCXXABI_INCLUDE}
)
SET( EMSCRIPTEN_LIBS make )

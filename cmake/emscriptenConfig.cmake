message("emscripten mode" ${EMSCRIPTEN_PATH})
SET(EMSCRIPTEN_BUILD 1)

SET( THREADS_HAVE_PTHREAD_ARG TRUE CACHE BOOL "Cross-compiling force pthread library" )
SET( CMAKE_THREAD_LIBS_INIT "-lpthread" CACHE STRING "Cross-compiling force pthread library" )
SET( CMAKE_HAVE_THREADS_LIBRARY TRUE CACHE BOOL "Cross-compiling force pthread library" )

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s DISABLE_EXCEPTION_CATCHING=2 -Wno-warn-absolute-paths -g -O2 --bind -Wall -Wno-unused-parameter -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s DISABLE_EXCEPTION_CATCHING=2 -Wno-warn-absolute-paths -g -O2 --bind -Wall -Wno-unused-parameter -std=c++11")

message( ${EMSCRIPTEN_PATH}/system/include )
set( EMSC_INCLUDE ${EMSCRIPTEN_PATH}/system/include )
set( LIBCXXABI_INCLUDE ${EMSCRIPTEN_PATH}/system/lib/libcxxabi/include )
include_directories(
	${EMSC_INCLUDE} 
	${LIBCXXABI_INCLUDE}
)
#link_directories( ${EMSCRIPTEN_PATH}/incoming )
SET( EMSCRIPTEN_LIBS make )

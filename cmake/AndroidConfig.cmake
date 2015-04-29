if (NOT ANDROID OR EMSCRIPTEN)
    return()
endif()

include(${PROJECT_SOURCE_DIR}/cmake/CreateApk.cmake)
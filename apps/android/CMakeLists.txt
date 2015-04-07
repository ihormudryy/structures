if(NOT ANDROID)
    return()
endif()

find_package(OpenGLES2 REQUIRED)
find_package(Java REQUIRED)
find_library(EGL_LIBRARY NAMES EGL)
find_library(LOG_LIBRARY NAMES log)

##
## native code
##
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/../common APP_COMMON_SOURCES)
add_library(GeoVizJNI MODULE AndroidSupport.cpp ${APP_COMMON_SOURCES})
target_include_directories(GeoVizJNI PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../common)
target_link_libraries(GeoVizJNI GeoViz
    ${OPENGLES2_LIBRARIES} ${EGL_LIBRARY} ${LOG_LIBRARY}
    android_native_app_glue android_ndk_helper)
#target_compile_definitions(GeoVizJNI PRIVATE USE_ANDROID_LOGGING)
set_target_properties(GeoVizJNI PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/out/libs/${ANDROID_ABI}/)

##
## java code
##
include(UseJava)

# cmake wants to always use posix path separators due to the android ndk toolchain
# This does not work with nmake on Windows. Force WIN32
if(CMAKE_HOST_WIN32 AND NOT WIN32)
    set(FORCED_WIN32 TRUE)
    set(WIN32 TRUE)
endif()

set(CMAKE_JAVA_COMPILE_FLAGS -source 1.7 -target 1.7)
set(CMAKE_JAVA_INCLUDE_PATH ${SDK_ROOT}/platforms/android-${ANDROID_SDK_VERSION}/android.jar) ### generalize
set(CMAKE_JAR_CLASSES_PREFIX com/here/geoviz)
set(JAVA_SOURCES
    src/com/here/geoviz/GeoVizActivity.java
    src/com/here/geoviz/GeoVizView.java
)
add_jar(GeoVizJava ${JAVA_SOURCES} OUTPUT_NAME out/libs/GeoVizJava)

if(FORCED_WIN32)
    unset(WIN32)
endif()

add_custom_target(apk)
add_custom_command(TARGET apk
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/out/

    COMMAND ${CMAKE_COMMAND} -E make_directory
        ${CMAKE_CURRENT_BINARY_DIR}/out/libs

    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/assets
        ${CMAKE_CURRENT_BINARY_DIR}/out/assets

    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/res
        ${CMAKE_CURRENT_BINARY_DIR}/out/res

    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_BINARY_DIR}/hype/src/HypeNetwork.jar
        ${CMAKE_CURRENT_BINARY_DIR}/out/libs/HypeNetwork.jar

    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_SOURCE_DIR}/AndroidManifest.xml
        ${CMAKE_CURRENT_BINARY_DIR}/out/AndroidManifest.xml

    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${ANDROID_STL_LIB}
        ${CMAKE_CURRENT_BINARY_DIR}/out/libs/${ANDROID_ABI}/

    COMMAND ${CMAKE_COMMAND} -E make_directory
        ${CMAKE_CURRENT_BINARY_DIR}/out/src

    COMMAND ${SDK_ROOT}/tools/android update project
        -p ${CMAKE_CURRENT_BINARY_DIR}/out
        -t android-${ANDROID_SDK_VERSION}
        -n geoviz

    COMMAND ant debug
)

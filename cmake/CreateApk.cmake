function(create_apk target buildType)
    
    set(APP_PATH android_tmp)

    if (NOT ANDROID)
        message(FATAL_ERROR "Not building for Android.")
    endif()
    if ((NOT SDK_ROOT) OR (NOT NDK_ROOT))
        message(FATAL_ERROR "SDK_ROOT and NDK_ROOT must be set.")
    endif()

    get_filename_component(androidSdkTool "${SDK_ROOT}/tools/android" REALPATH)
    if (NOT EXISTS ${androidSdkTool})
        get_filename_component(androidSdkTool "${SDK_ROOT}/tools/android.bat" REALPATH)
    endif()

    set(workingDirectory ${CMAKE_CURRENT_BINARY_DIR})

    # call the android SDK tool to create a new project
    execute_process(COMMAND ${androidSdkTool} create project
                    --path ${workingDirectory}
                    --target android-${ANDROID_SDK_VERSION}
                    --name ${target}
                    --package com.structures.${target}
                    --activity TestRunner
                    WORKING_DIRECTORY ${workingDirectory}
                    RESULT_VARIABLE androidSdkToolResult)
    if (NOT androidSdkToolResult STREQUAL "0")
        message(FATAL_ERROR "Failed while running ${androidSdkTool}, exit code ${androidSdkToolResult}")
    endif()

    # set the output directory for the .so files to point to the android project's 'lib/[cpuarch] directory
    configure_file(${NDK_ROOT}/sources/cxx-stl/gnu-libstdc++/${ANDROID_EABI_VERSION}/libs/${ANDROID_ABI}/libgnustl_shared.so
                   ${workingDirectory}/libs/${ANDROID_ABI}/libgnustl_shared.so)
    set(outDir ${workingDirectory}/libs/${ANDROID_ABI})
    set_target_properties(${target} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${outDir})
    set_target_properties(${target} PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELEASE ${outDir})
    set_target_properties(${target} PROPERTIES LIBRARY_OUTPUT_DIRECTORY_DEBUG ${outDir})

    if (${buildType} STREQUAL "debug")
        set(debuggable "true")
    else()
        set(debuggable "false")
    endif()

    configure_file(${CMAKE_SOURCE_DIR}/apps/${APP_PATH}/app_glue.cpp ${workingDirectory}/app_glue.cpp)

    configure_file(${CMAKE_SOURCE_DIR}/apps/${APP_PATH}/src/com/structures/unittests/RunUnittests.java
        ${workingDirectory}/src/com/structures/${target}/RunUnittests.java)

    # create AndroidManifest.xml
    configure_file(${CMAKE_SOURCE_DIR}/apps/${APP_PATH}/AndroidManifest.xml
        ${workingDirectory}/AndroidManifest.xml)
    configure_file(${CMAKE_SOURCE_DIR}/apps/${APP_PATH}/res/layout/activity_run_unittests.xml
        ${workingDirectory}/res/layout/activity_run_unittests.xml)
	configure_file(${CMAKE_SOURCE_DIR}/apps/${APP_PATH}/jni/Android.mk
        ${workingDirectory}/jni/Android.mk)


    add_custom_command(TARGET ${target} POST_BUILD
        COMMAND ${CMAKE_COMMAND} ARGS -E copy_if_different ${ANDROID_STL_LIB} ${outDir}
        COMMAND ant ARGS ${buildType} WORKING_DIRECTORY ${workingDir})
endfunction()

function(create_apk target_name buildType)
    configure_file(${NDK_ROOT}/sources/cxx-stl/gnu-libstdc++/${ANDROID_EABI_VERSION}/libs/${ANDROID_ABI}/libgnustl_shared.so
                   ${CMAKE_CURRENT_BINARY_DIR}/libs/${ANDROID_ABI}/libgnustl_shared.so)

    set(OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/libs/${ANDROID_ABI})
    set_target_properties(${target_name} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR})
    set_target_properties(${target_name} PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELEASE ${OUTPUT_DIR})
    set_target_properties(${target_name} PROPERTIES LIBRARY_OUTPUT_DIRECTORY_DEBUG ${OUTPUT_DIR})

    set(STRUCTURES_SOURCE_DIR ${CMAKE_SOURCE_DIR}/apps/android_unittest)

    file(GLOB_RECURSE RESOURCES "${STRUCTURES_SOURCE_DIR}/*.*")

    foreach(INPUT_FILE ${RESOURCES})
        string(REPLACE ${STRUCTURES_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} OUTPUT_FILE ${INPUT_FILE})
        configure_file(${INPUT_FILE} ${OUTPUT_FILE})
    endforeach()
endfunction()
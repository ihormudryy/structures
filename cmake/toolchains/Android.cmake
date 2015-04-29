if(DEFINED ENV{ANDROID_SDK_ROOT})
    set(SDK_ROOT $ENV{ANDROID_SDK_ROOT})
elseif(DEFINED ENV{SDK_ROOT})
    set(SDK_ROOT $ENV{SDK_ROOT})
endif()

file(TO_CMAKE_PATH "${SDK_ROOT}" SDK_ROOT)

if(NOT SDK_ROOT)
    message(FATAL_ERROR "SDK_ROOT not specified.\n\n")
endif()

if(DEFINED ENV{ANDROID_NDK_ROOT})
    set(NDK_ROOT $ENV{ANDROID_NDK_ROOT})
elseif(DEFINED ENV{NDK_ROOT})
    set(NDK_ROOT $ENV{NDK_ROOT})
endif()

file(TO_CMAKE_PATH "${NDK_ROOT}" NDK_ROOT)

if(NOT NDK_ROOT)
    message(FATAL_ERROR "NDK_ROOT not specified.\n\n")
endif()

set(SDK_VERSION 15)
if(DEFINED ENV{ANDROID_SDK_VERSION})
    set(SDK_VERSION $ENV{ANDROID_SDK_VERSION})
endif()

set(NDK_VERSION 15)
if(DEFINED ENV{ANDROID_NDK_VERSION})
    set(NDK_VERSION $ENV{ANDROID_NDK_VERSION})
endif()

set(ABI_VERSION armeabi-v7a)
if(DEFINED ENV{ANDROID_ABI_VERSION})
    set(ABI_VERSION $ENV{ANDROID_ABI_VERSION})
endif()

set(EABI_VERSION 4.9)
if(DEFINED ENV{ANDROID_EABI_VERSION})
    set(EABI_VERSION $ENV{ANDROID_EABI_VERSION})
endif()

set(SDK_ROOT ${SDK_ROOT} CACHE PATH "Android SDK root path")
set(NDK_ROOT ${NDK_ROOT} CACHE PATH "Android NDK root path")
set(ANDROID_SDK_VERSION ${SDK_VERSION} CACHE STRING "Android SDK version")
set(ANDROID_NDK_VERSION ${NDK_VERSION} CACHE STRING "Android NDK version")
set(ANDROID_ABI ${ABI_VERSION} CACHE STRING "Android ABI, e.g. x86 or armeabi-v7a")
set(ANDROID_EABI_VERSION ${EABI_VERSION} CACHE STRING "Android EABI version")

### TODO - set this dependend on the eabi if we want to support 64 bit builds
set(CMAKE_C_SIZEOF_DATA_PTR 4)

if ("${ANDROID_ABI}" STREQUAL "x86")
    set(ANDROID_ARCH x86 CACHE STRING "Android arch")
    set(ANDROID_TOOLCHAIN_ARCH x86 CACHE STRING "Android arch")
    set(ANDROID_TOOL_PREFIX i686-linux-android CACHE STRING "Android arch")
elseif("${ANDROID_ABI}" STREQUAL "armeabi-v7a")
    set(ANDROID_ARCH arm)
    set(ANDROID_GCC_ARCH armv7-a)
    set(ANDROID_TOOLCHAIN_ARCH arm-linux-androideabi)
    set(ANDROID_TOOL_PREFIX arm-linux-androideabi)
else()
    message(FATAL_ERROR "Unsupported Android ABI: ${ANDROID_ABI}")
endif()


# NOTE: The .so ${ANDROID_STL_LIB} points to must be embedded in the APK and loaded in Java before
# loading the .so libraries for the program.
set(ANDROID_STL_LIB ${NDK_ROOT}/sources/cxx-stl/gnu-libstdc++/${ANDROID_EABI_VERSION}/libs/${ANDROID_ABI}/libgnustl_shared.so CACHE FILEPATH "Path to STL")
set(ANDROID_STL_LIB_NAME gnustl_shared CACHE STRING "STL library to link to")

set(ANDROID TRUE)

if(NOT EXISTS ${SDK_ROOT}/platforms/android-${ANDROID_SDK_VERSION})
    message(FATAL_ERROR "android-${ANDROID_SDK_VERSION} is not installed in your SDK\n\n")
endif()

if(NOT EXISTS ${NDK_ROOT}/platforms/android-${ANDROID_NDK_VERSION})
    message(FATAL_ERROR "android-${ANDROID_NDK_VERSION} is not installed in your NDK\n\n")
endif()

set(CMAKE_CROSSCOMPILING TRUE)
set(CMAKE_SYSTEM_VERSION 1)
set(CMAKE_SYSTEM_NAME Linux)

if(${CMAKE_HOST_SYSTEM_PROCESSOR} STREQUAL "i686")
    set(ANDROID_NDK_HOST_SYSTEM_PROCESSOR "x86")
elseif(${CMAKE_HOST_SYSTEM_PROCESSOR} STREQUAL "x86_64")
    set(ANDROID_NDK_HOST_SYSTEM_PROCESSOR "x86_64")
elseif(${CMAKE_HOST_SYSTEM_PROCESSOR} STREQUAL "AMD64")
    set(ANDROID_NDK_HOST_SYSTEM_PROCESSOR "x86_64")
else()
    message(FATAL_ERROR "${CMAKE_HOST_SYSTEM_PROCESSOR} not supported")
endif()

set(ANDROID_TOOL_OS_SUFFIX)
if(CMAKE_HOST_SYSTEM_NAME MATCHES Linux)
    set(ANDROID_HOST "linux-${ANDROID_NDK_HOST_SYSTEM_PROCESSOR}")
elseif(CMAKE_HOST_SYSTEM_NAME MATCHES Darwin)
    set(ANDROID_HOST "darwin-${ANDROID_NDK_HOST_SYSTEM_PROCESSOR}")
elseif(CMAKE_HOST_SYSTEM_NAME MATCHES Windows)
    if(EXISTS ${NDK_ROOT}/toolchains/${ANDROID_TOOLCHAIN_ARCH}-${ANDROID_EABI_VERSION}/prebuilt/windows-${ANDROID_NDK_HOST_SYSTEM_PROCESSOR})
        set(ANDROID_HOST "windows-${ANDROID_NDK_HOST_SYSTEM_PROCESSOR}")
    else()
        SET(ANDROID_HOST "windows")
    endif()
    set(ANDROID_TOOL_OS_SUFFIX ".exe")
else()
    # TODO: Windows
    message(FATAL_ERROR "${CMAKE_HOST_SYSTEM_NAME} not supported")
endif()

set(ANDROID_TOOLCHAIN_ROOT ${NDK_ROOT}/toolchains/${ANDROID_TOOLCHAIN_ARCH}-${ANDROID_EABI_VERSION}/prebuilt/${ANDROID_HOST})

set(CMAKE_C_COMPILER ${ANDROID_TOOLCHAIN_ROOT}/bin/${ANDROID_TOOL_PREFIX}-gcc${ANDROID_TOOL_OS_SUFFIX} CACHE PATH "gcc")
set(CMAKE_CXX_COMPILER ${ANDROID_TOOLCHAIN_ROOT}/bin/${ANDROID_TOOL_PREFIX}-g++${ANDROID_TOOL_OS_SUFFIX} CACHE PATH "g++")
set(CMAKE_LINKER ${ANDROID_TOOLCHAIN_ROOT}/bin/${ANDROID_TOOL_PREFIX}-ld${ANDROID_TOOL_OS_SUFFIX} CACHE PATH "linker")
set(CMAKE_STRIP ${ANDROID_TOOLCHAIN_ROOT}/bin/${ANDROID_TOOL_PREFIX}-strip${ANDROID_TOOL_OS_SUFFIX} CACHE PATH "strip")
set(CMAKE_AR ${ANDROID_TOOLCHAIN_ROOT}/bin/${ANDROID_TOOL_PREFIX}-ar${ANDROID_TOOL_OS_SUFFIX} CACHE PATH "archive")
set(CMAKE_NM ${ANDROID_TOOLCHAIN_ROOT}/bin/${ANDROID_TOOL_PREFIX}-nm${ANDROID_TOOL_OS_SUFFIX} CACHE PATH "nm")
set(CMAKE_OBJCOPY ${ANDROID_TOOLCHAIN_ROOT}/bin/${ANDROID_TOOL_PREFIX}-objcopy${ANDROID_TOOL_OS_SUFFIX} CACHE PATH "objcopy")
set(CMAKE_OBJDUMP ${ANDROID_TOOLCHAIN_ROOT}/bin/${ANDROID_TOOL_PREFIX}-objdump${ANDROID_TOOL_OS_SUFFIX} CACHE PATH "objdump")
set(CMAKE_RANLIB ${ANDROID_TOOLCHAIN_ROOT}/bin/${ANDROID_TOOL_PREFIX}-ranlib${ANDROID_TOOL_OS_SUFFIX} CACHE PATH "ranlib")

set(ANDROID_SYSROOT "--sysroot=${NDK_ROOT}/platforms/android-${ANDROID_NDK_VERSION}/arch-${ANDROID_ARCH}/")
set(ANDROID_SYSROOT_LFLAGS "-L${NDK_ROOT}/sources/cxx-stl/gnu-libstdc++/${ANDROID_EABI_VERSION}/libs/${ANDROID_ABI} -L${NDK_ROOT}/platforms/android-${ANDROID_NDK_VERSION}/arch-${ANDROID_ARCH}/usr/lib")
set(CMAKE_EXE_LINKER_FLAGS_INIT "${ANDROID_SYSROOT} ${ANDROID_SYSROOT_LFLAGS} -l${ANDROID_STL_LIB_NAME} -lm")
set(CMAKE_SHARED_LINKER_FLAGS_INIT "${ANDROID_SYSROOT} ${ANDROID_SYSROOT_LFLAGS} -l${ANDROID_STL_LIB_NAME} -lm -Wl,--no-undefined")
set(CMAKE_MODULE_LINKER_FLAGS_INIT "${ANDROID_SYSROOT} ${ANDROID_SYSROOT_LFLAGS} -l${ANDROID_STL_LIB_NAME} -lm")

# Change the command for the C++ linker to use the C compiler so it doesn't link to libstdc++
#set(CMAKE_CXX_CREATE_SHARED_LIBRARY
#      "<CMAKE_C_COMPILER> <CMAKE_SHARED_LIBRARY_CXX_FLAGS> <LANGUAGE_COMPILE_FLAGS> <LINK_FLAGS> <CMAKE_SHARED_LIBRARY_CREATE_CXX_FLAGS> <CMAKE_SHARED_LIBRARY_SONAME_CXX_FLAG><TARGET_SONAME> -o <TARGET> <OBJECTS> <LINK_LIBRARIES>")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -finline-limit=64")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -finline-limit=64")

if (ANDROID_GCC_ARCH)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=${ANDROID_GCC_ARCH}")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -march=${ANDROID_GCC_ARCH}")
endif()

set(CMAKE_FIND_ROOT_PATH ${NDK_ROOT}/platforms/android-${ANDROID_NDK_VERSION}/arch-${ANDROID_ARCH}/usr/
                         ${CMAKE_PREFIX_PATH})

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

include_directories(
    ${NDK_ROOT}/sources/cxx-stl/gnu-libstdc++/${ANDROID_EABI_VERSION}/include
    ${NDK_ROOT}/sources/cxx-stl/gnu-libstdc++/${ANDROID_EABI_VERSION}/libs/${ANDROID_ABI}/include
    ${NDK_ROOT}/platforms/android-${ANDROID_NDK_VERSION}/arch-${ANDROID_ARCH}/usr/include
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}" CACHE STRING "c++ flags")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}" CACHE STRING "c flags")


cmake_minimum_required(VERSION 3.4.1)

set(CMAKE_VERBOSE_MAKEFILE on)


get_filename_component(INFERNO_OS_PROJ_DIR
                       ${CMAKE_CURRENT_SOURCE_DIR}/../../../.. ABSOLUTE)


# configure import libs
set(infrlib_DIR ${INFERNO_OS_PROJ_DIR}/inferno-os/Android/arm/lib)

add_library(emu STATIC IMPORTED)
set_target_properties(emu PROPERTIES IMPORTED_LOCATION
    ${infrlib_DIR}/emu.a)

add_library(lib9 STATIC IMPORTED)
set_target_properties(lib9 PROPERTIES IMPORTED_LOCATION
    ${infrlib_DIR}/lib9.a)

add_library(libbio STATIC IMPORTED)
set_target_properties(libbio PROPERTIES IMPORTED_LOCATION
    ${infrlib_DIR}/libbio.a)

add_library(libdraw STATIC IMPORTED)
set_target_properties(libdraw PROPERTIES IMPORTED_LOCATION
    ${infrlib_DIR}/libdraw.a)

add_library(libdynld STATIC IMPORTED)
set_target_properties(libdynld PROPERTIES IMPORTED_LOCATION
    ${infrlib_DIR}/libdynld.a)

add_library(libfreetype STATIC IMPORTED)
set_target_properties(libfreetype PROPERTIES IMPORTED_LOCATION
    ${infrlib_DIR}/libfreetype.a)

add_library(libinterp STATIC IMPORTED)
set_target_properties(libinterp PROPERTIES IMPORTED_LOCATION
    ${infrlib_DIR}/libinterp.a)

add_library(libkeyring STATIC IMPORTED)
set_target_properties(libkeyring PROPERTIES IMPORTED_LOCATION
    ${infrlib_DIR}/libkeyring.a)

add_library(libmath STATIC IMPORTED)
set_target_properties(libmath PROPERTIES IMPORTED_LOCATION
    ${infrlib_DIR}/libmath.a)

add_library(libmemdraw STATIC IMPORTED)
set_target_properties(libmemdraw PROPERTIES IMPORTED_LOCATION
    ${infrlib_DIR}/libmemdraw.a)

add_library(libmemlayer STATIC IMPORTED)
set_target_properties(libmemlayer PROPERTIES IMPORTED_LOCATION
    ${infrlib_DIR}/libmemlayer.a)

add_library(libmp STATIC IMPORTED)
set_target_properties(libmp PROPERTIES IMPORTED_LOCATION
    ${infrlib_DIR}/libmp.a)

add_library(libprefab STATIC IMPORTED)
set_target_properties(libprefab PROPERTIES IMPORTED_LOCATION
    ${infrlib_DIR}/libprefab.a)

add_library(libsec STATIC IMPORTED)
set_target_properties(libsec PROPERTIES IMPORTED_LOCATION
    ${infrlib_DIR}/libsec.a)

add_library(libstyx STATIC IMPORTED)
set_target_properties(libstyx PROPERTIES IMPORTED_LOCATION
    ${infrlib_DIR}/libstyx.a)

add_library(libtk STATIC IMPORTED)
set_target_properties(libtk PROPERTIES IMPORTED_LOCATION
    ${infrlib_DIR}/libtk.a)


#SET(WEBP_ENABLE_SWAP_16BIT_CSP ON CACHE BOOL
#    "Enable byte swap for 16 bit colorspaces." FORCE)
#add_subdirectory(${WEBP_SRC_DIR} ${WEBP_SRC_DIR}/build/)

# build native_app_glue as a static lib
include_directories(${ANDROID_NDK}/sources/android/native_app_glue)

add_library(native_app_glue STATIC
    ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c)

# now build app's shared lib
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -fPIC")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -fPIC -fPIE")

# Export ANativeActivity_onCreate(), 
# Refer to: https://github.com/android-ndk/ndk/issues/381.
set(CMAKE_SHARED_LINKER_FLAGS
    "${CMAKE_SHARED_LINKER_FLAGS} -u ANativeActivity_onCreate -fPIC -fPIE")

add_library(inferno_os_app SHARED
    inferno_os_app.cpp)


#target_include_directories(inferno_os_app PRIVATE
#    )
#    ${WEBP_SRC_DIR}/examples
#    ${WEBP_SRC_DIR}/src)

# add lib dependencies
target_link_libraries(inferno_os_app android log m native_app_glue m
    emu
    libinterp
    libbio
    libdraw
    libdynld
    libkeyring
    libmath
    libmemlayer
    libmemdraw
    libsec
    libstyx
    libtk
    libfreetype
    libmp
    lib9
    emu
    )
#    -Wl,--start-group
#     -Wl,--end-group
#   libprefab

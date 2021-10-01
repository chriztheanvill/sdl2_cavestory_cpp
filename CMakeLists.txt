### Using Ccmake
##
## $ cd /media/cris/Panzer/Cris/Documents/Workspace_Linux/Cpp_Cmake_VSCode/build
## $ ccmake ..
##
## Push [enter] to change val
## Push [c] to config
## Push [g] to make the changes happen and exit
## Push [q] to exit, and not make changes
##
## Setup
## 	Cppcheck ON
## 	Clang-tidy OFF
## 	Cppcheck ON
## 	Enable_Sanitizer_Address ON (On sanitizer, just can be enabled one kind)
##
###

## Main CMAKE file
## CMAKE version minimun required 3.16.3
cmake_minimum_required(VERSION 3.18.4)
# cmake_minimum_required(VERSION 3.19.2)

## Name System proyect ##
project(sdl_yt_cavestory_03 VERSION 1.0.0 LANGUAGES C CXX)

add_compile_options(
	-std=c++20 
    # -fmodules-ts 
)


include(My_Cmake/Standard_Project_Settings.cmake)

# Link this 'library' to set the c++ standard / compile-time options requested
add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_20 cxx_lambda_init_captures)

# Link this 'library' to use the warnings specified in CompilerWarnings.cmake
add_library(project_warnings INTERFACE)

# standard compiler warnings
include(My_Cmake/Compiler_Warnings.cmake)
set_project_warnings(project_warnings)

# sanitizer options if supported by compiler
include(My_Cmake/Sanitizers.cmake)
enable_sanitizers(project_options)

# Find Linux Version
include(My_Cmake/Linux_Ver.cmake)
if (CMAKE_SYSTEM_NAME MATCHES "Linux")
    get_linux_lsb_release_information()
    message(STATUS "+++++++++++++++ GNU Linux ${LSB_RELEASE_ID_SHORT} ${LSB_RELEASE_VERSION_SHORT} ${LSB_RELEASE_CODENAME_SHORT} +++++++++++++++")
endif ()

# enable Threads
include(My_Cmake/Threads.cmake)

# enable doxygen
include(My_Cmake/Doxygen.cmake)
enable_doxygen()

# allow for static analysis options
include(My_Cmake/Static_Analyzers.cmake)

# Enable Boost
include(My_Cmake/Boost.cmake)

# Enable Graphics
include(My_Cmake/Graphics.cmake)

# Set up some extra Conan dependencies based on our needs
# before loading Conan
set(CONAN_EXTRA_REQUIRES "")
set(CONAN_EXTRA_OPTIONS "")

# if(CPP_STARTER_USE_IMGUI)
# set(CONAN_EXTRA_REQUIRES ${CONAN_EXTRA_REQUIRES}
#                          imgui-sfml/2.1@bincrafters/stable)

# set(CONAN_EXTRA_OPTIONS ${CONAN_EXTRA_OPTIONS} sfml:shared=False
# sfml:graphics=True sfml:audio=False sfml:window=True
# libalsa:disable_python=True)
# endif()

## Conan config
include(My_Cmake/Conan.cmake)
run_conan()

# Very basic PCH example
option(ENABLE_PCH "Enable Precompiled Headers" ON)
# option(ENABLE_PCH "Enable Precompiled Headers" OFF)
if (ENABLE_PCH)
    # This sets a global PCH parameter, each project will build its own PCH, which
    # is a good idea if any #define's change
    #
    message(STATUS " -- Precompiled Headers ")
    # target_precompile_headers(project_options INTERFACE <vector> <string> <map> <utility>)
    target_precompile_headers(project_options
            # PUBLIC
            # "foo.h"
            INTERFACE
            # System
            <array>
            <iostream>
            <fstream>
            <map>
            <memory>
            <iterator>
            <random>
            <string>
            <utility>
            <vector>
            # 3s
            <SDL2/SDL.h>
            <SDL2/SDL_image.h>
            <SDL2/SDL_ttf.h>
#            <fmt/core.h>
#            <fmt/color.h>
            <glm/glm.hpp>

            # Boost
            <boost/format.hpp>
            #			<boost/filesystem
            )
endif ()

################################################################
# Enable C++20

#add_definitions(-std=c++11)
# add_definitions(-std=c++17 -DANALYSIS=ON)
# add_definitions(-std=c++2a -DANALYSIS=ON)
#add_definitions(-std=c++20 -DANALYSIS=ON)

## DEPRECATED
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated -Wdeprecated-declarations")
# set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Xclang -fconcepts-ts")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -Xclang -fconcepts-ts")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -fconcepts")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a -fconcepts")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a ")

## Which C++ version.
# set(CMAKE_C_STANDARD 99)
# set(CMAKE_CXX_STANDARD 11)
# set(CMAKE_CXX_STANDARD 14)
# set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD 20)

## Debug flags.
set(CMAKE_BUILD_TYPE Debug)

## Check compiler
include(My_Cmake/Clang_setup.cmake)

################################################################

# Enable Testing
enable_testing()
# message( "Testing enabled!!!" )
# add_subdirectory(test)
#add_subdirectory(googletest)


### List Programs ###
## 0000 program ##
add_subdirectory(0000)

################################################################

# set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
# set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

## Set the current directory the run time folder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} PUBLIC
        # ${LUA_LIBRARIES}
        ${LUA_LIBRARY}
        ${THREAD_LIBRARIES}
        ${OPENGL_VIDEO_LIBRARIES}
        ${Boost_LIBRARIES}
        )

####################################################


message(STATUS "\n -- MY -- CMake C FLAGS ${CMAKE_C_FLAGS}")
message(STATUS " -- MY -- CMake C++ FLAGS ${CMAKE_CXX_FLAGS} \n\n")

####################################################
## Features
### Lambdas
target_compile_features(${PROJECT_NAME} PRIVATE
        # LAMBDA FEATURES
        cxx_lambda_init_captures
        # C++17 ENABLED
        # cxx_std_17
        # C++20 ENABLED
        cxx_std_20
        )

message(STATUS " WARNING!!! If SDL2 / GLFW / VULKAN or some video program does not working, enable on My_Cmake config.\n")

####################################################
## Install
# install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin) # $(CMAKE_INSTALL_PREFIX) / bin
# install(FILES "src/main.cpp" DESTINATION src) # $(CMAKE_INSTALL_PREFIX) / bin
# target_link_libraries(${PROJECT_NAME} PRIVATE son_library)

# install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
####################################################
####################################################

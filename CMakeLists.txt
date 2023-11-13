
##
## Starfish Project Details
##
## (c) 2023 David Rowbotham (thedaver64@gmail.com)
##
##
cmake_minimum_required(VERSION 3.0...3.22)
project("starfish")
if(CMAKE_SIZEOF_VOID_P EQUAL 4)
    message(FATAL_ERROR "64 bit compiler required.")
endif(CMAKE_SIZEOF_VOID_P EQUAL 4)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../bin")



##
## Linux Package Requirements
##
if(UNIX)
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
include_directories($OPENGL_INCLUDE_DIR)
endif(UNIX)


##
## MSVC Compile Flags
##
if(MSVC)
set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS "-I../include /EHsc /Qpar /GS- /O2 /D NDEBUG")
endif(MSVC)


##
## Linux Compile Flags
##
if(UNIX)
set(CMAKE_CXX_FLAGS "-I../include -O2")
endif(UNIX)


##
## MINGW. Not supported atm.
##
if(MINGW)
message(FATAL_ERROR "MinGW not currently supported.")
endif(MINGW)


##
## Project Build.
##
add_executable(starfish src/starfish.cpp)

##
## MSVC Platform Link Options
##
if(MSVC)
set_target_properties(starfish PROPERTIES LINK_FLAGS "/LIBPATH:../lib/win64 /ENTRY:mainCRTStartup /SUBSYSTEM:WINDOWS")
target_link_libraries(starfish glfw3 opengl32 )
endif(MSVC)

##
## Linux Platform Link Options
##
if(UNIX)
target_link_libraries(starfish ${OPENGL_gl_LIBRARY} glfw)
endif(UNIX)
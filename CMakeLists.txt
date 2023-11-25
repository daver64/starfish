
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
include_directories($OPENGL_INCLUDE_DIR src/imgui)
endif(UNIX)


##
## MSVC Compile Flags
##
if(MSVC)
set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS "-I../include -I../src/imgui -I../src/imgui/backends /EHsc /Qpar /GS- /O2 /D NDEBUG")
endif(MSVC)


##
## Linux Compile Flags
##
if(UNIX)
set(CMAKE_CXX_FLAGS "-I../include -I../src/imgui -I../src/imgui/backends -O2")
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
if(MSVC)
add_executable(starfish src/starfish.cpp
    src/main_audio.cpp
    src/main_graphics.cpp
    src/main_networking.cpp
    src/sl_fastnoise.cpp
    src/sl_fontdata.cpp
    src/sl_draw.cpp
    src/sl_framebuffer.cpp
    src/sl_primitivebuffer.cpp
    src/sl_shader.cpp
    src/sl_texture.cpp
    src/sl_vertexbuffer.cpp
    src/sl_context.cpp
    src/imgui/imgui.cpp
    src/imgui/imgui_draw.cpp
    src/imgui/imgui_tables.cpp
    src/imgui/imgui_widgets.cpp
    src/imgui/backends/imgui_impl_glfw.cpp
    src/imgui/backends/imgui_impl_opengl3.cpp
    src/imgui/backends/imgui_impl_win32.cpp)
    target_sources(starfish PRIVATE src/starfish.rc)
endif(MSVC)

if(UNIX)
add_executable(starfish src/starfish.cpp
    src/main_audio.cpp
    src/main_graphics.cpp
    src/main_networking.cpp
    src/sl_fastnoise.cpp
    src/sl_fontdata.cpp
    src/sl_draw.cpp
    src/sl_framebuffer.cpp
    src/sl_primitivebuffer.cpp
    src/sl_shader.cpp
    src/sl_texture.cpp
    src/sl_vertexbuffer.cpp    
    src/sl_context.cpp
    src/imgui/imgui.cpp
    src/imgui/imgui_draw.cpp
    src/imgui/imgui_tables.cpp
    src/imgui/imgui_widgets.cpp
    src/imgui/backends/imgui_impl_glfw.cpp
    src/imgui/backends/imgui_impl_opengl3.cpp)
endif(UNIX)


##
## MSVC Platform Link Options
##
if(MSVC)
set_target_properties(starfish PROPERTIES LINK_FLAGS "/LIBPATH:../lib/win64 /ENTRY:mainCRTStartup /SUBSYSTEM:CONSOLE")
target_link_libraries(starfish glfw3 opengl32 openal32 )
endif(MSVC)

##
## Linux Platform Link Options
##
if(UNIX)
target_link_libraries(starfish GL glfw openal)
endif(UNIX)
cmake_minimum_required(VERSION 3.10)
project(GravitySimulationGame)

set(CMAKE_CXX_STANDARD 17) 

# Define paths for source and external libraries
set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(SFML_DIR "${CMAKE_SOURCE_DIR}/external/SFML/lib/cmake/SFML")
set(IMGUI_SFML_DIR "${CMAKE_SOURCE_DIR}/external/ImGui-SFML")

# Find OpenGL (Needed for ImGui-SFML)
find_package(OpenGL REQUIRED)

# Ensure CMake finds SFML and ImGui-SFML headers
include_directories(${SFML_DIR}/../../include)
include_directories(${IMGUI_SFML_DIR})
include_directories(${IMGUI_SFML_DIR}/imgui)  # Include "imgui.h"
include_directories(${CMAKE_SOURCE_DIR}/include)  # Add include directory

# Add ImGui Core Source Files
set(IMGUI_SRC
    ${IMGUI_SFML_DIR}/imgui/imgui.cpp
    ${IMGUI_SFML_DIR}/imgui/imgui_draw.cpp
    ${IMGUI_SFML_DIR}/imgui/imgui_widgets.cpp
    ${IMGUI_SFML_DIR}/imgui/imgui_tables.cpp
    ${IMGUI_SFML_DIR}/imgui-SFML.cpp  # SFML integration
)

find_package(SFML 2.6 REQUIRED COMPONENTS graphics window system)

set(SOURCES
    ${SOURCE_DIR}/main.cpp
    ${SOURCE_DIR}/GravitySource.cpp
    ${SOURCE_DIR}/Particle.cpp
    ${SOURCE_DIR}/Renderer.cpp
    ${IMGUI_SRC}
)

# Create executable
add_executable(GravitySimulationGame ${SOURCES})

# Link SFML, ImGui-SFML, and OpenGL (Windows-specific linking)
target_link_libraries(GravitySimulationGame sfml-graphics sfml-window sfml-system OpenGL::GL)

# Windows OpenGL fix
if (WIN32)
    target_link_libraries(GravitySimulationGame opengl32)
endif()

# Linux-specific linking (for OpenGL & X11)
if (UNIX AND NOT APPLE)
    target_link_libraries(GravitySimulationGame X11 pthread)
endif()

# --- Copy SFML DLLs to the output directory ---
if(WIN32)
    # Define the directory containing the DLLs
    set(SFML_BIN_DIR "${CMAKE_SOURCE_DIR}/external/SFML/bin")
    
    # List of SFML modules
    foreach(dll IN ITEMS "sfml-audio" "sfml-graphics" "sfml-network" "sfml-system" "sfml-window")
        add_custom_command(TARGET GravitySimulationGame POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "$<IF:$<CONFIG:Debug>,${SFML_BIN_DIR}/${dll}-d-2.dll,${SFML_BIN_DIR}/${dll}-2.dll>"
                $<TARGET_FILE_DIR:GravitySimulationGame>)
    endforeach()
endif()

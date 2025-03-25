cmake_minimum_required(VERSION 3.10)
project(GravitySimulationGame)

set(CMAKE_CXX_STANDARD 17)

# Define source and include paths
set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(SFML_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/external/SFML/include")
set(SFML_LIB_DIR "${CMAKE_SOURCE_DIR}/external/SFML/lib")
set(IMGUI_SFML_DIR "${CMAKE_SOURCE_DIR}/external/ImGui-SFML")

# Add include directories
include_directories(
    ${INCLUDE_DIR}
    ${SFML_INCLUDE_DIR}
    ${IMGUI_SFML_DIR}
    ${IMGUI_SFML_DIR}/imgui
)

# Link directories for local libraries
link_directories(${SFML_LIB_DIR})

# ImGui source files
set(IMGUI_SRC
    ${IMGUI_SFML_DIR}/imgui/imgui.cpp
    ${IMGUI_SFML_DIR}/imgui/imgui_draw.cpp
    ${IMGUI_SFML_DIR}/imgui/imgui_widgets.cpp
    ${IMGUI_SFML_DIR}/imgui/imgui_tables.cpp
    ${IMGUI_SFML_DIR}/imgui-SFML.cpp
)

# Game source files
set(SOURCES
    ${SOURCE_DIR}/main.cpp
    ${SOURCE_DIR}/GravitySource.cpp
    ${SOURCE_DIR}/Particle.cpp
    ${SOURCE_DIR}/Renderer.cpp
    ${IMGUI_SRC}
)

# Create executable
add_executable(GravitySimulationGame ${SOURCES})

# Platform-specific linking
if (WIN32)
    target_link_libraries(GravitySimulationGame
        sfml-graphics-d
        sfml-window-d
        sfml-system-d
        opengl32
    )
elseif (APPLE)
    target_link_libraries(GravitySimulationGame
        sfml-graphics
        sfml-window
        sfml-system
        "-framework OpenGL"
    )
elseif (UNIX)
    target_link_libraries(GravitySimulationGame
        sfml-graphics
        sfml-window
        sfml-system
        GL
        X11
        pthread
    )
endif()

# --- Copy SFML DLLs for Windows builds ---
if (WIN32)
    set(SFML_BIN_DIR "${CMAKE_SOURCE_DIR}/external/SFML/bin")

    foreach(dll IN ITEMS "sfml-audio" "sfml-graphics" "sfml-network" "sfml-system" "sfml-window")
        add_custom_command(TARGET GravitySimulationGame POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "$<IF:$<CONFIG:Debug>,${SFML_BIN_DIR}/${dll}-d-2.dll,${SFML_BIN_DIR}/${dll}-2.dll>"
                $<TARGET_FILE_DIR:GravitySimulationGame>)
    endforeach()
endif()

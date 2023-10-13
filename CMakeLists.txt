cmake_minimum_required(VERSION 3.16)
project(cppgfx)

if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})
    set(IS_TOP_LEVEL TRUE)
else ()
    set(IS_TOP_LEVEL FALSE)
endif ()

option(BUILD_EXAMPLES "Build examples" ${IS_TOP_LEVEL})

include(FetchContent)
set(BUILD_SHARED_LIBS FALSE CACHE BOOL "" FORCE)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.0
)
message(STATUS "Fetching SFML v2.6.0")
FetchContent_MakeAvailable(SFML)

FetchContent_Declare(imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG v1.89.9
)
message(STATUS "Fetching ImGui v1.89.9")
FetchContent_MakeAvailable(imgui)

FetchContent_Declare(imgui-sfml
    GIT_REPOSITORY https://github.com/SFML/imgui-sfml.git
    GIT_TAG v2.6
)
message(STATUS "Fetching ImGui-SFML v2.6")
set(IMGUI_SFML_FIND_SFML OFF CACHE BOOL "" FORCE)
set(IMGUI_DIR ${imgui_SOURCE_DIR} CACHE PATH "" FORCE)
FetchContent_MakeAvailable(imgui-sfml)

add_library(${PROJECT_NAME} STATIC
        src/cppgfx.cpp
        src/win32.cpp
)
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC include)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
target_link_libraries(${PROJECT_NAME} PUBLIC
        sfml-graphics
        sfml-window
        sfml-audio
        sfml-network
        sfml-system
        ImGui-SFML::ImGui-SFML
)

if (WIN32)
    target_link_libraries(${PROJECT_NAME} PUBLIC
            opengl32
            gdi32
            winmm
            dwmapi
    )
endif ()

if (BUILD_EXAMPLES)
    add_subdirectory(examples)
endif ()

cmake_minimum_required(VERSION 3.16)
project(cppgfx VERSION 0.1.0 LANGUAGES CXX)

include(cmake/deps.cmake)

option(BUILD_EXAMPLES "Build examples" ${IS_TOP_LEVEL})
option(BUILD_DOCS "Build documentation" OFF)
option(USE_WIN32_DARK_MODE "Use dark mode on Windows" ON)

add_library(${PROJECT_NAME} STATIC
        src/base64.cpp
        src/cppgfx.cpp
        src/data.cpp
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
        spdlog::spdlog
        glm::glm
)

if (USE_WIN32_DARK_MODE)
    target_compile_definitions(${PROJECT_NAME} PUBLIC USE_WIN32_DARK_MODE)
endif ()

if (WIN32)
    target_link_libraries(${PROJECT_NAME} PUBLIC opengl32 gdi32 winmm dwmapi)
endif ()

if (BUILD_EXAMPLES)
    add_subdirectory(examples)
endif ()

if (BUILD_DOCS)
    add_subdirectory(docs)
endif ()

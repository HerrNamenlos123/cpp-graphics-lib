cmake_minimum_required(VERSION 3.16)
project(cppgfx)

include(cmake/deps.cmake)

option(BUILD_EXAMPLES "Build examples" ${IS_TOP_LEVEL})

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
)

if (WIN32)
    target_link_libraries(${PROJECT_NAME} PUBLIC opengl32 gdi32 winmm dwmapi)
endif ()

if (BUILD_EXAMPLES)
    add_subdirectory(examples)
endif ()

include(FetchContent)

if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})
    set(IS_TOP_LEVEL TRUE)
else ()
    set(IS_TOP_LEVEL FALSE)
endif ()

set(BUILD_SHARED_LIBS FALSE CACHE BOOL "" FORCE)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 13c8a1de4e4597e1854fc2a17fef28135660c81e
        )
message(STATUS "Fetching SFML")
FetchContent_MakeAvailable(SFML)

FetchContent_Declare(imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui.git
        GIT_TAG v1.89.9
        )
message(STATUS "Fetching ImGui")
FetchContent_MakeAvailable(imgui)

FetchContent_Declare(spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG ff205fd29a4a2f6ebcbecffd149153256d89a671
        )
message(STATUS "Fetching spdlog")
FetchContent_MakeAvailable(spdlog)

FetchContent_Declare(imgui-sfml
        GIT_REPOSITORY https://github.com/SFML/imgui-sfml.git
        GIT_TAG 6bd43671d3fab76f94b1f0877d943d8cc3b34c3b
        )
message(STATUS "Fetching ImGui-SFML")
set(IMGUI_SFML_FIND_SFML OFF CACHE BOOL "" FORCE)
set(IMGUI_SFML_IMGUI_DEMO ON CACHE BOOL "" FORCE)
set(IMGUI_DIR ${imgui_SOURCE_DIR} CACHE PATH "" FORCE)
FetchContent_MakeAvailable(imgui-sfml)
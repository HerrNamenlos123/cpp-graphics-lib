include(FetchContent)

if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})
    set(IS_TOP_LEVEL TRUE)
else ()
    set(IS_TOP_LEVEL FALSE)
endif ()

message(STATUS "Fetching SFML")
set(BUILD_SHARED_LIBS FALSE CACHE BOOL "" FORCE)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 13c8a1de4e4597e1854fc2a17fef28135660c81e
        )
FetchContent_MakeAvailable(SFML)

message(STATUS "Fetching ImGui")
FetchContent_Declare(imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui.git
        GIT_TAG v1.89.9
        )
FetchContent_MakeAvailable(imgui)

message(STATUS "Fetching spdlog")
FetchContent_Declare(spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG ff205fd29a4a2f6ebcbecffd149153256d89a671
        )
FetchContent_MakeAvailable(spdlog)

message(STATUS "Fetching ImGui-SFML")
FetchContent_Declare(imgui-sfml
        GIT_REPOSITORY https://github.com/SFML/imgui-sfml.git
        GIT_TAG 6bd43671d3fab76f94b1f0877d943d8cc3b34c3b
        )
set(IMGUI_SFML_FIND_SFML OFF CACHE BOOL "" FORCE)
set(IMGUI_SFML_IMGUI_DEMO ON CACHE BOOL "" FORCE)
set(IMGUI_DIR ${imgui_SOURCE_DIR} CACHE PATH "" FORCE)
FetchContent_MakeAvailable(imgui-sfml)

message(STATUS "Fetching glm")
FetchContent_Declare(glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG 0.9.9.8
)
FetchContent_MakeAvailable(glm)
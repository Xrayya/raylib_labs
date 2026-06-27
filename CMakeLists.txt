cmake_minimum_required(VERSION 3.16...4.99)

include(cmake/PreferClang.cmake)

project(
    thing
    VERSION 0.1
    LANGUAGES CXX
)

# ========================
# Global C++ config
# ========================
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ========================
# Sources
# ========================
file(GLOB_RECURSE SOURCES
    src/*.cpp
)

add_executable(thing ${SOURCES})
target_include_directories(thing PRIVATE src)

# ========================
# Warnings (always on)
# ========================
function(enable_strict_warnings target)
    if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        message(STATUS "Using Clang warning set")

        target_compile_options(${target} PRIVATE
            -Wall
            -Wextra
            -Wpedantic

            -Wdeprecated-copy
            -Wdangling
            -Wunused-private-field
            -Wshadow
            -Wnon-virtual-dtor
            -Woverloaded-virtual
            -Wsuggest-override
            -Wold-style-cast
            -Wformat=2
            -Wswitch-enum

            -Werror=sign-compare
            -Werror=return-type
            -Werror=unreachable-code
            -Werror=missing-field-initializers
            -Werror=conversion
            -Werror=deprecated-copy
            -Werror=dangling
            -Werror=non-virtual-dtor
            -Werror=overloaded-virtual
            -Werror=suggest-override
        )

    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        message(STATUS "Using GCC warning set")

        target_compile_options(${target} PRIVATE
            -Wall
            -Wextra
            -Wpedantic

            -Wshadow
            -Wnon-virtual-dtor
            -Woverloaded-virtual
            -Wsuggest-override
            -Wconversion
            -Wsign-compare
            -Wduplicated-cond
            -Wduplicated-branches
            -Wlogical-op
            -Wuseless-cast
            -Wnull-dereference
            -Wold-style-cast

            -Werror=sign-compare
            -Werror=return-type
            -Werror=conversion
            -Werror=non-virtual-dtor
            -Werror=overloaded-virtual
            -Werror=suggest-override
        )
    endif()
endfunction()

enable_strict_warnings(thing)

# ========================
# Debug-only flags
# ========================
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Configuring Debug build with sanitizers")

    target_compile_options(thing PRIVATE
        -g
        -O0
        -fno-omit-frame-pointer
        -fsanitize=address
        -fsanitize=undefined
    )

    target_link_options(thing PRIVATE
        -fsanitize=address
        -fsanitize=undefined
    )
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
  message(STATUS "Optimizing for Release build")

    target_compile_options(thing PRIVATE
      -O2
    )

    target_link_options(thing PRIVATE
      -O2
    )
endif()

# ========================
# Fetch raylib
# ========================

set(RAYLIB_VERSION 5.5)
find_package(raylib ${RAYLIB_VERSION} QUIET)
if (NOT raylib_FOUND)
  message(STATUS "raylib ${RAYLIB_VERSION} not found")
  include(FetchContent)
  FetchContent_Declare(
      raylib
      GIT_REPOSITORY https://github.com/raysan5/raylib.git
      GIT_TAG ${RAYLIB_VERSION}
  )
  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED)
    message(STATUS "Populating raylib ${RAYLIB_VERSION}...")
    set(FETCHCONTENT_QUIET NO)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(raylib)
  endif()
endif()

# ========================
# Fetch imgui
# ========================

set(IMGUI_VERSION "v1.92.7")
include(FetchContent)
FetchContent_Declare(
    imGui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git 
    GIT_TAG ${IMGUI_VERSION}
)
FetchContent_MakeAvailable(imGui)
FetchContent_GetProperties(imGui SOURCE_DIR IMGUI_SRC_DIR)

# ========================
# Fetch rlImGui
# ========================

set(RLIMGUI_VERSION "Raylib_5_5")
FetchContent_Declare(
    rlImGui
    GIT_REPOSITORY https://github.com/raylib-extras/rlImGui.git 
    GIT_TAG ${RLIMGUI_VERSION}
)
FetchContent_MakeAvailable(rlImGui)
FetchContent_GetProperties(rlImGui SOURCE_DIR RLIMGUI_SRC_DIR)

# ========================
# Create Custom Targets for Non-CMake Libraries
# ========================

# 1. Define imgui as a static library target so it compiles separately from your strict warnings
add_library(imgui_lib STATIC
    ${IMGUI_SRC_DIR}/imgui.cpp
    ${IMGUI_SRC_DIR}/imgui_draw.cpp
    ${IMGUI_SRC_DIR}/imgui_tables.cpp
    ${IMGUI_SRC_DIR}/imgui_widgets.cpp
    ${IMGUI_SRC_DIR}/imgui_demo.cpp
)
target_include_directories(imgui_lib PUBLIC ${IMGUI_SRC_DIR})
# This line treats ImGui as a system header, suppressing external warnings in your code
target_include_directories(imgui_lib SYSTEM INTERFACE ${IMGUI_SRC_DIR}) 

# 2. Define rlImGui as a static library target
add_library(rlimgui_lib STATIC
    ${RLIMGUI_SRC_DIR}/rlImGui.cpp
)
target_include_directories(rlimgui_lib PUBLIC ${RLIMGUI_SRC_DIR})
target_include_directories(rlimgui_lib SYSTEM INTERFACE ${RLIMGUI_SRC_DIR})
# rlImGui needs access to both raylib and imgui headers to compile
target_link_libraries(rlimgui_lib PRIVATE raylib imgui_lib)

# ========================
# Link Everything to Your Target
# ========================
# Link your created library targets instead of phantom find_package names
target_link_libraries(thing PRIVATE raylib imgui_lib rlimgui_lib)

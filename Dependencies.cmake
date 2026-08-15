#
# Dependencies
#

include(FetchContent)

# Raylib
find_package(raylib QUIET)

if(NOT raylib_FOUND)
    message("Raylib not found, installing...")
    FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 6.0
    )
    FetchContent_MakeAvailable(raylib)
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
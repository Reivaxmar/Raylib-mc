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
else()
    message("Raylib found!")
endif()

# nlohmann/json
find_package(nlohmann_json QUIET)

if(NOT nlohmann_json_FOUND)
    message("nlohmann/json not found, installing...")
    FetchContent_Declare(
        nlohmann_json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.12.0
    )
    FetchContent_MakeAvailable(nlohmann_json)
else()
    message("nlohmann/json found!")
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE
    raylib
    nlohmann_json::nlohmann_json
)
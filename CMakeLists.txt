cmake_minimum_required(VERSION 3.16)

# Set project name
project(proj)

set(CMAKE_CXX_STANDARD 17)

# Get all the files
file(GLOB_RECURSE SOURCES src/*.cpp)
include_directories(headers /usr/include)
add_executable(${PROJECT_NAME} ${SOURCES})

include(Dependencies.cmake)

# Create a custom target to copy the assets
add_custom_target(copy_assets ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_SOURCE_DIR}/assets ${CMAKE_BINARY_DIR}/assets
    COMMENT "Copying assets to the build directory"
)

# Make sure the 'copy_assets' target is run before building the main executable
add_dependencies(${PROJECT_NAME} copy_assets)

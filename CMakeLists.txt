cmake_minimum_required(VERSION 3.16)

# Set project name
project(mc)

set(CMAKE_CXX_STANDARD 17)

# Get all the files
file(GLOB_RECURSE SOURCES src/*.cpp)
include_directories(headers external)
add_executable(${PROJECT_NAME} ${SOURCES})

include(Dependencies.cmake)

option(ENABLE_ASAN "Enable AddressSanitizer" OFF)
option(ENABLE_UBSAN "Enable UndefinedBehaviorSanitizer" OFF)
option(ENABLE_TSAN "Enable ThreadSanitizer" OFF)

if(ENABLE_ASAN)
    target_compile_options(${PROJECT_NAME} PRIVATE
        -fsanitize=address
        -fno-omit-frame-pointer
    )
    target_link_options(${PROJECT_NAME} PRIVATE
        -fsanitize=address
    )
endif()

if(ENABLE_UBSAN)
    target_compile_options(${PROJECT_NAME} PRIVATE
        -fsanitize=undefined
        -fno-omit-frame-pointer
    )
    target_link_options(${PROJECT_NAME} PRIVATE
        -fsanitize=undefined
    )
endif()

if(ENABLE_TSAN)
    target_compile_options(${PROJECT_NAME} PRIVATE
        -fsanitize=thread
        -fno-omit-frame-pointer
    )
    target_link_options(${PROJECT_NAME} PRIVATE
        -fsanitize=thread
    )
endif()

# Create a custom target to copy the assets
add_custom_target(copy_assets ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_SOURCE_DIR}/assets ${CMAKE_BINARY_DIR}/assets
    COMMENT "Copying assets to the build directory"
)

# Make sure the 'copy_assets' target is run before building the main executable
add_dependencies(${PROJECT_NAME} copy_assets)

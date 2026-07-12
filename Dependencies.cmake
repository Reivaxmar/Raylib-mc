#
# Dependencies
#

include(FetchContent)

# SFML
find_package(SFML 2.5 QUIET)
if(NOT SFML_FOUND)
    FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x
    )
    
    FetchContent_MakeAvailable(SFML)
endif()
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)
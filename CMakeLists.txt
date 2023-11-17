# Specify the minimum version for CMake
cmake_minimum_required(VERSION 3.10)

# Project's name
project(Impetus)

# Use C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable warnings
if(MSVC)
    add_compile_options(/W4 /WX /wd4100)
else()
    add_compile_options(-Wall -Wextra -g)
endif()

# Specify the source files
set(SOURCES
    ${PROJECT_SOURCE_DIR}/src/main.cpp
    ${PROJECT_SOURCE_DIR}/src/engine.cpp
    ${PROJECT_SOURCE_DIR}/src/glad.c
    # Add additional source files here
)

# Set binary output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")

# Add executable to be built from the source files
add_executable(Impetus ${SOURCES})

if(MSVC)
    # Include directories for SDL2
    target_include_directories(Impetus PRIVATE ${PROJECT_SOURCE_DIR}/include)
    # Link against SDL2 for Windows
    target_link_libraries(Impetus PRIVATE 
        ${PROJECT_SOURCE_DIR}/lib/SDL2/SDL2.lib
        ${PROJECT_SOURCE_DIR}/lib/SDL2/SDL2main.lib)
    #throws dll in with executable
    add_custom_command(TARGET Impetus POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E copy_if_different
                           ${PROJECT_SOURCE_DIR}/lib/SDL2/SDL2.dll
                           ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug)

elseif(UNIX AND NOT APPLE)
    find_package(SDL2 REQUIRED)
    target_link_libraries(Impetus PRIVATE ${SDL2_LIBRARIES})
    target_include_directories(Impetus PRIVATE ${PROJECT_SOURCE_DIR}/include)
    target_include_directories(Impetus PRIVATE ${SDL2_INCLUDE_DIRS})
endif()

# Custom target for making directories if necessary 
add_custom_target(
    directories ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory "${PROJECT_SOURCE_DIR}/bin"
)

# Add dependency between executable and directories target
add_dependencies(Impetus directories)

# Specify the install rule
install(TARGETS Impetus DESTINATION bin)

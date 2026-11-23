cmake_minimum_required(VERSION 3.28)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_COMPILER=gcc)
set(CMAKE_CXX_COMPILER=g++)
set(CMAKE_GENERATOR=Ninja)

set(SFML_USE_SYSTEM_DEPS OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.1.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

FetchContent_MakeAvailable(harfbuzz)
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
)
add_executable(main ${SOURCES})
target_link_libraries(main PRIVATE 
	SFML::Graphics 
	SFML::Audio    
	-static-libstdc++
	-static-libgcc
	-static
    "-Wl,--start-group"
    "${CMAKE_BINARY_DIR}/_deps/sfml-build/lib/libfreetype.a"
    "${CMAKE_BINARY_DIR}/_deps/sfml-build/lib/libharfbuzz.a"
    "-Wl,--end-group"
)
target_compile_definitions(main PRIVATE
	ASSETS_PATH="assets/"
)
target_compile_options(main PRIVATE
    $<$<CONFIG:Release>:-O3>
    $<$<CONFIG:Release>:-march=x86-64-v3>
)

add_custom_command(TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/assets"
        "${CMAKE_SOURCE_DIR}/build/bin/assets"
)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT main)

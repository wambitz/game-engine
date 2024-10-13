# Global CMakeLists.txt
cmake_minimum_required(VERSION 3.10)

# Project Name
project(GameEngine)

# Set C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable all warnings
set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS "${CXX_FLAGS}")

# Set the default build type to Debug if not set by user
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type (Debug/Release)" FORCE)
endif()

# Add compiler flags for debugging and optimizations
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")

# Enable Position Independent Code (PIC) for shared libraries
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Include directories for the engine headers (like IPlugin.h, engine_core.h)
include_directories(${PROJECT_SOURCE_DIR})

# Create the shared library for render (equivalent to: g++ -fPIC -shared -o render.so render.cpp)
add_library(render SHARED render.cpp)

# Create the shared library for libplugin (equivalent to: g++ -fPIC -shared -o plugin.so plugin.cpp)
add_library(plugin SHARED plugin.cpp)

# Add the main executable (equivalent to: g++ -o game_engine main.cpp)
add_executable(game_engine main.cpp engine_core.cpp)

# Link the main executable to the dynamically linked library librender 
# equivalent to: -L. -lrender -ldl
# The -L. flag tells the compiler to look for shared libraries in the current directory.
# The -lrender flag links against the librender.so shared library.
# The -ldl flag links against the dynamic loading library (dlopen, dlsym, etc.).
target_link_libraries(game_engine PRIVATE render dl)

# Set the output directories for the shared libraries and the executable
set_target_properties(render PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set_target_properties(plugin PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set_target_properties(game_engine PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# This adds a runtime path (RPATH) to the executable, telling it to look for the shared libraries in the same directory 
# ($ORIGIN refers to the directory where the executable is located). 
# This is equivalent to setting the LD_LIBRARY_PATH environment variable manually.
# Add RPATH (Runpath) so that the executable can find the shared libraries in the same directory
set_target_properties(game_engine PROPERTIES INSTALL_RPATH "$ORIGIN")

# Custom message for debugging
message(STATUS "CMake Build Type: ${CMAKE_BUILD_TYPE}")

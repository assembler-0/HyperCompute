cmake_minimum_required(VERSION 3.16)
project(HyperCompute LANGUAGES CXX)

# Enable folders in IDEs like VS Code
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Optimize for release
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

# Enable optimization flags
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native -ffast-math -flto")

# Include path
include_directories(${PROJECT_SOURCE_DIR}/include)

# Find OpenCL
find_package(OpenCL REQUIRED)

# Gather source files
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

# Define the executable
add_executable(HyperCompute ${SOURCES})

# Link OpenCL
target_link_libraries(HyperCompute PRIVATE OpenCL::OpenCL)

# Include directory for compiler
target_include_directories(HyperCompute PRIVATE ${PROJECT_SOURCE_DIR}/include)

# Optional: Print info
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Source files: ${SOURCES}")

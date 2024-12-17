cmake_minimum_required(VERSION 3.10)  # It's better to use a newer version of CMake if possible
project(hpc_proj)

# Find OpenCV package
find_package(OpenCV REQUIRED)

# Include OpenCV headers
include_directories(${OpenCV_INCLUDE_DIRS})

# Create the executable
add_executable(hpc_proj ../main.cpp)  # Make sure to specify the correct relative path to main.cpp

# Link OpenCV libraries to your executable
target_link_libraries(hpc_proj ${OpenCV_LIBS})


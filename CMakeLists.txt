cmake_minimum_required(VERSION 3.10)
project(hpc_proj)

# Find OpenCV package
find_package(OpenCV REQUIRED)

# Find MPI package
find_package(MPI REQUIRED)

# Include OpenCV and MPI headers
include_directories(${OpenCV_INCLUDE_DIRS} ${MPI_INCLUDE_PATH})

# Create the executable
add_executable(hpc_proj ../main.cpp)

# Link OpenCV and MPI libraries to your executable
target_link_libraries(hpc_proj ${OpenCV_LIBS} ${MPI_LIBRARIES})


#!/bin/bash

# Set the path to your build directory
BUILD_DIR="./build"

# Path to the main.cpp file
MAIN_CPP="../main.cpp"

# Check if the build directory exists, if not, create it
if [ ! -d "$BUILD_DIR" ]; then
    echo "Build directory not found, creating it..."
    mkdir "$BUILD_DIR"
fi

# Navigate to the build directory
cd "$BUILD_DIR"

# Run cmake to configure the project
echo "Running cmake..."
cmake ..

# Run make to compile the project
echo "Building the project..."
make

# Optionally, run the program after building
echo "Running the program..."
./hpc_proj


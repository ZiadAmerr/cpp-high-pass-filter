#!/bin/bash

# Set the path to your build directory
BUILD_DIR="./build"


# Flag to enable debugging
DEBUG=false

# Parse the -d argument for debugging
if [ "$1" == "-d" ]; then
    DEBUG=true
fi

# Function to run commands silently unless DEBUG is enabled
run_command() {
    if [ "$DEBUG" == "true" ]; then
        "$@"  # Print command output
    else
        "$@" >/dev/null 2>&1  # Silence output
    fi
}

# Check if the build directory exists, if not, create it
if [ ! -d "$BUILD_DIR" ]; then
    run_command echo "Build directory not found, creating it..."
    run_command mkdir "$BUILD_DIR"
fi

# Navigate to the build directory
cd "$BUILD_DIR"

# Run cmake to configure the project
run_command echo "Running cmake..."
run_command cmake ..

# Run make to compile the project
run_command echo "Building the project..."
run_command make

# Optionally, run the program after building
run_command echo "Running the program..."
./hpc_proj


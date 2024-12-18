#!/bin/bash

# Set the path to your build directory
BUILD_DIR="./build"

# Default values for arguments
DEBUG=false
NUM_NODES=1        # Default number of nodes
FILTER_SIZE=3      # Default filter size
IMAGE_PATH=""      # Default image path
OPEN_IMAGES=false  # Default: Do not open images
MEASURE_TIME=false # Default: Do not measure time

# Parse arguments
while [[ "$#" -gt 0 ]]; do
    case $1 in
        -d) DEBUG=true ;;                  # Enable debug mode
        -n) NUM_NODES="$2"; shift ;;       # Set number of nodes
        -f) FILTER_SIZE="$2"; shift ;;     # Set filter size
        -p) IMAGE_PATH="$2"; shift ;;      # Set image path
        -o) OPEN_IMAGES=true ;;            # Enable opening images
        -t) MEASURE_TIME=true ;;           # Enable measuring time
        *) echo "Unknown parameter: $1"; exit 1 ;;
    esac
    shift
done

# Function to run commands silently unless DEBUG is enabled
run_command() {
    if [ "$DEBUG" == "true" ]; then
        "$@"  # Print command output
    else
        "$@" >/dev/null 2>&1  # Silence output
    fi
}

# Validate arguments
if [ -z "$IMAGE_PATH" ]; then
    echo "Error: Image path (-p) is required."
    exit 1
fi

if (( FILTER_SIZE % 2 == 0 )); then
    echo "Error: FILTER_SIZE (-f) must be an odd number."
    exit 1
fi

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

# Measure and print the execution time of mpirun if enabled
run_command echo "Running the program with $NUM_NODES nodes, FILTER_SIZE $FILTER_SIZE, and PATH $IMAGE_PATH..."

FULL_COMMAND="mpirun -np $NUM_NODES ./hpc_proj $FILTER_SIZE $IMAGE_PATH"

if [ "$MEASURE_TIME" == "true" ]; then
    run_command echo "Benchmarking the program..."
    hyperfine -r 10 "$FULL_COMMAND"
else
    run_command $FULL_COMMAND
fi

# Optionally open the images after running
if [ "$OPEN_IMAGES" == "true" ]; then
    open ../output.png
    open "$IMAGE_PATH"
fi


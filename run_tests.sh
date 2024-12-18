#!/bin/bash

# List of sizes and node counts
sizes=("360" "480" "720" "1080" "2K" "4K")
nodes=("1" "2" "4" "8")

# Loop through all combinations
for size in "${sizes[@]}"; do
    for node in "${nodes[@]}"; do
        # Run the command and capture the output
        output=$(./quick_run.sh "$size" "$node")
        # Print formatted result
        echo "SIZE: $size, NODES: $node, OUT: $output"
    done
done

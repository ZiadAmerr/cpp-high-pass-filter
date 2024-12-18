#!/bin/bash

# Usage: ./quick_run.sh <resolution> <nodes>
# Example: ./quick_run.sh 360 8

# Check if arguments are provided
if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <resolution: 360|480|720|1080|2K|4K> <nodes: 1|2|4|8>"
    exit 1
fi

# Assign input arguments
resolution=$1
nodes=$2

# Define image paths based on resolution
case $resolution in
    360) image_path="/Users/ziad/Desktop/Fall24/proj_HPC/proj/random_noise_images/random_noise_360p.png" ;;
    480) image_path="/Users/ziad/Desktop/Fall24/proj_HPC/proj/random_noise_images/random_noise_480p.png" ;;
    720) image_path="/Users/ziad/Desktop/Fall24/proj_HPC/proj/random_noise_images/random_noise_720p.png" ;;
    1080) image_path="/Users/ziad/Desktop/Fall24/proj_HPC/proj/random_noise_images/random_noise_1080p.png" ;;
    2K) image_path="/Users/ziad/Desktop/Fall24/proj_HPC/proj/random_noise_images/random_noise_2K.png" ;;
    4K) image_path="/Users/ziad/Desktop/Fall24/proj_HPC/proj/random_noise_images/random_noise_4K.png" ;;
    *) echo "Invalid resolution. Use 360, 480, 720, 1080, 2K, or 4K."; exit 1 ;;
esac

# Run the benchmark
./run.sh -t -n "$nodes" -f 9 -p "$image_path" 2>/dev/null | grep "Time (mean ± σ):" | awk -F': *' '{print $2}' | awk '{print $1, $2, $3, $4, $5}'
# ./quick_run.sh 360 1

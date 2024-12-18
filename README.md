# High-Performance Computing Project

Parallelization of High-Pass Filter using MPI.

## Demo

To run the code, follow these steps:
Clone the repository and navigate to it.
```bash
git clone https://github.com/ZiadAmerr/cpp-high-pass-filter --depth=1  # Low depth for fast and lightweight clone

cd cpp-high-pass-filter/
```

Add execution permissions to the run file
```bash
chmod +x run.sh
```

Run the script with the suitable arguments.
```bash
./run.sh  -d  # to enable debugging (default is disabled)
            -n 4  # To run with 4 nodes (default is 1, must be less than the number of cores)
            -f 3  # To set the filter size to 3 (default is 3, must be odd)
            -p /path/to/image.jpg  # To set the image path (required, must be an absolute path, relative paths may behave unexpectedly)
            -o  # To enable opening the images after program finishes execution (default is disabled)
            -t  # To enable measuring the time taken for the program to finish (default is disabled)

# Example
./run.sh -n 4 -f 3 -p /path/to/image.jpg -o -t
./run.sh -d -n 8 -f 9 -p /path/to/image.jpg -t
```

To run the quick benchmarking script.
```bash
chmod +x run_tests.sh  # Add execution permissions to the script

./run_tests.sh  # Run the script
>>> SIZE: 360, NODES: 2, OUT: 470.6 ms ± 6.0 ms
>>> SIZE: 360, NODES: 4, OUT: 461.6 ms ± 12.3 ms
>>> SIZE: 360, NODES: 8, OUT: 626.0 ms ± 20.5 ms
>>> SIZE: 480, NODES: 1, OUT: 667.7 ms ± 8.9 ms
>>> SIZE: 480, NODES: 2, OUT: 541.2 ms ± 6.4 ms
>>> SIZE: 480, NODES: 4, OUT: 498.6 ms ± 3.6 ms
>>> SIZE: 480, NODES: 8, OUT: 677.7 ms ± 43.1 ms
>>> SIZE: 720, NODES: 1, OUT: 1.088 s ± 0.018 s
>>> SIZE: 720, NODES: 2, OUT: 757.3 ms ± 9.2 ms
>>> SIZE: 720, NODES: 4, OUT: 618.9 ms ± 13.5 ms
>>> SIZE: 720, NODES: 8, OUT: 754.5 ms ± 8.5 ms
>>> SIZE: 1080, NODES: 1, OUT: 2.007 s ± 0.016 s
>>> SIZE: 1080, NODES: 2, OUT: 1.235 s ± 0.014 s
>>> SIZE: 1080, NODES: 4, OUT: 882.0 ms ± 24.5 ms
>>> SIZE: 1080, NODES: 8, OUT: 988.8 ms ± 40.0 ms
>>> SIZE: 2K, NODES: 1, OUT: 6.296 s ± 0.014 s
>>> SIZE: 2K, NODES: 2, OUT: 3.444 s ± 0.016 s
>>> SIZE: 2K, NODES: 4, OUT: 2.263 s ± 0.113 s
>>> SIZE: 2K, NODES: 8, OUT: 2.095 s ± 0.053 s
>>> SIZE: 4K, NODES: 1, OUT: 26.761 s ± 1.260 s
>>> SIZE: 4K, NODES: 2, OUT: 15.933 s ± 0.236 s
>>> SIZE: 4K, NODES: 4, OUT: 10.563 s ± 0.234 s
>>> SIZE: 4K, NODES: 8, OUT: 7.821 s ± 0.084 s
```

## Prerequisites
The code needs `OpenCV`, `MPI` installed on the machine, the code was tested and confirmed to work on ARM64 systems, on OS X specifically, and is not guaranteed to work correctly on other systems (again, no time for this extensibility!)

For benchmarking, the previous requirements need to be installed correctly, plus `hyperfine`, which can be installed through `brew install hyperfine` on OS X.
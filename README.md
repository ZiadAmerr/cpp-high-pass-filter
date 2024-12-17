# High-Performance Computing Project

Parallelization of High-Pass Filter using MPI.

## Demo

To run the code, follow these steps:
Clone the repository and navigate to it.
```bash
git clone https://github.com/ZiadAmerr/cpp-high-pass-filter --depth=1  # Low depth for fast and lightweight clone

cd cpp-high-pass-filter/
```

Modify main.cpp with your arguments (it definitely can be modified from the shell script, but I just don't have time to do that right now).
```cpp
 #define FILTER_SIZE 3                  // Must be an odd number
 #define NUM_NODES 4                    // Number of nodes to use
 #define PATH "path/to/your/image.png"  // Path to the desired image
```

Run the build the script
```bash
./run.sh
```

Run the executable file on parallel systems
```bash
mpirun -np NUM_NODES ./build/hpc_proj  # Make sure to replace NUM_NODES with the same value in main.cpp
```


## Prerequisites
The code needs OpenCV and MPI installed on the machine, the code was tested and confirmed to work on ARM64 systems, on OS X specifically, and is not guaranteed to work correctly on other systems (again, no time for this extensibility!)


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
 #define PATH "path/to/your/image.png"  // Path to the desired image
```

Add execution permissions to the run file
```bash
chmod +x run.sh
```

Run the build the script
```bash
./run.sh -n 4  # To run the code with 4 nodes

# OR
./run.sh -d -n 4  # To run the code with debugging
```


## Prerequisites
The code needs OpenCV and MPI installed on the machine, the code was tested and confirmed to work on ARM64 systems, on OS X specifically, and is not guaranteed to work correctly on other systems (again, no time for this extensibility!)


# N-Queens
Exploration of methods to solve the N-Queens problem for my undergraduate dissertation. 

This program requires use of the MPI standard. This was developed using [MPICH](https://www.mpich.org/ "MPICH") implementation.
## Command Line usage
To compile:
```
mpiCC autoTest.cpp -o autoTest 
g++ -o generateValues generateValues.cpp
```
To run a single NQ.
The program will save a 0 if it correctly calculated the correct solution, 1 if else to `testResults.txt`.
It will then save the value of N, the depth of initial config, and the total number of parallel processes.
```
./generateValues <VALUE OF N> <INITIAL CONFIG DEPTH> <FILENAME>
mpirun -n <NUMBER OF PROCESSES> ./autoTest <VALUE OF N> <INITIAL CONFIG DEPTH> <FILENAME>
```
Example:
```
mpirun -n 4 ./autoTest 12 4 testResults.txt
```
# Files
The Array Backtracking algorithm can be found at `N-Queens/Parallel Backtracking/autoTest.cpp` and uses the header file `NQueen.hpp`

The Bit Pattern Backtracking algorithm can be found at `N-Queens/Jeff Somers Implementation/bitwiseParallel.cpp`

# N-Queens
Exploration of methods to solve the N-Queens problem for my undergraduate dissertation. The N-Queens problem aims to place *n* Queens on a chessboard of size *n x n*. 

This program requires use of the MPI standard. This was developed using [MPICH](https://www.mpich.org/ "MPICH") implementation.
## Command Line usage
To compile using the MPICH implementation:
```
mpiCC autoTest.cpp -o autoTest 
```
Compiling the serial sub program values
```
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
The Array Backtracking algorithm can be found at `N-Queens/Vector and Bit Pattern implementation/Vector/autoTest.cpp` and uses the generator file `generateValues.cpp`. The `autoTest.cpp` file requires the use of `NQueen.hpp`.

The Bit Pattern Backtracking algorithm can be found at `N-Queens/Vector and Bit Pattern implementation/Bitwise/bitwiseParallel.cpp`  and uses the generator file `generateArray.cpp`


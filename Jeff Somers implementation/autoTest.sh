#!/bin/bash

g++ generateArray.cpp -o generateArray
mpiCC bitwiseParallel.cpp -o bitwiseParallel

for N in {10..10}
do
    for ((D=0; D<$N; D++))
    do 
        for i in {1..10}
        do
            ./generateArray $N $D 
            /usr/bin/time -f "%E %U %S" -a -o testResultsBit.txt mpirun -n 1 ./bitwiseParallel $N $D 
        done
    done
done

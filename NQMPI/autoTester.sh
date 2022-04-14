#!/bin/bash
for N in {14..14}
do
    for ((D=0; D<$N; D++))
    do 
        for i in {1..10}
        do
            ./generateValues $N $D "depthValues.txt"
            /usr/bin/time -f "%E %U %S" -a -o testResults.txt mpirun -n 1 ./autoTest $N $D "depthValues.txt"
            ./generateValues $N $D "depthValues.txt"
            /usr/bin/time -f "%E %U %S" -a -o testResults.txt mpirun -n 2 ./autoTest $N $D "depthValues.txt"
            ./generateValues $N $D "depthValues.txt"
            /usr/bin/time -f "%E %U %S" -a -o testResults.txt mpirun -n 4 ./autoTest $N $D "depthValues.txt"
        done
    done
done

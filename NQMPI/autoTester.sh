#!/bin/bash

for N in {4..13}
do
    for ((D=0; D<$N; D++))
    do 
        for P in {1..4}
        do
        { time mpirun -n $P ./autoTest $N $D; } 2> "tests2/P${P}N${N}depth${D}.txt"
        done
    done
done

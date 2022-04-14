#!/bin/bash

for ((D=0; D<10; D++))
do 
    { time mpirun -n 4 ./autoTest 16 $D ; } 2> "testsN16/P4N16depth${D}.txt"
    done
done


#!/bin/bash --login

###
#SBATCH -p compute
#SBATCH -o runout.%J
#SBATCH -e runerr.%J
#SBATCH -n 16

#SBATCH --job-name=nq_bench

#SBATCH --time=0-01:00

#SBATCH --mem-per-cpu=2000
###

module purge
module load mpi/mpich/3.2.1

./generateValues 15 2 "depthValues.txt"
/usr/bin/time -f "%E %U %S" -a -o testResultsHPC.txt time mpiexec ./autoTest 15 2 "depthValues.txt"

for N in {10..17}
do
    ./generateValues $N 5 "depthValues.txt"
    #SBATCH -n 1
    /usr/bin/time -f "%E %U %S" -a -o testResultsHPC.txt time mpiexec ./autoTest $N 5 "depthValues.txt"
    #SBATCH -n 2
    /usr/bin/time -f "%E %U %S" -a -o testResultsHPC.txt time mpiexec ./autoTest $N 5 "depthValues.txt"
    #SBATCH -n 4
    /usr/bin/time -f "%E %U %S" -a -o testResultsHPC.txt time mpiexec ./autoTest $N 5 "depthValues.txt"
    #SBATCH -n 8
    /usr/bin/time -f "%E %U %S" -a -o testResultsHPC.txt time mpiexec ./autoTest $N 5 "depthValues.txt"
    #SBATCH -n 16
    /usr/bin/time -f "%E %U %S" -a -o testResultsHPC.txt time mpiexec ./autoTest $N 5 "depthValues.txt"
    #SBATCH -n 32
    /usr/bin/time -f "%E %U %S" -a -o testResultsHPC.txt time mpiexec ./autoTest $N 5 "depthValues.txt"
    #SBATCH -n 64
    /usr/bin/time -f "%E %U %S" -a -o testResultsHPC.txt time mpiexec ./autoTest $N 5 "depthValues.txt"
done


#!/bin/bash --login

###
#SBATCH -p compute
#SBATCH -o runout.%J
#SBATCH -e runerr.%J
#SBATCH -n 4

#SBATCH --job-name=nq_bench

#SBATCH --time=0-01:00

#SBATCH --mem-per-cpu=2000
###

module purge
module load mpi/mpich/3.2.1

for N in {10..16}
do
    ./generateValues $N 6 "depthValues.txt"
    /usr/bin/time -f "%E %U %S" -a -o testResultsHPC.txt time mpiexec ./autoTest $N 6 "depthValues.txt"
done


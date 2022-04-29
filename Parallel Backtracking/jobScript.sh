#!/bin/bash --login

###
#SBATCH -p compute
#SBATCH -o runout.%J
#SBATCH -e runerr.%J
#SBATCH -n 16

#SBATCH --job-name=nq_bench

#SBATCH --time=0-00:10

#SBATCH --mem-per-cpu=2000
###

module purge
module load mpi/mpich/3.2.1

./generateValues 15 2 "depthValues.txt"
time mpiexec ./autoTest 15 2 "depthValues.txt"
./generateValues 15 3 "depthValues.txt"
time mpiexec ./autoTest 15 3 "depthValues.txt"


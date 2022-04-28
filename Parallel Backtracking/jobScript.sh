#!/bin/bash --login

###
#SBATCH -p compute
#SBATCH -o runout.%J
#SBATCH -e runerr.%J
#SBATCH -n 8

#SBATCH --job-name=nq_bench

#SBATCH --time=0-00:10

#SBATCH --mem-per-cpu=2000
###

module load compiler/intel mpi/intel mpi
./generateValues 15 1 "depthValues.txt"

#run Intel MPI Benchmarks with mpirun - will automatically pick up Slurm parallel environment
mpirun ./autoTest 15 1 "depthValues.txt"

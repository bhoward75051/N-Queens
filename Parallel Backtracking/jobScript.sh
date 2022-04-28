#!/bin/bash --login

###
#SBATCH -p compute
#SBATCH -o runout.%J
#SBATCH -e runerr.%J

#Job name
#SBATCH --job-name=nq_bench

#maximum job time in D-HH:MM
#SBATCH --time=0-00:10

#Number of parallel processes (Tasks)
#SBATCH -n=8

#SBATCH --mem-per-cpu=2000


###
module load compiler/intel mpi/intel
./generateValues 15 1 "depthValues.txt"

#run Intel MPI Benchmarks with mpirun - will automatically pick up Slurm parallel environment
mpirun ./autoTest 15 1 "depthValues.txt"

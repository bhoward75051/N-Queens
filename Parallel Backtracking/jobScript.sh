#!/bin/bash --login

###

#Job name
#SBATCH --job-name=nq_bench

#maximum job time in D-HH:MM
#SBATCH --time=0-00:10

#Memory per process in MB
#SBATCH --mem-per-cpu=2000

#Number of parallel processes (Tasks)
#SBATCH --ntasks=15

#Tasks to run per node
#SBATCH --tasks-per-node=4

###
./generateValues 15 1 "depthValues.txt"

#run Intel MPI Benchmarks with mpirun - will automatically pick up Slurm parallel environment
mpirun $MPI_HOME/intel64/bin/IMB-MPI1 15 1 "depthValues.txt"
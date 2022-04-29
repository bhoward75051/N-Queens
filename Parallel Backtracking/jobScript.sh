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

module purge
module load mpich


mpirun ./autoTest 15 1 "depthValues.txt"

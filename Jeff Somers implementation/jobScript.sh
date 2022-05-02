#!/bin/bash --login

###
#SBATCH -p compute
#SBATCH -o runout.%J
#SBATCH -e runerr.%J
#SBATCH -n 64

#SBATCH --job-name=nq_bench

#SBATCH --time=0-02:00

#SBATCH --mem-per-cpu=2000
###

module purge
module load mpi/intel/2020/0

for N in {10..19}
do
    ./generateArray $N $N-4 
    /usr/bin/time -f "%E %U %S" -a -o testResultsBitHPC.txt time mpiexec ./bitwiseParallel $N $N-4
done

#!/usr/bin/zsh

N_START=100000000
N_END=300000000
THREADS_NUMBER=1
PROCESSORS_NUMBER=1

echo "Compiling..."
mpicc -fopenmp -o prog7 -lm src/lab7.c

echo "Working..."
mpirun -nq $THREADS_NUMBER ./prog7 $N_START $N_END $THREADS_NUMBER $PROCESSORS_NUMBER

python3 src/plot.py

echo "Deleting..."
rm prog7 timing.txt


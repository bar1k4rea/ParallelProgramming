#!/usr/bin/zsh

N_START=1
N_END=100
THREADS_NUMBER=2

echo "Compiling..."
mpicc -o prog7 -lm src/lab7.c

echo "Working..."
mpirun -nq $THREADS_NUMBER ./prog7 $N_START $N_END

echo "Deleting..."
rm prog7


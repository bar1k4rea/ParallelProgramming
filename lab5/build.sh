#!/usr/bin/zsh

echo "Compiling"

gcc -fopenmp -o prog1 src/lab1.c
gcc -o creating src/creating.c
mpicc -o prog5 src/lab5.c

echo "Working OpenMP..."
./prog1

echo "Working MPI..."
for ((i = 1; i <= 5; i++))
do
    ./creating 0
    for ((j = 1; j <= 6; j++))
        do
        mpirun -np $j -q ./prog5
        done
done
./creating 1

echo "Deleting"
rm prog1 creating prog5

#!/usr/bin/zsh

ARRAY_SIZE=100000
THREADS_NUMBER=4
TESTS_NUMBER=5

echo "Compiling"
mpicc -o prog6 -lm src/lab6.c
gcc -fopenmp -o prog3 src/lab3.c 

echo "Working OpenMP..."
./prog3 $TESTS_NUMBER $THREADS_NUMBER $ARRAY_SIZE

echo "Working MPI..."
for ((i = 1; i <= $TESTS_NUMBER; i++))
do
    echo "Creating array #$i"
    python3 src/array.py $ARRAY_SIZE

    for ((n = 1; n <= $THREADS_NUMBER; n *= 2))
    do
        echo "Number of theads: $n" 
        mpirun -nq $n ./prog6 $ARRAY_SIZE
    done
done

python3 src/plot.py $TESTS_NUMBER $THREADS_NUMBER

# TODO: report in Latex

echo "Deleting"
rm prog3 prog6 array.txt openmp.txt mpi.txt

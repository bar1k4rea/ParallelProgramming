#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>
#include <omp.h>


int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int threads_number = atoi(argv[3]); 
    int processors_number = atoi(argv[4]);
    if (!rank)
        if (threads_number != size) {
            fprintf(stderr, "Error! Invalid number of threads.\n");
            MPI_Abort(MPI_COMM_WORLD, MPI_ERR_OTHER);
        }
    
    if (!rank)
        if (!(processors_number > threads_number)) {
            fprintf(stderr, "Error! Invalid number of processors.\n");
            MPI_Abort(MPI_COMM_WORLD, MPI_ERR_OTHER);
        }
    int n = processors_number / threads_number;
        
    int start_range = atoi(argv[1]);
    int end_range = atoi(argv[2]);
    const int start_interval = rank * (end_range - start_range) / size + start_range;
    const int end_interval = (rank + 1) * (end_range - start_range) / size + start_range - 1;
    
    // printf("Processor #%d: [%d; %d]\n", rank, start_interval, end_interval);

    double *timing;
    if (!rank)    
        timing = (double *) malloc(size * sizeof(double));
   
    double start_time = MPI_Wtime();
    
    int flag;
#pragma omp parallel for num_threads(n) shared(flag, number) default(none)
    for (int number = start_interval; number <= end_interval; number++) {
        flag = 1;
        int max_divisor = sqrt(number);
  
        for (int d = 2; d <= max_divisor; d++)
            if (number % d == 0) {
                flag = 0;
                break; 
            }
        
        if (flag) {
            // printf("%d - prime number\n", n);
        }
    }

    double end_time = MPI_Wtime();

    printf("Thread #%d: %lf\n", rank, end_time - start_time);
    
    // int period = end_time - start_time;
    int period = 12;
    MPI_Gather(&period, 1, MPI_INTEGER, timing, 1, MPI_INTEGER, 0, MPI_COMM_WORLD);

    if (!rank) {
        printf("Range of numbers: [%d; %d).\n", start_range, end_range);
        
        for (int i = 0; i < size; i++)
            printf("Thread #%d: %lf\n", i, timing[i]);
    }
           
    MPI_Finalize();
    
    return 0;
}

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

    int n_start = atoi(argv[1]);
    int n_end = atoi(argv[2]);
    const int start_index = rank * (n_end - n_start) / size + n_start;
    const int end_index = (rank + 1) * (n_end - n_start) / size + n_start;
    
    //printf("Processor #%d: [%d; %d]\n", rank, start_index, end_index);

    for (int n = start_index; n <= end_index; n++) {
        int flag = 1;
        
        for (int d = 2; d <= sqrt(n); d++)
            if (n % d == 0) {
                flag = 0;
                break; 
            }
        
        if (flag)
            printf("%d - prime number\n", n);
    }
           
    MPI_Finalize();
    
    return 0;
}

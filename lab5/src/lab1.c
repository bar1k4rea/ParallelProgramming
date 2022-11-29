#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define MAX_THREADS_NUM 6
#define ARRAY_SIZE 100000000
#define TESTS_NUM 5

void func(int* array, int n) {
    int max = -1;
#pragma omp parallel num_threads(n) shared(array) reduction(max : max) 
    {
#pragma omp for
        for(int i = 0; i < ARRAY_SIZE; i++)
            if (array[i] > max)
                max = array[i];   
    }
}

int main() {
    double *timing = (double *) malloc(sizeof(double) *  MAX_THREADS_NUM * TESTS_NUM);
    int *array = (int *) malloc(sizeof(int) * ARRAY_SIZE);
    for (int i = 0; i < TESTS_NUM; i++) {
        srand(time(NULL));
        for (int j = 0; j < ARRAY_SIZE; j++)
            array[j] = rand();

        for (int n = 0; n < MAX_THREADS_NUM; n++) {
            double start_time = omp_get_wtime();
            func(array, n + 1);
            double end_time = omp_get_wtime();
            timing[MAX_THREADS_NUM * i + n] = end_time - start_time;
        }
    }

    FILE *fd = fopen("timing_OpenMP.txt", "w");
    fprintf(fd, "%d\n", MAX_THREADS_NUM);
    fprintf(fd, "%d\n", TESTS_NUM);
    for (int i = 0; i < MAX_THREADS_NUM; i++) {
        for (int j = 0; j < TESTS_NUM; j++)
            fprintf(fd, "%lf\t", timing[MAX_THREADS_NUM * j + i]);
        fprintf(fd, "\n");
    } 
    free(timing);
    free(array);
}


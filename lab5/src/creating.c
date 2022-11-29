#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 100000000
#define TESTS_NUM 5
#define MAX_THREADS_NUM 6

int main(int argc, char **argv) {
    int option = atoi(argv[1]);
    switch (option)
    {
       case 0:
            srand(time(NULL));   
            FILE *fd1 = fopen("array.txt", "w");
            for (int i = 0; i < ARRAY_SIZE; i++)
                fprintf(fd1, "%d ", rand());
            fclose(fd1);
            break;
          
        case 1:
            double *timing = (double *) malloc(sizeof(double) * MAX_THREADS_NUM * TESTS_NUM);
            FILE *fd2 = fopen("timing_MPI.txt", "r"); 
            fseek(fd2, 0, SEEK_SET); 
            for (int i = 0; i < MAX_THREADS_NUM * TESTS_NUM; i++) {
                fscanf(fd2, "%lf", &timing[i]); 
            }
            fclose(fd2);

            FILE *fd3 = fopen("timing_MPI.txt", "w");
            fprintf(fd3, "%d\n", MAX_THREADS_NUM);
            fprintf(fd3, "%d\n", TESTS_NUM);
            for (int i = 0; i < MAX_THREADS_NUM; i++) {
                for (int j = 0; j < TESTS_NUM; j++) 
                    fprintf(fd3, "%lf\t", timing[6*j + i]);
                fprintf(fd3, "\n");
            }
            fclose(fd3);
            free(timing);
            break; 
    }

    return 0;
}

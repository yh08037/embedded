#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#include "matrix.h"

void init_matrix(int ***, int ***, int ***, int);
double wtime();
void print_matrix(int**, char *, int);

int main(int argc, char *argv[])
{
    int **a;
    int **b;
    int **c;
    int i, j, k;
    int len, num_thread;
    double start, stop;

    if (argc == 2) {
        len = atoi(argv[1]);
        num_thread = 8;
    } else if (argc == 3) {
        len = atoi(argv[1]);
        num_thread = atoi(argv[2]);
    } else {
        printf("Usage: matrix [row] [num_thread\n");
    }

    init_matrix(&a, &b, &c, len);

    start = wtime();
    if (mat_mul(a, b, c, len) != 0) {
        fprintf(stderr, "mat_mul failed\n");
        exit(1);
    }
    stop = wtime();

    // print_matrix(c, "C", len);

    printf("Processing time: %lf\n", stop - start);
    
    
    for (i = 0; i < len; i++) { // i (Row)
        for (j = 0; j < len; j++) { // j (column)
            c[i][j] = 0;
        }
    }

    start = wtime();
    if (mat_mul_th(a, b, c, len, num_thread) != 0) {
        fprintf(stderr, "mat_mul_th failed\n");
        exit(1);
    }
    stop = wtime();

    // print_matrix(c, "C", len);

    printf("Processing time: %lf\n", stop - start);

    return 0;
}

void init_matrix(int*** p_a, int*** p_b, int*** p_c, int len)
{
    int **a, **b, **c;
    int i, j;
    
    a = (int**)malloc(len * sizeof(int*));
    b = (int**)malloc(len * sizeof(int*));
    c = (int**)malloc(len * sizeof(int*));

    for (i = 0; i < len; i++) {
        a[i] = (int*)malloc(len * sizeof(int));
        b[i] = (int*)malloc(len * sizeof(int));
        c[i] = (int*)malloc(len * sizeof(int));
    }

    srandom((unsigned int)time(NULL));

    for (i = 0; i < len; i++) { // i (Row)
        for (j = 0; j < len; j++) { // j (column)
            a[i][j] = random() % 10;
            b[i][j] = random() % 10;
            c[i][j] = 0;
        }
    }

    *p_a = a;
    *p_b = b;
    *p_c = c;
}

double wtime()
{
    static int sec = -1;
    struct timeval tv;
    gettimeofday(&tv, NULL);

    if (sec < 0)
        sec = tv.tv_sec;

    return (tv.tv_sec - sec) + 1.0e-6*tv.tv_usec;
}

void print_matrix(int **matrix, char *name, int len)
{
    printf("== %s matrix ========================\n", name);
    for (int i = 0; i < len; i++) { // i (Row)
        for (int j = 0; j < len; j++) { // j (column)
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}
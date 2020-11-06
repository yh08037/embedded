#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int mat_mul(int **, int **, int **, int);
int mat_mul_th(int **, int **, int **, int, int);

void init_matrix(int ***, int ***, int ***, int);
void free_matrix(int **, int **, int **, int);
void print_matrix(int **, char *, int);

typedef struct {
    int i;
    int **src1;
    int **src2;
    int **dst;
    int len;
    int num_thread;
} matmul_arg_t;

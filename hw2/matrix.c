#include "matrix.h"


int mat_mul(int** src1, int** src2, int** dst, int len)
{
    int i, j, k;
    int result;

    for (i = 0; i < len; i++) { // i (Row)
        for (j = 0; j < len; j++) { // j (column)
            result = 0;
            for (k = 0; k < len; k++) {
                result += src1[i][k] * src2[k][j];
            }
            dst[i][j] = result;
        }
    }

    return 0;
}

void* mat_mul_th_kernel(void *arg)
{
    int j, k, result;
    matmul_arg_t *p_arg = (matmul_arg_t*)arg;

    int i          = p_arg->i;
    int **src1     = p_arg->src1;
    int **src2     = p_arg->src2;
    int **dst      = p_arg->dst;
    int len        = p_arg->len;
    int num_thread = p_arg->num_thread;

    // printf("Thread %d started\n", i);

    for (; i < len; i += num_thread) {
        for (j = 0; j < len; j++) {
            result = 0;
            for (k = 0; k < len; k++) {
                result += src1[i][k] * src2[k][j];
            }
            dst[i][j] = result;
        }
    }
}

int mat_mul_th(int** src1, int** src2, int** dst, int len, int num_thread)
{
    int             i, res;
    matmul_arg_t    *arg;
    pthread_t       *a_thread;
    void            *thread_result;

    arg = (matmul_arg_t*)malloc(sizeof(matmul_arg_t) * num_thread);
    a_thread = (pthread_t*)malloc(sizeof(pthread_t) * num_thread);

    for (i = 0; i < num_thread; i++) {
        (arg+i)->i          = i;
        (arg+i)->src1       = src1;
        (arg+i)->src2       = src2;
        (arg+i)->dst        = dst;
        (arg+i)->len        = len;
        (arg+i)->num_thread = num_thread;

        // printf("Thread %d called\n", i);

        res = pthread_create(a_thread+i, NULL, mat_mul_th_kernel, (void*)(arg+i));
        if (res != 0) {
            perror("Thread creation failed");
            exit(EXIT_FAILURE);
        }
    }

    for (i = 0; i < num_thread; i++) {
        res = pthread_join(a_thread[i], &thread_result);
        if (res != 0) {
            perror("Thread join failed");
            exit(EXIT_FAILURE);
        }
    }

    free(arg);
    free(a_thread);

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

void free_matrix(int **a, int **b, int **c, int len)
{
    for (int i = 0; i < len; i++) {
        free(a[i]);
        free(b[i]);
        free(c[i]);
    }
    free(a);
    free(b);
    free(c);
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
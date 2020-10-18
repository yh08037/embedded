#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>


int mat_add(int** src1, int** src2, int** dst, int len)
{

}

int mat_sub(int** src1, int** src2, int** dst, int len)
{

}

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

typedef struct {
    int i;
    int** src1;
    int** src2;
    int** dst;
    int len;
    int num_thread;
} matmul_arg_t;

void* mat_mul_th_kernel(void *arg)
{
    int j, k, result;
    matmul_arg_t *p_arg = (matmul_arg_t*)arg;

    int i = p_arg->i;
    int** src1 = p_arg->src1;
    int** src2 = p_arg->src2;
    int** dst = p_arg->dst;
    int len = p_arg->len;
    int num_thread = p_arg->num_thread;

    // printf("Thread %d started\n", i);

    for (; i < len; i += num_thread) {
        for (j = 0; j < len; j++) { // j (column)
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
        (arg+i)->i = i;
        (arg+i)->src1 = src1;
        (arg+i)->src2 = src2;
        (arg+i)->dst = dst;
        (arg+i)->len = len;
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

int mat_inv(int** src, int** dst, int len)
{

}

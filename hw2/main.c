#include <sys/time.h>
#include "matrix.h"

double wtime();

int main(int argc, char *argv[])
{
    int **a;
    int **b;
    int **c;
    int i, j, k;
    int len, num_thread;
    double start, stop;
    double single, multi;

    if (argc == 2) {
        len = atoi(argv[1]);
        num_thread = 4;
    } else if (argc == 3) {
        len = atoi(argv[1]);
        num_thread = atoi(argv[2]);
    } else {
        printf("Usage: matrix [row] [num_thread]\n");
	exit(1);
    }

    init_matrix(&a, &b, &c, len);

    start = wtime();
    if (mat_mul(a, b, c, len) != 0) {
        fprintf(stderr, "mat_mul failed\n");
        exit(1);
    }
    stop = wtime();

    // print_matrix(c, "C", len);

    printf("Processing time: %lf\n", single = stop - start);
    
    
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

    printf("Processing time: %lf\n", multi = stop - start);

    if (single > multi)
        printf("mat_mul_th is %lf times faster\n", single/multi);
    else
        printf("mat_mul is %lf times faster\n", multi/single);
    
    free_matrix(a, b, c, len);

    return 0;
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

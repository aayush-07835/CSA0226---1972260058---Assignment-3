#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DISTRICTS 38
#define MONTHS 12

int main(void)
{
    /* Array of 38 pointers, each pointing to a separately allocated 12-double row */
    double *rows[DISTRICTS];
    for (int i = 0; i < DISTRICTS; i++) {
        rows[i] = malloc(MONTHS * sizeof(double));
        if (!rows[i]) return 1;
        for (int j = 0; j < MONTHS; j++) {
            rows[i][j] = 80.0 + ((i * 7 + j * 3) % 45);
        }
    }

    double d0_total = 0.0;
    for (int j = 0; j < MONTHS; j++) {
        d0_total += rows[0][j];
    }
    printf("Pointer-Array (double *rows[38]) -> District 1 Total = %.2f mm, Pointer Overhead = %zu bytes\n",
           d0_total, sizeof(rows));

    for (int i = 0; i < DISTRICTS; i++) free(rows[i]);

    /* Benchmark 2000 x 2000 pointer-to-pointer traversal */
    const int N = 2000;
    double **ptr_grid = malloc((size_t)N * sizeof(double *));
    if (!ptr_grid) return 1;
    for (int i = 0; i < N; i++) {
        ptr_grid[i] = malloc((size_t)N * sizeof(double));
        for (int j = 0; j < N; j++) ptr_grid[i][j] = (double)((i + j) % 100);
    }

    struct timespec t0, t1;
    clock_gettime(CLOCK_MONOTONIC, &t0);
    double sum = 0.0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            sum += ptr_grid[i][j];
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &t1);
    double ms = (t1.tv_sec - t0.tv_sec) * 1000.0 + (t1.tv_nsec - t0.tv_nsec) / 1e6;
    printf("Pointer-Array 2000x2000 Row-Wise Traversal: %.4f ms (sum = %.0f)\n", ms, sum);

    for (int i = 0; i < N; i++) free(ptr_grid[i]);
    free(ptr_grid);
    return 0;
}

#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DISTRICTS 38
#define MONTHS 12

int main(void)
{
    /* 1D contiguous array representing 38 x 12 via index i * 12 + j */
    double rain1d[DISTRICTS * MONTHS];
    for (int i = 0; i < DISTRICTS; i++) {
        for (int j = 0; j < MONTHS; j++) {
            rain1d[i * MONTHS + j] = 80.0 + ((i * 7 + j * 3) % 45);
        }
    }

    double d0_total = 0.0;
    for (int j = 0; j < MONTHS; j++) {
        d0_total += rain1d[0 * MONTHS + j];
    }
    printf("1D Contiguous Mapping (i * 12 + j) -> District 1 Annual Total = %.2f mm\n", d0_total);

    /* Benchmark 2000 x 2000 flat 1D traversal */
    const int N = 2000;
    double *flat = malloc((size_t)N * N * sizeof(double));
    if (!flat) return 1;
    for (int i = 0; i < N * N; i++) flat[i] = (double)(i % 100);

    struct timespec t0, t1;
    clock_gettime(CLOCK_MONOTONIC, &t0);
    double sum = 0.0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            sum += flat[i * N + j];
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &t1);
    double ms = (t1.tv_sec - t0.tv_sec) * 1000.0 + (t1.tv_nsec - t0.tv_nsec) / 1e6;
    printf("1D Flat 2000x2000 Row-Wise Traversal: %.4f ms (sum = %.0f)\n", ms, sum);

    free(flat);
    return 0;
}

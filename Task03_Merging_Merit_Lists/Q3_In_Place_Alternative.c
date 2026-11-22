#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Simple in-place merge of two descending sorted arrays a[0..na-1] and b[0..nb-1]
 * Time complexity: O(na * nb), Extra space: O(1) */
void inplace_merge_desc(int a[], int na, int b[], int nb, long long *comps, long long *shifts)
{
    *comps = 0;
    *shifts = 0;
    for (int i = 0; i < na; i++) {
        (*comps)++;
        if (b[0] > a[i]) {
            int tmp = a[i];
            a[i] = b[0];
            (*shifts)++;

            /* Re-insert tmp into b[] in descending order */
            int k = 1;
            while (k < nb) {
                (*comps)++;
                if (b[k] > tmp) {
                    b[k - 1] = b[k];
                    (*shifts)++;
                    k++;
                } else {
                    break;
                }
            }
            b[k - 1] = tmp;
        }
    }
}

int main(void)
{
    int a[] = {98, 91, 85, 72};
    int b[] = {95, 91, 80};
    long long comps = 0, shifts = 0;

    inplace_merge_desc(a, 4, b, 3, &comps, &shifts);

    printf("In-place merged (A then B): ");
    for (int i = 0; i < 4; i++) printf("%d ", a[i]);
    for (int j = 0; j < 3; j++) printf("%d ", b[j]);
    printf("\nComparisons = %lld, Shifts/Moves = %lld\n", comps, shifts);

    /* Benchmark for m = n = 1000 */
    int m = 1000, n = 1000;
    int *ba = malloc((size_t)m * sizeof(int));
    int *bb = malloc((size_t)n * sizeof(int));
    if (ba && bb) {
        for (int i = 0; i < m; i++) ba[i] = 100000 - i * 2;
        for (int j = 0; j < n; j++) bb[j] = 100000 - j * 2 - 1;
        struct timespec t0, t1;
        clock_gettime(CLOCK_MONOTONIC, &t0);
        inplace_merge_desc(ba, m, bb, n, &comps, &shifts);
        clock_gettime(CLOCK_MONOTONIC, &t1);
        double ms = (t1.tv_sec - t0.tv_sec) * 1000.0 + (t1.tv_nsec - t0.tv_nsec) / 1e6;
        printf("m=n=1000 In-Place -> comps=%lld, shifts=%lld, time=%.4f ms\n", comps, shifts, ms);
    }
    free(ba);
    free(bb);
    return 0;
}

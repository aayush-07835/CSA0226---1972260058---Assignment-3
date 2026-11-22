#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Linear search on an array (works on unsorted or sorted data).
 * Counts each element comparison in *comparisons. */
int linear_search(const int a[], int n, int key, long long *comparisons)
{
    *comparisons = 0;
    for (int i = 0; i < n; i++) {
        (*comparisons)++;
        if (a[i] == key) {
            return i;
        }
    }
    return -1;
}

/* Deterministic pseudo-random generator for reproducible unsorted arrays */
static unsigned int lcg_state = 123456789u;
static int next_rand(void)
{
    lcg_state = 1664525u * lcg_state + 1013904223u;
    return (int)((lcg_state >> 16) & 0x7FFF);
}

int main(void)
{
    /* Trial 10-book unsorted catalogue */
    int trial_unsorted[] = {1305, 1021, 1533, 1190, 1048, 1460, 1103, 1377, 1222, 1402};
    int n_trial = sizeof(trial_unsorted) / sizeof(trial_unsorted[0]);
    int test_keys[] = {1305, 1048, 1402, 1400}; /* first, middle, last, missing */
    const char *labels[] = {"First", "Middle", "Last", "Missing"};

    printf("=== Trial Catalogue (n = %d, Unsorted) - Linear Search ===\n", n_trial);
    for (int i = 0; i < 4; i++) {
        long long comps = 0;
        int idx = linear_search(trial_unsorted, n_trial, test_keys[i], &comps);
        printf("%-7s | Key %d -> index %2d, comparisons = %lld\n",
               labels[i], test_keys[i], idx, comps);
    }

    /* Scaled experiments: n = 1,000, 10,000, 100,000 */
    int sizes[] = {1000, 10000, 100000};
    printf("\n=== Scaled Linear Search Benchmark ===\n");
    printf("%-10s %-12s %-14s %-15s\n", "Size", "Case", "Comparisons", "Time(ms)");

    for (int s = 0; s < 3; s++) {
        int n = sizes[s];
        int *arr = malloc((size_t)n * sizeof(int));
        if (!arr) {
            fprintf(stderr, "Memory allocation failed for n=%d\n", n);
            return 1;
        }
        lcg_state = 42u + (unsigned int)s;
        for (int i = 0; i < n; i++) {
            arr[i] = 100000 + i * 3 + (next_rand() % 2);
        }

        int keys[4] = {arr[0], arr[n / 2], arr[n - 1], -999999};
        const char *case_names[4] = {"First", "Middle", "Last", "Missing"};

        for (int c = 0; c < 4; c++) {
            long long comps = 0;
            struct timespec t0, t1;
            clock_gettime(CLOCK_MONOTONIC, &t0);
            int idx = linear_search(arr, n, keys[c], &comps);
            clock_gettime(CLOCK_MONOTONIC, &t1);
            double ms = (t1.tv_sec - t0.tv_sec) * 1000.0 +
                        (t1.tv_nsec - t0.tv_nsec) / 1e6;
            (void)idx;
            printf("%-10d %-12s %-14lld %-15.6f\n", n, case_names[c], comps, ms);
        }
        free(arr);
    }

    return 0;
}

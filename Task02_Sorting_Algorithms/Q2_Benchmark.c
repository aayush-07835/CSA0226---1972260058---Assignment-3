#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void bubble_sort(int a[], int n, long long *comps, long long *swaps)
{
    *comps = 0;
    *swaps = 0;
    for (int i = 0; i < n - 1; i++) {
        int swapped = 0;
        for (int j = 0; j < n - 1 - i; j++) {
            (*comps)++;
            if (a[j] > a[j + 1]) {
                int t = a[j]; a[j] = a[j + 1]; a[j + 1] = t;
                (*swaps)++;
                swapped = 1;
            }
        }
        if (!swapped) break;
    }
}

void selection_sort(int a[], int n, long long *comps, long long *swaps)
{
    *comps = 0;
    *swaps = 0;
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            (*comps)++;
            if (a[j] < a[min_idx]) min_idx = j;
        }
        if (min_idx != i) {
            int t = a[i]; a[i] = a[min_idx]; a[min_idx] = t;
            (*swaps)++;
        }
    }
}

void insertion_sort(int a[], int n, long long *comps, long long *shifts)
{
    *comps = 0;
    *shifts = 0;
    for (int i = 1; i < n; i++) {
        int key = a[i], j = i - 1;
        while (j >= 0) {
            (*comps)++;
            if (a[j] > key) {
                a[j + 1] = a[j];
                (*shifts)++;
                j--;
            } else {
                break;
            }
        }
        a[j + 1] = key;
    }
}

/* Counting Sort for integers in range [0, max_val] */
void counting_sort(int a[], int n, int max_val)
{
    int *count = calloc((size_t)(max_val + 1), sizeof(int));
    int *output = malloc((size_t)n * sizeof(int));
    if (!count || !output) { free(count); free(output); return; }

    for (int i = 0; i < n; i++) count[a[i]]++;
    for (int i = 1; i <= max_val; i++) count[i] += count[i - 1];
    for (int i = n - 1; i >= 0; i--) {
        output[count[a[i]] - 1] = a[i];
        count[a[i]]--;
    }
    memcpy(a, output, (size_t)n * sizeof(int));
    free(count);
    free(output);
}

static int is_sorted(const int a[], int n)
{
    for (int i = 1; i < n; i++) {
        if (a[i] < a[i - 1]) return 0;
    }
    return 1;
}

static unsigned int lcg = 987654321u;
static int next_rand(void)
{
    lcg = 1664525u * lcg + 1013904223u;
    return (int)((lcg >> 16) & 0x7FFF);
}

static void fill_array(int a[], int n, int order_type)
{
    /* 0: Sorted, 1: Nearly Sorted (5% adjacent swaps), 2: Reverse Sorted, 3: Random */
    for (int i = 0; i < n; i++) a[i] = i + 1;

    if (order_type == 1) {
        int swaps = n / 20;
        if (swaps < 1) swaps = 1;
        lcg = 2026u;
        for (int k = 0; k < swaps; k++) {
            int idx = next_rand() % (n - 1);
            int t = a[idx]; a[idx] = a[idx + 1]; a[idx + 1] = t;
        }
    } else if (order_type == 2) {
        for (int i = 0; i < n; i++) a[i] = n - i;
    } else if (order_type == 3) {
        lcg = 13579u;
        for (int i = 0; i < n; i++) a[i] = next_rand() % 10000;
    }
}

int main(void)
{
    int sizes[] = {100, 1000, 10000};
    const char *orders[] = {"Sorted", "Nearly_Sorted", "Reverse_Sorted", "Random"};

    FILE *f_cmp = fopen("comparison_counts.csv", "w");
    FILE *f_trc = fopen("sorting_traces.csv", "w");
    if (!f_cmp || !f_trc) return 1;

    fprintf(f_cmp, "algorithm,array_size,input_order,comparisons,swaps_or_shifts,time_ms,verified_sorted\n");
    fprintf(f_trc, "algorithm,pass,array_state,comparisons_so_far,swaps_or_shifts_so_far\n");

    /* Generate 6-element trace for sorting_traces.csv */
    int base_trace[6] = {105, 102, 108, 101, 104, 103};
    {
        int a[6]; memcpy(a, base_trace, sizeof(a));
        long long c = 0, s = 0;
        for (int i = 0; i < 5; i++) {
            int sw = 0;
            for (int j = 0; j < 5 - i; j++) {
                c++;
                if (a[j] > a[j + 1]) { int t = a[j]; a[j] = a[j + 1]; a[j + 1] = t; s++; sw = 1; }
            }
            fprintf(f_trc, "Bubble_Sort,%d,\"%d %d %d %d %d %d\",%lld,%lld\n",
                    i + 1, a[0], a[1], a[2], a[3], a[4], a[5], c, s);
            if (!sw) break;
        }
    }
    {
        int a[6]; memcpy(a, base_trace, sizeof(a));
        long long c = 0, s = 0;
        for (int i = 0; i < 5; i++) {
            int m = i;
            for (int j = i + 1; j < 6; j++) { c++; if (a[j] < a[m]) m = j; }
            if (m != i) { int t = a[i]; a[i] = a[m]; a[m] = t; s++; }
            fprintf(f_trc, "Selection_Sort,%d,\"%d %d %d %d %d %d\",%lld,%lld\n",
                    i + 1, a[0], a[1], a[2], a[3], a[4], a[5], c, s);
        }
    }
    {
        int a[6]; memcpy(a, base_trace, sizeof(a));
        long long c = 0, s = 0;
        for (int i = 1; i < 6; i++) {
            int key = a[i], j = i - 1;
            while (j >= 0) {
                c++;
                if (a[j] > key) { a[j + 1] = a[j]; s++; j--; } else break;
            }
            a[j + 1] = key;
            fprintf(f_trc, "Insertion_Sort,%d,\"%d %d %d %d %d %d\",%lld,%lld\n",
                    i, a[0], a[1], a[2], a[3], a[4], a[5], c, s);
        }
    }

    printf("=== Task 2: Sorting Benchmark (n = 100, 1000, 10000) ===\n");
    for (int si = 0; si < 3; si++) {
        int n = sizes[si];
        int *orig = malloc((size_t)n * sizeof(int));
        int *work = malloc((size_t)n * sizeof(int));
        if (!orig || !work) return 1;

        for (int oi = 0; oi < 4; oi++) {
            fill_array(orig, n, oi);
            long long comps = 0, ops = 0;
            struct timespec t0, t1;
            double ms;

            /* Bubble Sort */
            memcpy(work, orig, (size_t)n * sizeof(int));
            clock_gettime(CLOCK_MONOTONIC, &t0);
            bubble_sort(work, n, &comps, &ops);
            clock_gettime(CLOCK_MONOTONIC, &t1);
            ms = (t1.tv_sec - t0.tv_sec) * 1000.0 + (t1.tv_nsec - t0.tv_nsec) / 1e6;
            fprintf(f_cmp, "Bubble_Sort,%d,%s,%lld,%lld,%.4f,%d\n", n, orders[oi], comps, ops, ms, is_sorted(work, n));

            /* Selection Sort */
            memcpy(work, orig, (size_t)n * sizeof(int));
            clock_gettime(CLOCK_MONOTONIC, &t0);
            selection_sort(work, n, &comps, &ops);
            clock_gettime(CLOCK_MONOTONIC, &t1);
            ms = (t1.tv_sec - t0.tv_sec) * 1000.0 + (t1.tv_nsec - t0.tv_nsec) / 1e6;
            fprintf(f_cmp, "Selection_Sort,%d,%s,%lld,%lld,%.4f,%d\n", n, orders[oi], comps, ops, ms, is_sorted(work, n));

            /* Insertion Sort */
            memcpy(work, orig, (size_t)n * sizeof(int));
            clock_gettime(CLOCK_MONOTONIC, &t0);
            insertion_sort(work, n, &comps, &ops);
            clock_gettime(CLOCK_MONOTONIC, &t1);
            ms = (t1.tv_sec - t0.tv_sec) * 1000.0 + (t1.tv_nsec - t0.tv_nsec) / 1e6;
            fprintf(f_cmp, "Insertion_Sort,%d,%s,%lld,%lld,%.4f,%d\n", n, orders[oi], comps, ops, ms, is_sorted(work, n));

            /* Counting Sort on Random order as O(n+k) alternative */
            if (oi == 3) {
                memcpy(work, orig, (size_t)n * sizeof(int));
                clock_gettime(CLOCK_MONOTONIC, &t0);
                counting_sort(work, n, 10000);
                clock_gettime(CLOCK_MONOTONIC, &t1);
                ms = (t1.tv_sec - t0.tv_sec) * 1000.0 + (t1.tv_nsec - t0.tv_nsec) / 1e6;
                fprintf(f_cmp, "Counting_Sort,%d,%s,0,0,%.4f,%d\n", n, orders[oi], ms, is_sorted(work, n));
            }
        }
        free(orig);
        free(work);
    }

    fclose(f_cmp);
    fclose(f_trc);
    printf("Generated comparison_counts.csv and sorting_traces.csv successfully.\n");
    return 0;
}

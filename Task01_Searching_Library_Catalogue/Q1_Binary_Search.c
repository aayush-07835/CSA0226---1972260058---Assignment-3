#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int binary_search_counted(const int a[], int n, int key, long long *comparisons)
{
    *comparisons = 0;
    int low = 0;
    int high = n - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        (*comparisons)++;
        if (a[mid] == key) {
            return mid;
        } else if (a[mid] < key) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

int linear_search_counted(const int a[], int n, int key, long long *comparisons)
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

int main(void)
{
    int sizes[] = {1000, 10000, 100000};

    FILE *f_res = fopen("search_results.csv", "w");
    FILE *f_cmp = fopen("comparison_analysis.csv", "w");
    if (!f_res || !f_cmp) {
        fprintf(stderr, "Failed to open CSV files for writing.\n");
        return 1;
    }

    fprintf(f_res, "algorithm,array_size,case_type,key,found_index,comparisons,time_ms\n");
    fprintf(f_cmp, "array_size,linear_best,linear_avg_found,linear_worst_missing,binary_best,binary_avg_found,binary_worst_missing\n");

    printf("=== Task 1: Binary vs Linear Search Benchmark ===\n");
    for (int s = 0; s < 3; s++) {
        int n = sizes[s];
        int *arr = malloc((size_t)n * sizeof(int));
        if (!arr) return 1;

        for (int i = 0; i < n; i++) {
            arr[i] = 100000 + i * 2; /* deterministic sorted accession numbers */
        }

        int keys[4] = {arr[0], arr[n / 2], arr[n - 1], 999999};
        const char *cases[4] = {"First", "Middle", "Last", "Missing"};

        for (int c = 0; c < 4; c++) {
            long long lin_c = 0, bin_c = 0;
            struct timespec t0, t1;

            clock_gettime(CLOCK_MONOTONIC, &t0);
            int l_idx = linear_search_counted(arr, n, keys[c], &lin_c);
            clock_gettime(CLOCK_MONOTONIC, &t1);
            double l_ms = (t1.tv_sec - t0.tv_sec) * 1000.0 + (t1.tv_nsec - t0.tv_nsec) / 1e6;

            clock_gettime(CLOCK_MONOTONIC, &t0);
            int b_idx = binary_search_counted(arr, n, keys[c], &bin_c);
            clock_gettime(CLOCK_MONOTONIC, &t1);
            double b_ms = (t1.tv_sec - t0.tv_sec) * 1000.0 + (t1.tv_nsec - t0.tv_nsec) / 1e6;

            fprintf(f_res, "Linear,%d,%s,%d,%d,%lld,%.6f\n", n, cases[c], keys[c], l_idx, lin_c, l_ms);
            fprintf(f_res, "Binary,%d,%s,%d,%d,%lld,%.6f\n", n, cases[c], keys[c], b_idx, bin_c, b_ms);
        }

        /* Average successful search over 100 evenly spaced keys */
        long long lin_sum = 0, bin_sum = 0;
        int samples = 100;
        for (int k = 0; k < samples; k++) {
            int target_idx = (k * (n - 1)) / (samples - 1);
            long long lc = 0, bc = 0;
            linear_search_counted(arr, n, arr[target_idx], &lc);
            binary_search_counted(arr, n, arr[target_idx], &bc);
            lin_sum += lc;
            bin_sum += bc;
        }
        long long lin_best = 0, bin_best = 0, lin_miss = 0, bin_miss = 0;
        linear_search_counted(arr, n, arr[0], &lin_best);
        binary_search_counted(arr, n, arr[(n - 1) / 2], &bin_best);
        linear_search_counted(arr, n, 999999, &lin_miss);
        binary_search_counted(arr, n, 999999, &bin_miss);

        double lin_avg = (double)lin_sum / samples;
        double bin_avg = (double)bin_sum / samples;

        fprintf(f_cmp, "%d,%lld,%.2f,%lld,%lld,%.2f,%lld\n",
                n, lin_best, lin_avg, lin_miss, bin_best, bin_avg, bin_miss);

        printf("n = %6d | Linear avg = %8.2f, missing = %6lld | Binary avg = %5.2f, missing = %2lld\n",
               n, lin_avg, lin_miss, bin_avg, bin_miss);

        free(arr);
    }

    fclose(f_res);
    fclose(f_cmp);
    printf("CSV files written: search_results.csv, comparison_analysis.csv\n");
    return 0;
}

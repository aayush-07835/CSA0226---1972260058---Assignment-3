#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NAME_LEN 30

static void generate_names(char (*names)[NAME_LEN], int n)
{
    const char *first[] = {"Aarav", "Bhavna", "Charan", "Divya", "Eshan", "Farah", "Gokul", "Harini", "Ishaan", "Janani"};
    const char *last[]  = {"Sharma", "Nair", "Iyer", "Patel", "Kumar", "Reddy", "Menon", "Rao", "Verma", "Pillai"};
    unsigned int lcg = 54321u;
    for (int i = 0; i < n; i++) {
        lcg = 1664525u * lcg + 1013904223u;
        int f = (int)((lcg >> 16) % 10);
        lcg = 1664525u * lcg + 1013904223u;
        int l = (int)((lcg >> 16) % 10);
        snprintf(names[i], NAME_LEN, "%s %s %04d", first[f], last[l], i);
    }
}

void sort_by_strcpy(char (*names)[NAME_LEN], int n, long long *cmps, long long *copies)
{
    *cmps = 0; *copies = 0;
    char tmp[NAME_LEN];
    for (int i = 0; i < n - 1; i++) {
        int swapped = 0;
        for (int j = 0; j < n - 1 - i; j++) {
            (*cmps)++;
            if (strcmp(names[j], names[j + 1]) > 0) {
                *copies += (long long)(strlen(names[j]) + strlen(names[j + 1]) + strlen(names[j]) + 3);
                strcpy(tmp, names[j]);
                strcpy(names[j], names[j + 1]);
                strcpy(names[j + 1], tmp);
                swapped = 1;
            }
        }
        if (!swapped) break;
    }
}

void sort_by_index(char (*names)[NAME_LEN], int idx[], int n, long long *cmps, long long *int_swaps)
{
    *cmps = 0; *int_swaps = 0;
    for (int i = 0; i < n; i++) idx[i] = i;

    for (int i = 0; i < n - 1; i++) {
        int swapped = 0;
        for (int j = 0; j < n - 1 - i; j++) {
            (*cmps)++;
            if (strcmp(names[idx[j]], names[idx[j + 1]]) > 0) {
                int t = idx[j];
                idx[j] = idx[j + 1];
                idx[j + 1] = t;
                (*int_swaps)++;
                swapped = 1;
            }
        }
        if (!swapped) break;
    }
}

int main(void)
{
    int sizes[] = {100, 500, 5000};
    FILE *f_cmp = fopen("comparison_counts.csv", "w");
    FILE *f_res = fopen("resident_names.csv", "w");
    if (!f_cmp || !f_res) return 1;

    fprintf(f_cmp, "method,n_names,strcmp_calls,char_copies,int_or_ptr_swaps,time_ms\n");

    for (int s = 0; s < 3; s++) {
        int n = sizes[s];
        char (*names1)[NAME_LEN] = malloc((size_t)n * sizeof(*names1));
        char (*names2)[NAME_LEN] = malloc((size_t)n * sizeof(*names2));
        int *idx = malloc((size_t)n * sizeof(int));
        if (!names1 || !names2 || !idx) return 1;

        generate_names(names1, n);
        memcpy(names2, names1, (size_t)n * sizeof(*names1));

        if (n == 100) {
            fprintf(f_res, "id,resident_name\n");
            for (int i = 0; i < n; i++) fprintf(f_res, "%d,%s\n", i + 1, names1[i]);
        }

        long long cmps1 = 0, copies1 = 0, cmps2 = 0, swaps2 = 0;
        struct timespec t0, t1;

        clock_gettime(CLOCK_MONOTONIC, &t0);
        sort_by_strcpy(names1, n, &cmps1, &copies1);
        clock_gettime(CLOCK_MONOTONIC, &t1);
        double ms1 = (t1.tv_sec - t0.tv_sec) * 1000.0 + (t1.tv_nsec - t0.tv_nsec) / 1e6;
        fprintf(f_cmp, "Strcpy_Bubble_Sort,%d,%lld,%lld,0,%.4f\n", n, cmps1, copies1, ms1);

        clock_gettime(CLOCK_MONOTONIC, &t0);
        sort_by_index(names2, idx, n, &cmps2, &swaps2);
        clock_gettime(CLOCK_MONOTONIC, &t1);
        double ms2 = (t1.tv_sec - t0.tv_sec) * 1000.0 + (t1.tv_nsec - t0.tv_nsec) / 1e6;
        fprintf(f_cmp, "Index_Bubble_Sort,%d,%lld,0,%lld,%.4f\n", n, cmps2, swaps2, ms2);

        printf("n = %4d | strcpy: %.2f ms (%lld char copies) | index: %.2f ms (%lld int swaps, 0 char copies)\n",
               n, ms1, copies1, ms2, swaps2);

        free(names1); free(names2); free(idx);
    }

    fclose(f_cmp);
    fclose(f_res);
    return 0;
}

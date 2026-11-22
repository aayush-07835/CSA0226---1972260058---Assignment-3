#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define CANDIDATES 12

static int cmp_int_asc(const void *a, const void *b)
{
    int va = *(const int *)a;
    int vb = *(const int *)b;
    return (va > vb) - (va < vb);
}

/* Method 1: O(v) single-pass count array */
static double bench_count_array(const int *votes, int v, int counts[])
{
    struct timespec t0, t1;
    clock_gettime(CLOCK_MONOTONIC, &t0);
    memset(counts, 0, (size_t)(CANDIDATES + 1) * sizeof(int));
    int invalid = 0;
    for (int i = 0; i < v; i++) {
        if (votes[i] >= 1 && votes[i] <= CANDIDATES) counts[votes[i]]++;
        else invalid++;
    }
    clock_gettime(CLOCK_MONOTONIC, &t1);
    (void)invalid;
    return (t1.tv_sec - t0.tv_sec) * 1000.0 + (t1.tv_nsec - t0.tv_nsec) / 1e6;
}

/* Method 2: O(v * c) linear scan of candidate ID list for each vote */
static double bench_linear_candidate_scan(const int *votes, int v, int counts[])
{
    int cand_ids[CANDIDATES];
    for (int c = 0; c < CANDIDATES; c++) cand_ids[c] = c + 1;

    struct timespec t0, t1;
    clock_gettime(CLOCK_MONOTONIC, &t0);
    memset(counts, 0, (size_t)(CANDIDATES + 1) * sizeof(int));
    int invalid = 0;
    for (int i = 0; i < v; i++) {
        int found = 0;
        for (int c = 0; c < CANDIDATES; c++) {
            if (votes[i] == cand_ids[c]) {
                counts[cand_ids[c]]++;
                found = 1;
                break;
            }
        }
        if (!found) invalid++;
    }
    clock_gettime(CLOCK_MONOTONIC, &t1);
    (void)invalid;
    return (t1.tv_sec - t0.tv_sec) * 1000.0 + (t1.tv_nsec - t0.tv_nsec) / 1e6;
}

/* Method 3: O(v log v) sort all votes then count consecutive runs */
static double bench_sort_votes(const int *votes_src, int v, int counts[])
{
    int *votes = malloc((size_t)v * sizeof(int));
    if (!votes) return -1.0;
    memcpy(votes, votes_src, (size_t)v * sizeof(int));

    struct timespec t0, t1;
    clock_gettime(CLOCK_MONOTONIC, &t0);
    qsort(votes, (size_t)v, sizeof(int), cmp_int_asc);
    memset(counts, 0, (size_t)(CANDIDATES + 1) * sizeof(int));
    int i = 0;
    while (i < v) {
        int val = votes[i], run = 0;
        while (i < v && votes[i] == val) { run++; i++; }
        if (val >= 1 && val <= CANDIDATES) counts[val] = run;
    }
    clock_gettime(CLOCK_MONOTONIC, &t1);
    free(votes);
    return (t1.tv_sec - t0.tv_sec) * 1000.0 + (t1.tv_nsec - t0.tv_nsec) / 1e6;
}

int main(void)
{
    int vote_sizes[] = {5000, 500000};
    FILE *f_csv = fopen("performance_comparison.csv", "w");
    if (!f_csv) return 1;
    fprintf(f_csv, "method,votes_v,candidates_c,complexity,time_ms\n");

    for (int s = 0; s < 2; s++) {
        int v = vote_sizes[s];
        int *votes = malloc((size_t)v * sizeof(int));
        if (!votes) return 1;

        unsigned int lcg = 77777u;
        for (int i = 0; i < v; i++) {
            lcg = 1664525u * lcg + 1013904223u;
            int r = (int)((lcg >> 16) % 100);
            votes[i] = (r < 3) ? 0 : ((int)((lcg >> 8) % CANDIDATES) + 1);
        }

        int c1[CANDIDATES + 1], c2[CANDIDATES + 1], c3[CANDIDATES + 1];
        double ms1 = bench_count_array(votes, v, c1);
        double ms2 = bench_linear_candidate_scan(votes, v, c2);
        double ms3 = bench_sort_votes(votes, v, c3);

        fprintf(f_csv, "Count_Array,%d,%d,O(v),%.4f\n", v, CANDIDATES, ms1);
        fprintf(f_csv, "Candidate_List_Search,%d,%d,O(v*c),%.4f\n", v, CANDIDATES, ms2);
        fprintf(f_csv, "Sort_All_Votes,%d,%d,O(v log v),%.4f\n", v, CANDIDATES, ms3);

        printf("v = %6d | Count Array: %7.4f ms | Linear Search: %7.4f ms | Sort Votes: %8.4f ms\n",
               v, ms1, ms2, ms3);

        free(votes);
    }

    fclose(f_csv);
    return 0;
}

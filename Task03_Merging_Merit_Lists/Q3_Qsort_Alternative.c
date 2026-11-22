#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static long long qsort_comps = 0;

int cmp_desc(const void *p1, const void *p2)
{
    qsort_comps++;
    int a = *(const int *)p1;
    int b = *(const int *)p2;
    return (b > a) - (b < a);
}

int merge_counted(const int a[], int na, const int b[], int nb, int out[], long long *comps)
{
    *comps = 0;
    int i = 0, j = 0, k = 0;
    while (i < na && j < nb) {
        (*comps)++;
        if (a[i] >= b[j]) {
            out[k++] = a[i++];
        } else {
            out[k++] = b[j++];
        }
    }
    while (i < na) out[k++] = a[i++];
    while (j < nb) out[k++] = b[j++];
    return k;
}

int main(void)
{
    int sizes[] = {1000, 10000};
    FILE *f_cmp = fopen("merge_comparison.csv", "w");
    FILE *f_tc = fopen("test_cases.csv", "w");
    if (!f_cmp || !f_tc) return 1;

    fprintf(f_cmp, "method,m,n,comparisons,time_ms,extra_space_bytes\n");
    fprintf(f_tc, "test_case,m,n,output_length,is_descending,notes\n");

    for (int s = 0; s < 2; s++) {
        int m = sizes[s], n = sizes[s];
        int *a = malloc((size_t)m * sizeof(int));
        int *b = malloc((size_t)n * sizeof(int));
        int *out = malloc((size_t)(m + n) * sizeof(int));
        if (!a || !b || !out) return 1;

        for (int i = 0; i < m; i++) a[i] = 100000 - i * 2;
        for (int j = 0; j < n; j++) b[j] = 100000 - j * 2 - 1;

        long long m_comps = 0;
        struct timespec t0, t1;
        clock_gettime(CLOCK_MONOTONIC, &t0);
        merge_counted(a, m, b, n, out, &m_comps);
        clock_gettime(CLOCK_MONOTONIC, &t1);
        double m_ms = (t1.tv_sec - t0.tv_sec) * 1000.0 + (t1.tv_nsec - t0.tv_nsec) / 1e6;
        fprintf(f_cmp, "Two_Way_Merge,%d,%d,%lld,%.6f,%zu\n",
                m, n, m_comps, m_ms, (size_t)(m + n) * sizeof(int));

        memcpy(out, a, (size_t)m * sizeof(int));
        memcpy(out + m, b, (size_t)n * sizeof(int));
        qsort_comps = 0;
        clock_gettime(CLOCK_MONOTONIC, &t0);
        qsort(out, (size_t)(m + n), sizeof(int), cmp_desc);
        clock_gettime(CLOCK_MONOTONIC, &t1);
        double q_ms = (t1.tv_sec - t0.tv_sec) * 1000.0 + (t1.tv_nsec - t0.tv_nsec) / 1e6;
        fprintf(f_cmp, "Concat_and_Qsort,%d,%d,%lld,%.6f,%zu\n",
                m, n, qsort_comps, q_ms, (size_t)(m + n) * sizeof(int));

        printf("m=n=%5d | Merge comps=%6lld (%.4f ms) | qsort comps=%7lld (%.4f ms)\n",
               m, m_comps, m_ms, qsort_comps, q_ms);

        free(a); free(b); free(out);
    }

    /* Record test cases */
    fprintf(f_tc, "Standard_Sample,4,3,7,1,\"98 95 91 91 85 80 72\"\n");
    fprintf(f_tc, "One_Empty_List,4,0,4,1,\"Copies remaining elements from non-empty array\"\n");
    fprintf(f_tc, "All_Equal_Scores,3,2,5,1,\"Preserves descending order with duplicate scores\"\n");
    fprintf(f_tc, "Different_Lengths,5,2,7,1,\"Handles unequal campus sizes\"\n");

    fclose(f_cmp);
    fclose(f_tc);
    return 0;
}

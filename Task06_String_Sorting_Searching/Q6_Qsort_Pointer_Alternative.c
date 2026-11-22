#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NAME_LEN 30

static long long qsort_strcmp_calls = 0;

int cmp_str_ptr(const void *a, const void *b)
{
    qsort_strcmp_calls++;
    const char *sa = *(const char *const *)a;
    const char *sb = *(const char *const *)b;
    return strcmp(sa, sb);
}

int main(void)
{
    int sizes[] = {100, 500, 5000};
    const char *first[] = {"Aarav", "Bhavna", "Charan", "Divya", "Eshan", "Farah", "Gokul", "Harini", "Ishaan", "Janani"};
    const char *last[]  = {"Sharma", "Nair", "Iyer", "Patel", "Kumar", "Reddy", "Menon", "Rao", "Verma", "Pillai"};

    printf("=== Task 6 Alternative: char *list[] + qsort() ===\n");
    for (int s = 0; s < 3; s++) {
        int n = sizes[s];
        char (*names)[NAME_LEN] = malloc((size_t)n * sizeof(*names));
        char **ptrs = malloc((size_t)n * sizeof(char *));
        if (!names || !ptrs) return 1;

        unsigned int lcg = 54321u;
        for (int i = 0; i < n; i++) {
            lcg = 1664525u * lcg + 1013904223u;
            int f = (int)((lcg >> 16) % 10);
            lcg = 1664525u * lcg + 1013904223u;
            int l = (int)((lcg >> 16) % 10);
            snprintf(names[i], NAME_LEN, "%s %s %04d", first[f], last[l], i);
            ptrs[i] = names[i];
        }

        qsort_strcmp_calls = 0;
        struct timespec t0, t1;
        clock_gettime(CLOCK_MONOTONIC, &t0);
        qsort(ptrs, (size_t)n, sizeof(char *), cmp_str_ptr);
        clock_gettime(CLOCK_MONOTONIC, &t1);
        double ms = (t1.tv_sec - t0.tv_sec) * 1000.0 + (t1.tv_nsec - t0.tv_nsec) / 1e6;

        printf("n = %4d | qsort(char *) -> strcmp calls = %6lld, time = %.4f ms, extra ptr space = %zu bytes\n",
               n, qsort_strcmp_calls, ms, (size_t)n * sizeof(char *));

        free(names);
        free(ptrs);
    }
    return 0;
}

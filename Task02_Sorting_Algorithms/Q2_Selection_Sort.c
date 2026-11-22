#include <stdio.h>

/* Selection sort.
 * Counts element comparisons and swaps (only when min_idx != i). */
void selection_sort(int a[], int n, long long *comparisons, long long *swaps)
{
    *comparisons = 0;
    *swaps = 0;
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            (*comparisons)++;
            if (a[j] < a[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            int tmp = a[i];
            a[i] = a[min_idx];
            a[min_idx] = tmp;
            (*swaps)++;
        }
    }
}

static void print_array(const int a[], int n)
{
    for (int i = 0; i < n; i++) {
        printf("%d%s", a[i], (i + 1 < n) ? " " : "");
    }
    printf("\n");
}

int main(void)
{
    int sample[] = {105, 102, 108, 101, 104, 103};
    int n = 6;
    long long comps = 0, swaps = 0;

    printf("Original: ");
    print_array(sample, n);

    selection_sort(sample, n, &comps, &swaps);

    printf("Sorted:   ");
    print_array(sample, n);
    printf("Comparisons = %lld, Swaps = %lld\n", comps, swaps);

    return 0;
}

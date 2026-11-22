#include <stdio.h>

/* Bubble sort with early-exit flag.
 * Counts element comparisons and swaps. */
void bubble_sort(int a[], int n, long long *comparisons, long long *swaps)
{
    *comparisons = 0;
    *swaps = 0;
    for (int i = 0; i < n - 1; i++) {
        int swapped = 0;
        for (int j = 0; j < n - 1 - i; j++) {
            (*comparisons)++;
            if (a[j] > a[j + 1]) {
                int tmp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = tmp;
                (*swaps)++;
                swapped = 1;
            }
        }
        if (!swapped) {
            break; /* Array is already sorted; exit early */
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

    bubble_sort(sample, n, &comps, &swaps);

    printf("Sorted:   ");
    print_array(sample, n);
    printf("Comparisons = %lld, Swaps = %lld\n", comps, swaps);

    /* Already sorted test */
    bubble_sort(sample, n, &comps, &swaps);
    printf("Already Sorted -> Comparisons = %lld, Swaps = %lld (early exit)\n", comps, swaps);

    return 0;
}

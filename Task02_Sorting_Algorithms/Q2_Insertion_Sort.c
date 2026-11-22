#include <stdio.h>

/* Insertion sort.
 * Counts key-to-element comparisons and inner-loop element shifts (a[j+1] = a[j]). */
void insertion_sort(int a[], int n, long long *comparisons, long long *shifts)
{
    *comparisons = 0;
    *shifts = 0;
    for (int i = 1; i < n; i++) {
        int key = a[i];
        int j = i - 1;
        while (j >= 0) {
            (*comparisons)++;
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
    long long comps = 0, shifts = 0;

    printf("Original: ");
    print_array(sample, n);

    insertion_sort(sample, n, &comps, &shifts);

    printf("Sorted:   ");
    print_array(sample, n);
    printf("Comparisons = %lld, Shifts = %lld\n", comps, shifts);

    return 0;
}

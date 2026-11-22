#include <stdio.h>

/* a[] and b[] are merit lists sorted in DESCENDING order of score.
   Copies both into out[] in descending order and returns the total count. */
int merge(const int a[], int na, const int b[], int nb, int out[])
{
    int i = 0, j = 0, k = 0;
    // TODO 1: While both lists have elements, copy the larger score into out[k]; then
    //   copy whatever remains in a[] and in b[]
    while (i < na && j < nb) {
        if (a[i] >= b[j]) {
            out[k++] = a[i++];
        } else {
            out[k++] = b[j++];
        }
    }
    while (i < na) {
        out[k++] = a[i++];
    }
    while (j < nb) {
        out[k++] = b[j++];
    }

    return k;
}

static int verify_descending(const int arr[], int n)
{
    for (int i = 1; i < n; i++) {
        if (arr[i] > arr[i - 1]) return 0;
    }
    return 1;
}

int main(void)
{
    int campusA[] = {98, 91, 85, 72};
    int campusB[] = {95, 91, 80};
    int merged[7];
    int n = merge(campusA, 4, campusB, 3, merged);
    for (int i = 0; i < n; i++) printf("%d ", merged[i]);
    printf("\n");

    /* Additional boundary tests */
    int empty_arr[1] = {0};
    int out1[4];
    int n1 = merge(campusA, 4, empty_arr, 0, out1);
    printf("One empty list (na=4, nb=0): count=%d, sorted=%s\n",
           n1, verify_descending(out1, n1) ? "YES" : "NO");

    int eqA[] = {90, 90, 90};
    int eqB[] = {90, 90};
    int out2[5];
    int n2 = merge(eqA, 3, eqB, 2, out2);
    printf("All equal scores (na=3, nb=2): count=%d, sorted=%s\n",
           n2, verify_descending(out2, n2) ? "YES" : "NO");

    return 0;
}

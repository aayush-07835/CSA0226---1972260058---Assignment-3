#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CANDIDATES 4

static int cmp_int(const void *a, const void *b)
{
    int x = *(const int *)a, y = *(const int *)b;
    return (x > y) - (x < y);
}

int main(void)
{
    const char *names[CANDIDATES] = {"Aarav", "Bhavna", "Charan", "Divya"};
    int votes[] = {1, 2, 1, 0, 3, -1, 1, 5, 2, 4};
    int v = sizeof(votes) / sizeof(votes[0]);

    /* Alternative 1: Search candidate names/IDs for every vote -> O(v * c) */
    int counts_alt1[CANDIDATES] = {0};
    int invalid1 = 0;
    for (int i = 0; i < v; i++) {
        int matched = 0;
        for (int c = 0; c < CANDIDATES; c++) {
            if (votes[i] == c + 1) {
                counts_alt1[c]++;
                matched = 1;
                break;
            }
        }
        if (!matched) invalid1++;
    }

    /* Alternative 2: Sort all votes and count consecutive runs -> O(v log v) */
    int sorted_votes[10];
    memcpy(sorted_votes, votes, sizeof(votes));
    qsort(sorted_votes, (size_t)v, sizeof(int), cmp_int);

    int counts_alt2[CANDIDATES] = {0};
    int invalid2 = 0;
    int i = 0;
    while (i < v) {
        int val = sorted_votes[i], run = 0;
        while (i < v && sorted_votes[i] == val) { run++; i++; }
        if (val >= 1 && val <= CANDIDATES) counts_alt2[val - 1] = run;
        else invalid2 += run;
    }

    printf("=== Task 7 Alternative Methods Verification ===\n");
    for (int c = 0; c < CANDIDATES; c++) {
        printf("Candidate %-7s: LinearSearch = %d | SortRuns = %d\n",
               names[c], counts_alt1[c], counts_alt2[c]);
    }
    printf("Invalid Votes     : LinearSearch = %d | SortRuns = %d\n", invalid1, invalid2);
    return 0;
}

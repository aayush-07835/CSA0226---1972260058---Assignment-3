#include <stdio.h>
#include <string.h>

#define NAME_LEN 30

int binary_search_names(char names[][NAME_LEN], int n, const char *target, int *comparisons)
{
    *comparisons = 0;
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        (*comparisons)++;
        int cmp = strcmp(names[mid], target);
        if (cmp == 0) {
            return mid;
        } else if (cmp < 0) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

int main(void)
{
    char sorted_names[8][NAME_LEN] = {
        "Aarav Sharma",
        "Ananya Iyer",
        "Bala Murugan",
        "Deepak Kumar",
        "Karthik Subramanian",
        "Meera Krishnan",
        "Priya Nair",
        "Vikram Patel"
    };

    const char *queries[] = {
        "Aarav Sharma",        /* Present (first) */
        "Karthik Subramanian", /* Present (middle) */
        "Vikram Patel",        /* Present (last) */
        "Zoya Khan",           /* Missing (after end) */
        "Arjun Menon"          /* Missing (middle gap) */
    };

    printf("=== Task 6: Binary Search on Sorted Resident Directory ===\n");
    for (int i = 0; i < 5; i++) {
        int comps = 0;
        int idx = binary_search_names(sorted_names, 8, queries[i], &comps);
        printf("Query \"%-20s\" -> index = %2d, strcmp comparisons = %d\n",
               queries[i], idx, comps);
    }

    return 0;
}

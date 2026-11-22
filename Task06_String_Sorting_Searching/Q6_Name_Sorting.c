#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_RESIDENTS 500
#define NAME_LEN 30

/* Case-insensitive string comparison */
int strcmp_ci(const char *a, const char *b)
{
    while (*a && *b) {
        int ca = tolower((unsigned char)*a);
        int cb = tolower((unsigned char)*b);
        if (ca != cb) return ca - cb;
        a++;
        b++;
    }
    return tolower((unsigned char)*a) - tolower((unsigned char)*b);
}

/* Safe fgets helper that strips '\n' and flushes overflow characters */
void safe_read_line(FILE *fp, char dest[], int max_len)
{
    if (fgets(dest, max_len, fp) != NULL) {
        size_t len = strlen(dest);
        if (len > 0 && dest[len - 1] == '\n') {
            dest[len - 1] = '\0';
        } else {
            /* Line exceeded max_len - 1; discard remainder up to '\n' */
            int ch;
            while ((ch = fgetc(fp)) != '\n' && ch != EOF) {}
        }
    }
}

void sort_names_strcpy(char names[][NAME_LEN], int n, long long *cmp_calls, long long *char_copies)
{
    *cmp_calls = 0;
    *char_copies = 0;
    char tmp[NAME_LEN];

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            (*cmp_calls)++;
            if (strcmp(names[j], names[j + 1]) > 0) {
                *char_copies += (long long)(strlen(names[j]) + 1);
                strcpy(tmp, names[j]);
                *char_copies += (long long)(strlen(names[j + 1]) + 1);
                strcpy(names[j], names[j + 1]);
                *char_copies += (long long)(strlen(tmp) + 1);
                strcpy(names[j + 1], tmp);
            }
        }
    }
}

int main(void)
{
    char names[MAX_RESIDENTS][NAME_LEN] = {
        "Karthik Subramanian",
        "Aarav Sharma",
        "Priya Nair",
        "Aarav Sharma", /* duplicate */
        "apple",
        "Apple",
        "12345678901234567890123456789", /* 29 chars: fits exactly with '\0' */
        "123456789012345678901234567890" /* 30 chars: truncated to 29 if read via fgets(30) */
    };
    int n = 8;

    /* Demonstrate length 29 vs 30 truncation with buffer size 30 */
    char buf29[NAME_LEN], buf30[NAME_LEN];
    const char *src29 = "ABCDEFGHIJKLMNOPQRSTUVWX12345"; /* 29 chars */
    const char *src30 = "ABCDEFGHIJKLMNOPQRSTUVWX123456"; /* 30 chars */
    snprintf(buf29, NAME_LEN, "%s", src29);
    strncpy(buf30, src30, NAME_LEN - 1); buf30[NAME_LEN - 1] = '\0';
    printf("Length 29 input -> stored len = %zu (\"%s\")\n", strlen(buf29), buf29);
    printf("Length 30 input -> stored len = %zu (\"%s\" - 30th char truncated!)\n\n", strlen(buf30), buf30);

    /* Case-sensitive ASCII ordering vs case-insensitive */
    printf("strcmp(\"Apple\", \"apple\") = %d ('A'=65 < 'a'=97)\n", strcmp("Apple", "apple"));
    printf("strcmp_ci(\"Apple\", \"apple\") = %d\n\n", strcmp_ci("Apple", "apple"));

    long long cmps = 0, copies = 0;
    sort_names_strcpy(names, n, &cmps, &copies);

    printf("Sorted Names (n = %d, strcmp calls = %lld, char copies = %lld):\n", n, cmps, copies);
    for (int i = 0; i < n; i++) {
        printf("  [%d] %s\n", i, names[i]);
    }

    printf("\nDuplicate Entries Detected (adjacent after sort):\n");
    int dup_found = 0;
    for (int i = 1; i < n; i++) {
        if (strcmp(names[i], names[i - 1]) == 0) {
            printf("  Duplicate: \"%s\" at indices %d and %d\n", names[i], i - 1, i);
            dup_found = 1;
        }
    }
    if (!dup_found) printf("  None\n");

    return 0;
}

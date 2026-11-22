#include <stdio.h>
#include <string.h>
#include <ctype.h>

int word_count_lib(const char *s)
{
    int count = 0, inside = 0;
    size_t len = strlen(s); /* Compute once: O(n) instead of O(n^2) */
    for (size_t i = 0; i < len; i++) {
        if (s[i] == ' ') {
            inside = 0;
        } else if (!inside) {
            inside = 1;
            count++;
        }
    }
    return count;
}

void to_uppercase_lib(char *s)
{
    size_t len = strlen(s);
    for (size_t i = 0; i < len; i++) {
        s[i] = (char)toupper((unsigned char)s[i]);
    }
}

void reverse_lib(char *s)
{
    size_t len = strlen(s);
    for (size_t i = 0; i < len / 2; i++) {
        char tmp = s[i];
        s[i] = s[len - 1 - i];
        s[len - 1 - i] = tmp;
    }
}

/* Alternative: recursive reversal (uses O(n) call stack space) */
void reverse_recursive(char *s, int left, int right)
{
    if (left >= right) return;
    char tmp = s[left];
    s[left] = s[right];
    s[right] = tmp;
    reverse_recursive(s, left + 1, right - 1);
}

int is_palindrome_lib(const char *s)
{
    char cleaned[256];
    int k = 0;
    size_t len = strlen(s);
    for (size_t i = 0; i < len && k < 255; i++) {
        if (isalpha((unsigned char)s[i])) {
            cleaned[k++] = (char)tolower((unsigned char)s[i]);
        }
    }
    cleaned[k] = '\0';

    char rev[256];
    strcpy(rev, cleaned);
    reverse_lib(rev);
    return strcmp(cleaned, rev) == 0;
}

int main(void)
{
    const char *tests[] = {
        "  Meet at  the library at 5 PM ",
        "   ",
        "",
        "Madam, I'm Adam",
        "Hello",
        "A man, a plan, a canal: Panama!",
        "Meet\tat\tthe library"
    };
    int n_tests = sizeof(tests) / sizeof(tests[0]);

    FILE *f_csv = fopen("string_test_cases.csv", "w");
    if (!f_csv) return 1;
    fprintf(f_csv, "test_id,input_description,word_count_space_only,is_palindrome,uppercase_preview\n");

    printf("=== Task 5: string.h Comparison ===\n");
    for (int i = 0; i < n_tests; i++) {
        char copy[128];
        snprintf(copy, sizeof(copy), "%s", tests[i]);
        to_uppercase_lib(copy);
        int wc = word_count_lib(tests[i]);
        int pal = is_palindrome_lib(tests[i]);
        printf("Test %d: wc=%d, pal=%d | Upper=\"%s\"\n", i + 1, wc, pal, copy);
        fprintf(f_csv, "%d,\"Test_%d\",%d,%d,\"%s\"\n", i + 1, i + 1, wc, pal, copy);
    }

    char rec_demo[] = "SAVEETHA";
    reverse_recursive(rec_demo, 0, (int)strlen(rec_demo) - 1);
    printf("Recursive reverse of SAVEETHA: %s\n", rec_demo);

    fclose(f_csv);
    return 0;
}

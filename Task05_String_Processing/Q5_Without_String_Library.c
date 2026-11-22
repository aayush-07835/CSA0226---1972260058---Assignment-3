#include <stdio.h>
#include <ctype.h>

/* Counts words separated by one or more spaces, without using string.h */
int word_count(const char s[])
{
    int count = 0, inside = 0;
    // TODO 1: Scan the string up to '\0'; count a new word each time a non-space
    //   character follows a space (or the start of the string)
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == ' ') {
            inside = 0;
        } else if (!inside) {
            inside = 1;
            count++;
        }
    }

    return count;
}

/* Returns 1 if s reads the same both ways, ignoring case and non-letters. */
int is_palindrome(const char s[])
{
    int left = 0, right = 0;
    while (s[right] != '\0') right++;
    right--;
    // TODO 2: Move left forward and right backward, skipping non-letters, and compare
    //   the letters ignoring case; return 0 on the first mismatch
    while (left < right) {
        while (left < right && !isalpha((unsigned char)s[left])) {
            left++;
        }
        while (left < right && !isalpha((unsigned char)s[right])) {
            right--;
        }
        if (left < right) {
            if (tolower((unsigned char)s[left]) != tolower((unsigned char)s[right])) {
                return 0;
            }
            left++;
            right--;
        }
    }

    return 1;
}

/* Additional custom string functions without string.h */
void to_uppercase_custom(char s[])
{
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] >= 'a' && s[i] <= 'z') {
            s[i] = (char)(s[i] - ('a' - 'A'));
        }
    }
}

void reverse_custom(char s[])
{
    int len = 0;
    while (s[len] != '\0') len++;
    for (int i = 0; i < len / 2; i++) {
        char tmp = s[i];
        s[i] = s[len - 1 - i];
        s[len - 1 - i] = tmp;
    }
}

int main(void)
{
    printf("Words: %d\n", word_count("  Meet at  the library at 5 PM "));
    printf("%d %d\n", is_palindrome("Madam, I'm Adam"), is_palindrome("Hello"));

    /* Tab character test */
    const char *tab_msg = "Meet\tat\tthe library";
    printf("Tab test \"%s\" -> word_count = %d (tab '\\t' != ' ', so \"Meet\\tat\\tthe\" counts as 1 token)\n",
           tab_msg, word_count(tab_msg));

    /* Uppercase & Reverse demo */
    char buf[64] = "Feedback 101!";
    to_uppercase_custom(buf);
    printf("Uppercase: %s\n", buf);
    reverse_custom(buf);
    printf("Reversed:  %s\n", buf);

    return 0;
}

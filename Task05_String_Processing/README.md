# Task 5 — Processing Text Without the Library (6 Marks)

**Objective:** Implement word counting, uppercase conversion, string reversal, and palindrome checking without `string.h` (completing `TODO 1` and `TODO 2`), compare against `string.h` equivalents, test tabs/spaces/empty strings, and demonstrate safe string handling (`snprintf`, `fgets`).

## Files Included
- `Q5_Without_String_Library.c` — Completed TODO 1 & TODO 2 + tab test
- `Q5_With_String_Library.c` — `strlen`, `strcpy`, `strcmp`, `toupper` equivalents + recursive reverse + `string_test_cases.csv`
- `Q5_Safe_String_Handling.c` — `char s[]` vs `char *s`, `snprintf()` truncation safety, `fgets()` vs `gets()`
- `output/` — Verified `.txt` outputs

## Compile & Run
```bash
gcc -std=c11 -Wall -Wextra -pedantic -O2 Q5_Without_String_Library.c -o q5_custom && ./q5_custom
```

## Exact Verified Output (`Q5_Without_String_Library.c`)
```text
Words: 7
1 0
Tab test "Meet	at	the library" -> word_count = 2 (tab '\t' != ' ', so "Meet\tat\tthe" counts as 1 token)
```

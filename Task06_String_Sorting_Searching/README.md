# Task 6 — A Directory of Names: Sorting and Searching Strings (7 Marks)

**Objective:** Manage `names[500][30]` safely with `fgets()`, sort with `strcmp()`/`strcpy()`, detect duplicates, run binary search, test length 29 vs. 30 truncation, benchmark index sorting (`100`, `500`, `5,000` names), and evaluate `char *list[]` + `qsort()`.

## Files Included
- `Q6_Name_Sorting.c` — `strcpy()` sorting, duplicate detection, length 29/30 test, `strcmp_ci()`
- `Q6_Binary_Search.c` — Binary search on sorted resident names (present & missing keys)
- `Q6_Index_Sorting.c` — `strcpy` vs. index-array sorting benchmark (`100`, `500`, `5,000` names)
- `Q6_Qsort_Pointer_Alternative.c` — `char *list[]` + `qsort()` alternative
- `resident_names.csv`, `comparison_counts.csv` — Verified CSV data
- `output/` — Verified `.txt` outputs & `q6_strcpy_vs_index.png`

## Compile & Run
```bash
gcc -std=c11 -Wall -Wextra -pedantic -O2 Q6_Index_Sorting.c -o q6_index && ./q6_index
```

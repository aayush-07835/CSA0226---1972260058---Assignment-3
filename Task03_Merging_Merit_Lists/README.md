# Task 3 — Merging Two Merit Lists (7 Marks)

**Objective:** Merge two descending-sorted merit lists into a third array without re-sorting, complete `TODO 1`, test boundary cases (empty list, all equal scores), and compare against `concat + qsort()` and in-place merging.

## Files Included
- `Q3_Merge_Sorted_Arrays.c` — Completed TODO 1 program + boundary tests
- `Q3_Qsort_Alternative.c` — `O(m+n)` merge vs `O((m+n) log(m+n))` `qsort()` benchmark (`merge_comparison.csv`, `test_cases.csv`)
- `Q3_In_Place_Alternative.c` — `O(m·n)` in-place merge with `O(1)` extra space
- `output/` — Verified `.txt` outputs & `q3_merge_vs_qsort.png`

## Compile & Run
```bash
gcc -std=c11 -Wall -Wextra -pedantic -O2 Q3_Merge_Sorted_Arrays.c -o q3_merge && ./q3_merge
```

## Exact Verified Output (`Q3_Merge_Sorted_Arrays.c`)
```text
98 95 91 91 85 80 72 
One empty list (na=4, nb=0): count=4, sorted=YES
All equal scores (na=3, nb=2): count=5, sorted=YES
```

# Executive Summary — CSA02 CO3 Assignment 3

**Student:** Aayush Nambiar T. (`1972260058`)  
**Course:** CSA02 – C Programming (CO3)  
**Total Marks:** 50  

This repository contains the complete, individually executed implementation, experimental benchmarks, algorithm analysis, and academic report for **Assignment 3 (CO3)**.

## Key Verified Findings

1. **Q1 (Searching):** Binary search reduced average comparisons at `n = 100,000` from `50,000.05` (linear search) to `15.79` (`17` worst-case), matching `⌊log₂(n)⌋ + 1 = 17`.
2. **Q2 (Sorting):** Insertion sort achieved `O(n)` (`n - 1` comparisons, `0` swaps) on sorted data and outperformed Bubble/Selection sort on nearly sorted data (`n = 10,000`: `0.04 ms` vs `2.9 ms` for Bubble Sort and `69 ms` for Selection Sort).
3. **Q3 (Merging):** Two-way descending merge used `19,999` comparisons (`0.042 ms`) at `m = n = 10,000`, compared to `149,215` comparisons (`0.527 ms`) for concatenation + `qsort()`.
4. **Q4 (2D Arrays):** Row-wise traversal of a `2,000 × 2,000` `double` array took `3.9577 ms`, whereas column-wise traversal took `21.4763 ms` (5.43× slower) due to row-major cache misses.
5. **Q5 (Strings):** Custom loop implementations matched `string.h` outputs across all test cases; `word_count()` treats `'\t'` as a non-space character unless explicitly checked.
6. **Q6 (String Sorting):** At `n = 5,000` names, index-based sorting eliminated `323,581,232` character copies and cut runtime from `276.51 ms` to `190.22 ms`.
7. **Q7 (Election System):** A single-pass count array (`O(v)`) processed `500,000` votes in `0.4699 ms`, compared to `6.8434 ms` for linear candidate search (`O(v·c)`) and `39.2610 ms` for sorting all votes (`O(v log v)`).

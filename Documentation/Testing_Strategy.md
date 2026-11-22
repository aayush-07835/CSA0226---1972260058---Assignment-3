# Testing Strategy (Q1–Q7)

1. **Compiler Strictness:** Every program is compiled with `gcc -std=c11 -Wall -Wextra -pedantic -O2` and must produce zero errors and zero warnings.
2. **Exact Starter-Code Verification:** `Q1_Complete_Code.c`, `Q3_Merge_Sorted_Arrays.c`, and `Q5_Without_String_Library.c` are verified against the exact expected outputs in `CO3_Assignment_3.docx`.
3. **Deterministic Datasets:** All scaled benchmarks (`n = 100..500,000`) use fixed-seed linear congruential generators (LCGs) or deterministic arithmetic formulas so results are 100% reproducible.
4. **Boundary & Edge Cases:**
   - **Q1:** First, middle, last, and missing keys; overflow-safe `mid = low + (high - low) / 2`.
   - **Q2:** Already sorted, nearly sorted (5% swaps), reverse-sorted, random; `is_sorted()` post-condition check.
   - **Q3:** Different lengths, equal scores (tie stability), one empty array, all equal scores, `verify_descending()` check.
   - **Q4:** Small `3 × 4` hand-verified dataset before `38 × 12` execution; `2,000 × 2,000` cache-locality timing.
   - **Q5:** Leading/trailing/multiple spaces, empty string, punctuation, tab character `'\t'`, and `snprintf` truncation.
   - **Q6:** Length 29 vs length 30 names in `char[30]`, duplicate detection, case-sensitive vs case-insensitive ordering.
   - **Q7:** Invalid votes (`0`, negative, `> c`), tie detection, clear winner, hand-verified 10-ballot set, and `5,000` / `500,000` vote scaling.
5. **High-Resolution Timing:** Benchmarks use `clock_gettime(CLOCK_MONOTONIC, ...)` in milliseconds (`ms`) and write raw measurements directly to CSV.

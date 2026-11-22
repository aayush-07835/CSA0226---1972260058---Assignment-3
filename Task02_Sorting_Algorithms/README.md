# Task 2 — Sorting the Examination Hall Seating Register (7 Marks)

**Objective:** Implement Bubble Sort (early-exit), Selection Sort, and Insertion Sort; count comparisons and swaps/shifts across Sorted, Nearly Sorted, Reverse-Sorted, and Random arrays for `n = 100, 1,000, 10,000`; trace a 6-element array; and evaluate Counting Sort `O(n + k)`.

## Files Included
- `Q2_Bubble_Sort.c`, `Q2_Selection_Sort.c`, `Q2_Insertion_Sort.c` — Individual implementations
- `Q2_Benchmark.c` — Full benchmark + Counting Sort + `comparison_counts.csv` & `sorting_traces.csv`
- `output/` — Verified `.txt` outputs & `q2_sorting_comparisons.png`

## Compile & Run
```bash
gcc -std=c11 -Wall -Wextra -pedantic -O2 Q2_Benchmark.c -o q2_bench && ./q2_bench
```

## Counting Definitions
- **Comparisons:** Every element-to-element (`a[j] > a[j+1]`, `a[j] < a[min]`, or `a[j] > key`) check.
- **Swaps/Shifts:** Swaps for Bubble/Selection Sort; inner-loop shifts (`a[j+1] = a[j]`) for Insertion Sort.

## Complexity Summary
- **Bubble / Insertion Sort:** Best `O(n)` (sorted), Avg/Worst `O(n²)`, Extra Space `O(1)`, **Stable**
- **Selection Sort:** Best/Avg/Worst `O(n²)`, Swaps `<= n - 1`, Extra Space `O(1)`, **Unstable**
- **Counting Sort:** `O(n + k)` time, `O(k)` extra space

# Task 1 — Searching a Library Catalogue (6 Marks)

**Objective:** Implement and compare linear search (unsorted) and binary search (sorted) for library accession numbers, complete `TODO 1`, benchmark `n = 1,000`, `10,000`, and `100,000`, and analyse hash-table and interpolation-search alternatives.

## Files Included
- `Q1_Complete_Code.c` — Completed original TODO 1 program
- `Q1_Linear_Search.c` — Linear search on unsorted arrays (`n = 10`, `1,000`, `10,000`, `100,000`)
- `Q1_Binary_Search.c` — Binary vs. linear benchmark generating `search_results.csv` and `comparison_analysis.csv`
- `Q1_Alternative_Hash_Table.c` — Hash table (`key % table_size`, linear probing) & interpolation search
- `search_results.csv`, `comparison_analysis.csv` — Verified CSV data
- `output/` — Verified `.txt` outputs & `q1_search_comparisons.png`

## Compile & Run
```bash
gcc -std=c11 -Wall -Wextra -pedantic -O2 Q1_Complete_Code.c -o q1_complete && ./q1_complete
gcc -std=c11 -Wall -Wextra -pedantic -O2 Q1_Binary_Search.c -o q1_bench && ./q1_bench
```

## Exact Verified Output (`Q1_Complete_Code.c`)
```text
Book 1021 -> index 0, comparisons = 3
Book 1305 -> index 5, comparisons = 3
Book 1533 -> index 9, comparisons = 4
Book 1400 -> index -1, comparisons = 4
```

## Complexity Summary
- **Linear Search:** Best `O(1)`, Avg `O(n)`, Worst `O(n)`, Extra Space `O(1)`
- **Binary Search:** Best `O(1)`, Avg `O(log n)`, Worst `O(log n)`, Extra Space `O(1)`
- **Hash Table (Linear Probing):** Avg `O(1)`, Worst `O(n)`, Extra Space `O(m)`
- **Interpolation Search:** Avg `O(log log n)`, Worst `O(n)`, Extra Space `O(1)`

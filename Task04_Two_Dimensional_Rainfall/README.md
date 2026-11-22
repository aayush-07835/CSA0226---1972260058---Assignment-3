# Task 4 — Two-Dimensional Arrays: District Rainfall Records (7 Marks)

**Objective:** Analyse `rain[38][12]` using four modular functions, verify on a `3 × 4` hand-checked dataset, benchmark `2,000 × 2,000` row-wise vs. column-wise traversal, extend to 3D `rain[years][districts][months]`, and compare 1D (`i*12+j`) and pointer-array (`double *rows[38]`) alternatives.

## Files Included
- `Q4_Rainfall_Analysis.c` — Core 4-function system, `3x4` check, `38x12` dataset, `2000x2000` benchmark
- `Q4_Three_Dimensional_Array.c` — Multi-year 3D extension
- `Q4_One_Dimensional_Alternative.c` — Flat 1D `i * 12 + j` alternative
- `Q4_Pointer_Array_Alternative.c` — Array of 38 row pointers alternative
- `rainfall_data.csv`, `traversal_benchmark.csv` — Verified CSV data
- `output/` — Verified `.txt` outputs & `q4_traversal_benchmark.png`

## Compile & Run
```bash
gcc -std=c11 -Wall -Wextra -pedantic -O2 Q4_Rainfall_Analysis.c -o q4_rain && ./q4_rain
```

## Key Measured Finding
- Row-wise traversal (`2,000 × 2,000`): **3.9577 ms**
- Column-wise traversal (`2,000 × 2,000`): **21.4763 ms** (5.43× slower due to cache misses on 16,000-byte stride)

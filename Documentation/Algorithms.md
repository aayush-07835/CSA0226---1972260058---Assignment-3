# Algorithms Overview (Q1–Q7)

## Q1 — Searching a Library Catalogue
- **Linear Search:** Sequentially inspects `a[0..n-1]` until `a[i] == key`. Works on unsorted data.
- **Binary Search:** Maintains `[low, high]` on a sorted array, checks `mid = low + (high - low) / 2` (preventing integer overflow), and halves the search space each step.
- **Alternatives:** Hash table (`key % table_size` with linear probing) for `O(1)` average lookup; Interpolation search (`pos = low + (key - a[low])*(high - low)/(a[high] - a[low])`) for `O(log log n)` average on uniformly distributed sorted keys.

## Q2 — Sorting Examination Hall Seating Register
- **Bubble Sort (Early-Exit):** Repeatedly swaps adjacent out-of-order elements; exits early if a full pass makes zero swaps.
- **Selection Sort:** Selects the minimum element from `a[i..n-1]` and swaps it into `a[i]`. Minimizes swaps (`<= n - 1`).
- **Insertion Sort:** Inserts `a[i]` into the already-sorted prefix `a[0..i-1]` by shifting larger elements right.
- **Alternative (Counting Sort):** Counts frequencies in `count[0..k]` and reconstructs sorted output in `O(n + k)` time without comparisons.

## Q3 — Merging Two Merit Lists
- **Two-Way Merge:** Compares heads `a[i]` and `b[j]` of two descending arrays, copying the larger (`>=` preserves Campus A before Campus B on ties) into `out[k]`, then copies remaining tails.
- **Alternatives:** Concatenate + `qsort()` in `O((m+n) log(m+n))`; simple in-place merge in `O(m·n)` time and `O(1)` extra space.

## Q4 — 2D Arrays: District Rainfall Records
- **Row-Major Storage:** `rain[i][j]` is stored contiguously row by row at `Base + (i * 12 + j) * sizeof(double)`.
- **Four Core Functions:** District annual totals (row sums), state monthly averages (column means), wettest district-month (global max), and deficient districts (`< 60%` of state annual mean).
- **Alternatives:** 1D flat array (`i * 12 + j`) and pointer array (`double *rows[38]`).

## Q5 — Processing Text Without `string.h`
- **Custom Loops:** Scan until `'\0'`. `word_count` uses an `inside` state flag; `is_palindrome` uses two converging pointers skipping non-letters via `isalpha()` and comparing via `tolower()`.
- **Safety:** Replace `gets()` (removed in C11) and unbounded `strcpy()` with `fgets()` and `snprintf()`.

## Q6 — Sorting & Searching Strings
- **String Sorting:** Sort `names[n][30]` via `strcmp()` and `strcpy()`.
- **Index Sorting:** Sort `int idx[n]` by comparing `names[idx[j]]`, reducing `strcpy()` overhead to zero character copies.
- **Alternative:** `char *list[n]` sorted with `qsort()` in `O(n log n)` string comparisons.

## Q7 — Student Council Election Counting
- **One-Pass Count Array:** Validate `1 <= vote <= num_candidates`, increment `counts[vote]`, track `invalid_votes`. Copy `(id, votes)` into `CandidateResult[]`, sort descending, and detect ties by counting candidates matching `results[0].votes`.
- **Alternatives:** Linear candidate search per vote `O(v·c)` or sorting all votes `O(v log v)`.

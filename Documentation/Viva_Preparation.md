# Viva Preparation — CSA02 CO3 Assignment 3

Comprehensive oral-viva questions and concise, technically accurate answers covering all 22 CO3 topics.

---

## 1. Linear & Binary Search & Comparison Counts (Q1)
1. **Q: Why does binary search require a sorted array?**  
   A: Binary search discards half the search space based on comparing `a[mid]` with `key`. If the array is unsorted, `key` could lie on either side of `mid`, breaking the invariant.
2. **Q: Why is `mid = low + (high - low) / 2` preferred over `(low + high) / 2`?**  
   A: When `low` and `high` are large integers (e.g., near `INT_MAX`), `low + high` can overflow signed 32-bit `int`. `low + (high - low) / 2` avoids overflow while computing the exact same midpoint.
3. **Q: Why does a missing key take as many comparisons as a worst-case successful search?**  
   A: A search for a missing key only terminates when the `[low, high]` interval becomes empty (`low > high`), which traverses the full height of the binary search tree (`⌊log₂(n)⌋ + 1` comparisons).
4. **Q: What are the best, average, and worst comparison counts for linear search on `n` elements?**  
   A: Best: `1` (first element); Average (successful): `(n + 1) / 2`; Worst (last or missing): `n`.
5. **Q: For `n = 100,000`, how many comparisons does binary search need at most?**  
   A: `⌊log₂(100,000)⌋ + 1 = 16 + 1 = 17` comparisons (verified experimentally: `17`).
6. **Q: If new books arrive daily, is keeping the array sorted worth it?**  
   A: Only if searches vastly outnumber insertions. Inserting into a sorted array costs `O(n)` shifts, whereas an unsorted array inserts in `O(1)`. We need the daily search-to-insertion ratio to decide.
7. **Q: How does a hash table with linear probing improve search time?**  
   A: It hashes `key % table_size` for `O(1)` average lookup, probing sequentially on collisions. Its trade-off is `O(m)` extra space (`m > n`) and no sorted range queries.
8. **Q: When is interpolation search faster than binary search, and when is it worse?**  
   A: On uniformly distributed sorted keys it achieves `O(log log n)` average comparisons, but on skewed/exponential data it degrades to `O(n)` worst case.

---

## 2. Bubble, Selection, Insertion Sort & Stability (Q2)
9. **Q: What is the purpose of the early-exit `swapped` flag in bubble sort?**  
   A: If an entire inner pass performs zero swaps, the array is already sorted, so bubble sort terminates immediately—improving best-case time from `O(n²)` to `O(n)`.
10. **Q: Why is insertion sort fast on nearly sorted data?**  
    A: Each element is already close to its final position, so the inner `while` loop performs only a few shifts (`O(n + d)` total time where `d` is the number of inversions).
11. **Q: Which of the three `O(n²)` sorts are stable, and why?**  
    A: Bubble sort and Insertion sort are stable (they only swap/shift on strict `>`). Standard Selection sort is unstable because long-range swaps can move an equal element past another.
12. **Q: Why does stability matter for an examination seating register?**  
    A: When students share equal marks, a stable sort preserves their original secondary ordering (e.g., by register number or submission order).
13. **Q: Which sort is best for a register sorted except for 20 late registrations?**  
    A: Insertion sort, because the sorted prefix is untouched and each of the 20 late entries only shifts across the elements larger than it (`O(n)` work).
14. **Q: When is Selection sort preferable despite always taking `O(n²)` comparisons?**  
    A: When writes/swaps are expensive (e.g., flash/EEPROM memory), because Selection sort performs at most `n - 1` swaps.
15. **Q: How does Counting Sort achieve `O(n + k)` time, and when is it unsuitable?**  
    A: It counts frequencies in an auxiliary array of size `k + 1` without comparing elements. It is unsuitable when `k` is huge (e.g., 10-digit IDs) due to `O(k)` memory, or for floating-point/string keys.
16. **Q: How do you define a swap vs. a shift in your benchmark?**  
    A: A swap exchanges two array elements (Bubble/Selection); a shift moves `a[j]` to `a[j + 1]` inside Insertion sort's inner loop.

---

## 3. Merging Sorted Arrays (Q3)
17. **Q: Why is every element compared at most once during a two-way merge?**  
    A: Each comparison advances either `i` or `j` by 1, placing one element into `out[]`. Once `i` or `j` advances, that element is never compared again (`<= m + n - 1` comparisons).
18. **Q: How are remaining elements handled after one array ends?**  
    A: Two trailing `while` loops copy the remaining suffix of whichever array is non-empty directly into `out[]` without further comparisons.
19. **Q: How do you preserve original campus order on equal scores?**  
    A: By using `if (a[i] >= b[j])` (taking from Campus A first on ties).
20. **Q: What happens if one input array is empty (`nb = 0`)?**  
    A: The main `while (i < na && j < nb)` loop does not execute, and the `while (i < na)` loop copies `a[]` directly into `out[]`.
21. **Q: Compare `O(m + n)` merge vs. `concat + qsort()` vs. in-place merge.**  
    A: Two-way merge takes `O(m + n)` time and `O(m + n)` space; `concat + qsort()` takes `O((m+n) log(m+n))` time and `O(m + n)` space; simple in-place merge uses `O(1)` extra space but costs `O(m·n)` time.

---

## 4. 2D Arrays, Row-Major Layout & Cache Locality (Q4)
22. **Q: How does C store `double rain[38][12]` in memory?**  
    A: In **row-major order**: all 12 months of District 0 are stored contiguously, followed immediately by District 1, and so on.
23. **Q: What is the memory address formula for `rain[i][j]`?**  
    A: `Address(rain[i][j]) = Base_Address + (i * 12 + j) * sizeof(double)`.
24. **Q: Why is row-wise traversal faster than column-wise traversal on a `2,000 × 2,000` array?**  
    A: Row-wise traversal accesses adjacent memory addresses sequentially, maximizing CPU cache-line hits (`3.96 ms` measured vs `21.48 ms` for column-wise strided access).
25. **Q: Why is `rain[38][12]` better than 38 separate 1D arrays?**  
    A: It allows loops over both districts and months, guarantees one contiguous memory block, and cleanly passes to functions.
26. **Q: Compare `rain[38][12]`, 1D `rain[i*12+j]`, and `double *rows[38]`.**  
    A: All three have `O(1)` access. `rain[38][12]` and 1D `i*12+j` are contiguous and cache-friendly; `double *rows[38]` adds `38 * sizeof(double *)` pointer overhead and extra pointer-dereference indirection.

---

## 5. Character Arrays, `'\0'`, `string.h` & Safe String Handling (Q5)
27. **Q: What is the role of `'\0'` in C strings?**  
    A: It marks the end of the string in memory so functions know where to stop reading.
28. **Q: Why is `for (i = 0; i < strlen(s); i++)` inefficient?**  
    A: `strlen(s)` scans until `'\0'` on every iteration, turning an `O(n)` loop into `O(n²)`.
29. **Q: What is the difference between `char s[] = "OK";` and `char *s = "OK";`?**  
    A: `char s[] = "OK"` creates a mutable 3-byte array on the stack; `char *s = "OK"` points to a read-only string literal (modifying it is undefined behavior).
30. **Q: Why was `gets()` removed from the C11 standard?**  
    A: `gets()` does not know the destination buffer size, making buffer-overflow attacks trivial. `fgets(buf, sizeof(buf), stdin)` is the safe replacement.
31. **Q: Why does `word_count("Meet\tat\tthe library")` return `2` instead of `4`?**  
    A: Because the starter specification checks `s[i] == ' '` only; `'\t'` is not `' '`, so `"Meet\tat\tthe"` is treated as a single word token.

---

## 6. Sorting & Searching Strings, `strcmp` & Index Sorting (Q6)
32. **Q: How does `strcmp(a, b)` work, and why do `"Apple"` and `"apple"` differ?**  
    A: `strcmp()` compares unsigned `char` values byte-by-byte until a difference or `'\0'`. Since ASCII `'A'` (65) < `'a'` (97), `"Apple"` sorts before `"apple"`.
33. **Q: What happens when a 30-character name is read into `char name[30]` via `fgets()`?**  
    A: `fgets(name, 30, fp)` reads at most 29 characters and appends `'\0'`, truncating the 30th character (and leaving it in the input stream unless flushed).
34. **Q: Why does sorting an index array `int idx[n]` save time over `strcpy()`?**  
    A: Swapping two 4-byte integers takes `O(1)` work with `0` character copies, whereas `strcpy()` copies up to 30 bytes three times per swap (`323.58M` char copies saved at `n = 5,000`).
35. **Q: Why do duplicate names become adjacent after sorting?**  
    A: Identical strings have `strcmp(a, b) == 0`, so any valid total-order sort places all equal strings in consecutive positions.

---

## 7. Election Counting System, Ties & Big-O Analysis (Q7)
36. **Q: Why is a count array `O(v)` better than searching candidate names `O(v·c)`?**  
    A: Candidate number `k` directly indexes `counts[k]` in `O(1)` time per vote, avoiding `c` comparisons per ballot (`0.47 ms` vs `6.84 ms` at `v = 500,000`).
37. **Q: Why must we sort a copy/struct array of `(id, votes)` rather than `counts[]` directly?**  
    A: Sorting `counts[]` directly would lose the mapping between array index (candidate ID) and vote total.
38. **Q: How does your tie-detection logic work?**  
    A: After sorting candidates descending by votes, we count how many candidates have `results[i].votes == results[0].votes`. If `tie_count > 1`, a tie is declared among those candidates.
39. **Q: How would the design change for `500` candidates, and what is a remaining limitation?**  
    A: Increase `MAX_CANDIDATES` to `500` (still only ~2 KB of RAM). A remaining limitation is that votes are assumed to be numeric candidate IDs rather than string names, and `O(c²)` sorting of results would be better replaced by `qsort()` (`O(c log c)`) for large `c`.
40. **Q: Compare `O(v)`, `O(v·c)`, and `O(v log v)` in terms of `v` (votes) and `c` (candidates).**  
    A: `v` is total ballots (`500,000`) and `c` is candidates (`12`). Count array `O(v)` scales linearly with ballots using `O(c)` space; linear search `O(v·c)` multiplies by `c`; sorting all votes `O(v log v)` requires `O(v)` memory and `log₂(v)` factor (`39.26 ms`).

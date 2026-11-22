# Complexity Analysis (Q1–Q7)

| Question | Primary Algorithm | Best Time | Average Time | Worst Time | Extra Space | Alternative & Complexity |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| **Q1** | Linear Search | `O(1)` | `O(n)` (`(n+1)/2`) | `O(n)` | `O(1)` | Hash Table `O(1)` avg / `O(n)` worst, `O(m)` space |
| **Q1** | Binary Search | `O(1)` | `O(log n)` | `O(log n)` (`⌊log₂n⌋+1`) | `O(1)` | Interpolation Search `O(log log n)` avg / `O(n)` worst, `O(1)` space |
| **Q2** | Bubble Sort (Early-Exit) | `O(n)` | `O(n²)` | `O(n²)` | `O(1)` | Counting Sort `O(n + k)` time, `O(k)` space |
| **Q2** | Selection Sort | `O(n²)` | `O(n²)` | `O(n²)` | `O(1)` | Counting Sort `O(n + k)` time, `O(k)` space |
| **Q2** | Insertion Sort | `O(n)` | `O(n²)` | `O(n²)` | `O(1)` | Counting Sort `O(n + k)` time, `O(k)` space |
| **Q3** | Two-Way Merge | `O(min(m,n))` | `O(m + n)` | `O(m + n)` | `O(m + n)` | Concat + `qsort()`: `O((m+n) log(m+n))`; In-Place: `O(m·n)` time, `O(1)` space |
| **Q4** | 2D Array Traversal | `O(R·C)` | `O(R·C)` | `O(R·C)` | `O(1)` aux | 1D `i*12+j`: `O(1)` access; Pointer array `double *rows[38]`: `O(1)` access + `38*sizeof(ptr)` |
| **Q5** | Custom / `string.h` Loops | `O(n)` | `O(n)` | `O(n)` | `O(1)` | `strlen()` in loop condition: `O(n²)`; Recursive reverse: `O(n)` stack space |
| **Q6** | `strcpy` String Sort | `O(n·L)` | `O(n²·L)` | `O(n²·L)` | `O(L)` temp | Index Sort: `O(n)` int space, `0` char copies; `char *` + `qsort`: `O(n log n · L)` |
| **Q7** | Count Array Election | `O(v + c log c)` | `O(v + c log c)` | `O(v + c log c)` | `O(c)` | Candidate Search: `O(v·c)`; Sort All Votes: `O(v log v)` |

# CSA02 – C Programming | Assignment 3 (CO3)

**Institution:** Saveetha Institute of Medical and Technical Sciences  
**Programme:** B.E / B.Tech  
**Course Code & Name:** CSA02 – C Programming  
**Course Outcome:** CO3 (Searching, Sorting, Merging, 2D/3D Arrays, Strings & Algorithm Analysis)  
**Student Name:** Aayush Nambiar T.  
**Register Number:** 1972260058  
**Working Mode:** Individual Completion (All Student A, Student B, Shared, and Joint sections consolidated)  
**Compiler & Standard:** GCC 12.2.0 (`gcc -std=c11 -Wall -Wextra -pedantic`)  
**Total Marks:** 50  

---

## Folder Structure

```text
CSA02_CO3_Assignment_3/
├── README.md
├── SUMMARY.md
├── Assignment_Report.docx
├── Assignment_Report.pdf
├── Task01_Searching_Library_Catalogue/
├── Task02_Sorting_Algorithms/
├── Task03_Merging_Merit_Lists/
├── Task04_Two_Dimensional_Rainfall/
├── Task05_String_Processing/
├── Task06_String_Sorting_Searching/
├── Task07_Election_Counting_System/
└── Documentation/
```

Each task folder contains its `.c` source files, deterministic `.csv` datasets/benchmarks, `README.md`, `output/` (verified `.txt` execution logs and `.png` performance charts), and `screenshots/` (placeholder for local terminal screenshots).

---

## Compilation & Execution Instructions

Compile any C11 source file from its task directory:

```bash
gcc -std=c11 -Wall -Wextra -pedantic -O2 <filename.c> -o <program>
./<program>
```

To compile and run every program across all seven tasks at once (Linux/macOS):

```bash
for dir in Task0*; do
  (cd "$dir" && for f in *.c; do gcc -std=c11 -Wall -Wextra -pedantic -O2 "$f" -o "${f%.c}" && ./"${f%.c}"; done)
done
```

---

## Summary of Tasks (Q1–Q7)

| Task | Topic | Marks | Key Programs | Verified Output Highlights |
| :--- | :--- | :---: | :--- | :--- |
| **Q1** | Searching a Library Catalogue | 6 | `Q1_Complete_Code.c`, `Q1_Linear_Search.c`, `Q1_Binary_Search.c`, `Q1_Alternative_Hash_Table.c` | Exact TODO output (`1021->0 (3)`, `1305->5 (3)`, `1533->9 (4)`, `1400->-1 (4)`); `n=100,000` avg binary `15.79` vs linear `50,000.05` comparisons |
| **Q2** | Sorting Examination Hall Register | 7 | `Q2_Bubble_Sort.c`, `Q2_Selection_Sort.c`, `Q2_Insertion_Sort.c`, `Q2_Benchmark.c` | Full `n=100, 1,000, 10,000` benchmark across 4 input orders + Counting Sort `O(n+k)` |
| **Q3** | Merging Two Merit Lists | 7 | `Q3_Merge_Sorted_Arrays.c`, `Q3_Qsort_Alternative.c`, `Q3_In_Place_Alternative.c` | Exact TODO output `98 95 91 91 85 80 72`; `m=n=10,000`: `19,999` merge vs `149,215` `qsort` comparisons |
| **Q4** | 2D Arrays: District Rainfall | 7 | `Q4_Rainfall_Analysis.c`, `Q4_Three_Dimensional_Array.c`, `Q4_One_Dimensional_Alternative.c`, `Q4_Pointer_Array_Alternative.c` | `3x4` hand-check + `38x12` analysis; `2000x2000` row-wise `3.9577 ms` vs col-wise `21.4763 ms` |
| **Q5** | Text Processing Without `string.h` | 6 | `Q5_Without_String_Library.c`, `Q5_With_String_Library.c`, `Q5_Safe_String_Handling.c` | Exact TODO output `Words: 7` and `1 0`; tab test, `snprintf`/`fgets` safety |
| **Q6** | Hostel Directory: String Sort/Search | 7 | `Q6_Name_Sorting.c`, `Q6_Binary_Search.c`, `Q6_Index_Sorting.c`, `Q6_Qsort_Pointer_Alternative.c` | `n=5,000`: `strcpy` `323.58M` char copies (`276.51 ms`) vs index sort `0` copies (`190.22 ms`) |
| **Q7** | Election Counting System | 10 | `Q7_Election_Counting.c`, `Q7_Benchmark.c`, `Q7_Alternative_Methods.c` | `O(v)` count array (`0.4699 ms` for `500,000` votes) vs `O(v*c)` (`6.8434 ms`) vs `O(v log v)` (`39.2610 ms`) |

---

## Explanation of CSV Evidence

All CSV files in `Task01`–`Task07` are generated directly by executing the compiled C programs with deterministic inputs (fixed LCG seeds and deterministic formulas). Every table and Matplotlib graph in `Assignment_Report.docx` and `Assignment_Report.pdf` is plotted directly from these CSV files.

---

## GitHub Submission Instructions

1. Create a repository named `CSA02-1972260058-Assignment3`.
2. Capture local terminal screenshots for each task and place them in `Task0X_.../screenshots/`.
3. Commit progressively per task (`git add Task01_... && git commit -m "Complete Task 1: Library Catalogue Search"`), repeating for Tasks 2–7 and Documentation.
4. Update the GitHub link placeholder on the cover page of `Assignment_Report.docx` / `Assignment_Report.pdf` and push to GitHub.

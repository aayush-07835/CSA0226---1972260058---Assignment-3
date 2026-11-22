# Pseudocode Reference (Q1–Q7)

## Q1: Binary Search & Linear Search
```text
FUNCTION LinearSearch(A, n, key):
    FOR i <- 0 TO n - 1:
        comparisons <- comparisons + 1
        IF A[i] == key THEN RETURN i
    RETURN -1

FUNCTION BinarySearch(A, n, key):
    low <- 0, high <- n - 1
    WHILE low <= high:
        mid <- low + (high - low) / 2
        comparisons <- comparisons + 1
        IF A[mid] == key THEN RETURN mid
        ELSE IF A[mid] < key THEN low <- mid + 1
        ELSE high <- mid - 1
    RETURN -1
```

## Q2: Bubble, Selection, and Insertion Sort
```text
FUNCTION BubbleSort(A, n):
    FOR i <- 0 TO n - 2:
        swapped <- FALSE
        FOR j <- 0 TO n - 2 - i:
            IF A[j] > A[j + 1] THEN SWAP(A[j], A[j + 1]); swapped <- TRUE
        IF NOT swapped THEN BREAK

FUNCTION SelectionSort(A, n):
    FOR i <- 0 TO n - 2:
        min_idx <- i
        FOR j <- i + 1 TO n - 1:
            IF A[j] < A[min_idx] THEN min_idx <- j
        IF min_idx != i THEN SWAP(A[i], A[min_idx])

FUNCTION InsertionSort(A, n):
    FOR i <- 1 TO n - 1:
        key <- A[i]; j <- i - 1
        WHILE j >= 0 AND A[j] > key:
            A[j + 1] <- A[j]; j <- j - 1
        A[j + 1] <- key
```

## Q3: Two-Way Descending Merge
```text
FUNCTION MergeDesc(A, na, B, nb, Out):
    i <- 0, j <- 0, k <- 0
    WHILE i < na AND j < nb:
        IF A[i] >= B[j] THEN Out[k++] <- A[i++]
        ELSE Out[k++] <- B[j++]
    WHILE i < na: Out[k++] <- A[i++]
    WHILE j < nb: Out[k++] <- B[j++]
    RETURN k
```

## Q4: 2D Rainfall Analysis
```text
FOR i <- 0 TO 37: totals[i] <- SUM(rain[i][0..11])
FOR j <- 0 TO 11: monthly_avg[j] <- SUM(rain[0..37][j]) / 38.0
Find (best_d, best_m) maximizing rain[i][j]
threshold <- 0.60 * (SUM(totals[0..37]) / 38.0)
FOR i <- 0 TO 37: IF totals[i] < threshold THEN mark district i deficient
```

## Q5: Word Count & Palindrome Check (No `string.h`)
```text
FUNCTION WordCount(s):
    count <- 0, inside <- 0
    FOR i <- 0 WHILE s[i] != '\0':
        IF s[i] == ' ' THEN inside <- 0
        ELSE IF inside == 0 THEN inside <- 1; count <- count + 1
    RETURN count

FUNCTION IsPalindrome(s):
    left <- 0, right <- length(s) - 1
    WHILE left < right:
        WHILE left < right AND NOT isalpha(s[left]): left++
        WHILE left < right AND NOT isalpha(s[right]): right--
        IF tolower(s[left]) != tolower(s[right]) THEN RETURN 0
        left++; right--
    RETURN 1
```

## Q6: Index-Based String Sort & Binary Search
```text
Initialize idx[0..n-1] <- 0..n-1
Sort idx[] using strcmp(names[idx[j]], names[idx[j+1]]) > 0 (swap integers only)
BinarySearch(names, n, target): compare target with names[mid] using strcmp()
```

## Q7: Election Counting System
```text
Initialize counts[1..C] <- 0, valid <- 0, invalid <- 0
FOR each vote v in ballots[0..V-1]:
    IF 1 <= v <= C: counts[v]++; valid++
    ELSE: invalid++
Copy (id, counts[id]) to results[0..C-1]
Sort results[] descending by votes
top <- results[0].votes
tie_count <- count of results[i].votes == top
IF tie_count > 1 THEN report TIE among top candidates
ELSE report WINNER results[0].id
```

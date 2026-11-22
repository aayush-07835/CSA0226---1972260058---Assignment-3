# Task 7 — Design an Election Counting Program from First Principles (10 Marks)

**Objective:** Design, implement, verify, and defend a Student Council Election counting system (up to 12 candidates, up to 5,000 votes) using a single-pass `O(v)` count array, tie detection, invalid-vote filtering, and benchmarks for `5,000` and `500,000` votes against `O(v·c)` and `O(v log v)` alternatives.

## Files Included
- `Q7_Election_Counting.c` — Complete system (hand-verified test, tie test, 5,000-vote simulation)
- `Q7_Benchmark.c` — `5,000` & `500,000` vote runtime benchmark (`performance_comparison.csv`)
- `Q7_Alternative_Methods.c` — Candidate-list linear search `O(v·c)` & sort-all-votes `O(v log v)`
- `election_votes.csv`, `election_results.csv`, `performance_comparison.csv` — Verified CSV data
- `output/` — Verified `.txt` outputs & `q7_election_performance.png`

## Compile & Run
```bash
gcc -std=c11 -Wall -Wextra -pedantic -O2 Q7_Election_Counting.c -o q7_elec && ./q7_elec
gcc -std=c11 -Wall -Wextra -pedantic -O2 Q7_Benchmark.c -o q7_bench && ./q7_bench
```

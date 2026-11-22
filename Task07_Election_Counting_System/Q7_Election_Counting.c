#include <stdio.h>

#define MAX_CANDIDATES 12

typedef struct {
    int id;
    int votes;
} CandidateResult;

void run_election(const char *scenario_name, int num_candidates, const int votes[], int num_votes)
{
    int counts[MAX_CANDIDATES + 1] = {0}; /* 1-indexed candidate counts */
    int valid_votes = 0;
    int invalid_votes = 0;

    /* Single-pass O(v) counting */
    for (int i = 0; i < num_votes; i++) {
        int v = votes[i];
        if (v >= 1 && v <= num_candidates) {
            counts[v]++;
            valid_votes++;
        } else {
            invalid_votes++;
        }
    }

    /* Copy into result records before sorting so counts[] stays intact */
    CandidateResult results[MAX_CANDIDATES] = {{0, 0}};
    for (int c = 0; c < num_candidates; c++) {
        results[c].id = c + 1;
        results[c].votes = counts[c + 1];
    }

    /* Sort results in descending order of votes */
    for (int i = 0; i < num_candidates - 1; i++) {
        for (int j = 0; j < num_candidates - 1 - i; j++) {
            if (results[j].votes < results[j + 1].votes) {
                CandidateResult tmp = results[j];
                results[j] = results[j + 1];
                results[j + 1] = tmp;
            }
        }
    }

    printf("=== %s ===\n", scenario_name);
    printf("Total Ballots: %d | Valid: %d | Invalid: %d\n", num_votes, valid_votes, invalid_votes);
    for (int c = 0; c < num_candidates; c++) {
        double pct = valid_votes > 0 ? (100.0 * results[c].votes / valid_votes) : 0.0;
        printf("  Rank %d: Candidate #%d -> %d votes (%.2f%%)\n",
               c + 1, results[c].id, results[c].votes, pct);
    }

    if (valid_votes == 0) {
        printf("Result: No valid votes cast.\n\n");
        return;
    }

    int top_votes = results[0].votes;
    int tie_count = 0;
    for (int c = 0; c < num_candidates; c++) {
        if (results[c].votes == top_votes) tie_count++;
    }

    if (tie_count > 1) {
        printf("Result: TIE between %d candidates (", tie_count);
        for (int c = 0; c < tie_count; c++) {
            printf("Candidate #%d%s", results[c].id, (c + 1 < tie_count) ? ", " : "");
        }
        printf(") with %d votes each!\n\n", top_votes);
    } else {
        printf("Result: WINNER is Candidate #%d with %d votes!\n\n", results[0].id, top_votes);
    }
}

int main(void)
{
    /* Test 1: Hand-verified small set with invalid votes (0, -2, 6) and clear winner */
    int small_votes[] = {1, 2, 1, 0, 3, -2, 1, 6, 2, 4};
    run_election("Test 1: Hand-Verified Clear Winner + Invalid Votes", 4, small_votes, 10);

    /* Test 2: Tie scenario */
    int tie_votes[] = {2, 4, 2, 4, 1, 3, 0, 99};
    run_election("Test 2: Tie Detection", 4, tie_votes, 8);

    /* Test 3: Deterministic 5,000-vote election for 12 candidates */
    int votes_5000[5000];
    int counts[13] = {0};
    int valid = 0, invalid = 0;
    unsigned int lcg = 20261122u;

    FILE *f_v = fopen("election_votes.csv", "w");
    FILE *f_r = fopen("election_results.csv", "w");
    if (f_v) fprintf(f_v, "ballot_id,candidate_vote,is_valid\n");

    for (int i = 0; i < 5000; i++) {
        lcg = 1664525u * lcg + 1013904223u;
        int r = (int)((lcg >> 16) % 100);
        int vote = (r < 4) ? ((r == 0) ? 0 : (r == 1 ? -1 : 15)) : ((int)((lcg >> 8) % 12) + 1);
        votes_5000[i] = vote;
        int ok = (vote >= 1 && vote <= 12);
        if (ok) { counts[vote]++; valid++; } else { invalid++; }
        if (f_v) fprintf(f_v, "%d,%d,%d\n", i + 1, vote, ok);
    }
    if (f_v) fclose(f_v);

    run_election("Test 3: Full 5,000-Vote Student Council Election (12 Candidates)", 12, votes_5000, 5000);

    if (f_r) {
        fprintf(f_r, "candidate_id,votes,percentage_of_valid\n");
        for (int c = 1; c <= 12; c++) {
            fprintf(f_r, "%d,%d,%.2f\n", c, counts[c], 100.0 * counts[c] / valid);
        }
        fprintf(f_r, "INVALID,%d,0.00\n", invalid);
        fclose(f_r);
    }

    return 0;
}

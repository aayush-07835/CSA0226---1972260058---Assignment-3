#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DISTRICTS 38
#define MONTHS 12

/* 1. Annual rainfall total per district */
void compute_district_totals(int d_count, int m_count, double rain[][MONTHS], double totals[])
{
    for (int i = 0; i < d_count; i++) {
        double sum = 0.0;
        for (int j = 0; j < m_count; j++) {
            sum += rain[i][j];
        }
        totals[i] = sum;
    }
}

/* 2. Monthly average rainfall for the state */
void compute_monthly_avg(int d_count, int m_count, double rain[][MONTHS], double monthly_avg[])
{
    for (int j = 0; j < m_count; j++) {
        double sum = 0.0;
        for (int i = 0; i < d_count; i++) {
            sum += rain[i][j];
        }
        monthly_avg[j] = sum / d_count;
    }
}

/* 3. Wettest district-month */
double find_wettest(int d_count, int m_count, double rain[][MONTHS], int *best_d, int *best_m)
{
    double max_val = rain[0][0];
    *best_d = 0;
    *best_m = 0;
    for (int i = 0; i < d_count; i++) {
        for (int j = 0; j < m_count; j++) {
            if (rain[i][j] > max_val) {
                max_val = rain[i][j];
                *best_d = i;
                *best_m = j;
            }
        }
    }
    return max_val;
}

/* 4. Districts below 60% of the state average annual rainfall */
int find_deficient_districts(int d_count, const double totals[], double threshold, int deficient[])
{
    int count = 0;
    for (int i = 0; i < d_count; i++) {
        if (totals[i] < threshold) {
            deficient[count++] = i;
        }
    }
    return count;
}

/* Hand-verification on 3 x 4 dataset */
static void verify_3x4_hand_check(void)
{
    double small[3][4] = {
        {100.0, 120.0,  80.0, 100.0}, /* Total = 400 */
        { 40.0,  50.0,  30.0,  40.0}, /* Total = 160 (< 60% of 320 = 192) */
        {110.0, 130.0,  70.0,  90.0}  /* Total = 400 */
    };
    double totals[3] = {0};
    double m_avg[4] = {0};
    int best_d = 0, best_m = 0;
    double max_r = small[0][0];

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            totals[i] += small[i][j];
            m_avg[j] += small[i][j];
            if (small[i][j] > max_r) { max_r = small[i][j]; best_d = i; best_m = j; }
        }
    }
    double state_avg = (totals[0] + totals[1] + totals[2]) / 3.0; /* 960/3 = 320 */
    printf("=== Hand-Verified 3x4 Test ===\n");
    printf("District Totals: %.1f, %.1f, %.1f (State Avg = %.1f, 60%% Threshold = %.1f)\n",
           totals[0], totals[1], totals[2], state_avg, 0.6 * state_avg);
    printf("Monthly Averages: ");
    for (int j = 0; j < 4; j++) printf("%.2f ", m_avg[j] / 3.0);
    printf("\nWettest: District %d, Month %d (%.1f mm)\n", best_d + 1, best_m + 1, max_r);
    printf("Deficient Districts (< 192.0 mm): ");
    for (int i = 0; i < 3; i++) {
        if (totals[i] < 0.6 * state_avg) printf("District %d ", i + 1);
    }
    printf("\n\n");
}

int main(void)
{
    verify_3x4_hand_check();

    double rain[DISTRICTS][MONTHS];
    /* Deterministic seasonal rainfall model (mm) */
    const double base_month[MONTHS] = {18, 15, 22, 45, 78, 140, 195, 180, 150, 165, 110, 42};
    FILE *f_data = fopen("rainfall_data.csv", "w");
    if (!f_data) return 1;
    fprintf(f_data, "district_id,M1,M2,M3,M4,M5,M6,M7,M8,M9,M10,M11,M12,annual_total\n");

    for (int i = 0; i < DISTRICTS; i++) {
        /* Introduce 4 intentionally dry districts (indices 5, 14, 23, 32) below 60% */
        double factor = (i == 5 || i == 14 || i == 23 || i == 32) ? 0.45 : (0.85 + 0.015 * (i % 15));
        double row_sum = 0.0;
        fprintf(f_data, "District_%02d", i + 1);
        for (int j = 0; j < MONTHS; j++) {
            double val = base_month[j] * factor + ((i * 7 + j * 3) % 11);
            rain[i][j] = val;
            row_sum += val;
            fprintf(f_data, ",%.2f", val);
        }
        fprintf(f_data, ",%.2f\n", row_sum);
    }
    fclose(f_data);

    double totals[DISTRICTS];
    double monthly_avg[MONTHS];
    int deficient[DISTRICTS];
    int best_d = 0, best_m = 0;

    compute_district_totals(DISTRICTS, MONTHS, rain, totals);
    compute_monthly_avg(DISTRICTS, MONTHS, rain, monthly_avg);
    double max_rain = find_wettest(DISTRICTS, MONTHS, rain, &best_d, &best_m);

    double state_total = 0.0;
    for (int i = 0; i < DISTRICTS; i++) state_total += totals[i];
    double state_avg_annual = state_total / DISTRICTS;
    double threshold = 0.60 * state_avg_annual;
    int def_count = find_deficient_districts(DISTRICTS, totals, threshold, deficient);

    printf("=== 38 Districts x 12 Months Rainfall Analysis ===\n");
    printf("State Average Annual Rainfall: %.2f mm\n", state_avg_annual);
    printf("60%% Deficiency Threshold:      %.2f mm\n", threshold);
    printf("Wettest District-Month:        District %d, Month %d (%.2f mm)\n",
           best_d + 1, best_m + 1, max_rain);
    printf("Deficient Districts (%d):       ", def_count);
    for (int i = 0; i < def_count; i++) {
        printf("D%02d(%.1f) ", deficient[i] + 1, totals[deficient[i]]);
    }
    printf("\nMonthly State Averages: ");
    for (int j = 0; j < MONTHS; j++) printf("M%d:%.1f ", j + 1, monthly_avg[j]);
    printf("\n\n");

    /* Benchmark 2,000 x 2,000 row-wise vs column-wise traversal */
    const int N = 2000;
    double (*big)[2000] = malloc((size_t)N * sizeof(*big));
    if (!big) return 1;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            big[i][j] = (double)((i + j) % 100);
        }
    }

    volatile double sink = 0.0;
    struct timespec t0, t1;

    clock_gettime(CLOCK_MONOTONIC, &t0);
    double sum_row = 0.0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            sum_row += big[i][j];
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &t1);
    double row_ms = (t1.tv_sec - t0.tv_sec) * 1000.0 + (t1.tv_nsec - t0.tv_nsec) / 1e6;
    sink = sum_row;

    clock_gettime(CLOCK_MONOTONIC, &t0);
    double sum_col = 0.0;
    for (int j = 0; j < N; j++) {
        for (int i = 0; i < N; i++) {
            sum_col += big[i][j];
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &t1);
    double col_ms = (t1.tv_sec - t0.tv_sec) * 1000.0 + (t1.tv_nsec - t0.tv_nsec) / 1e6;
    sink += sum_col;
    (void)sink;

    printf("=== 2000 x 2000 Traversal Benchmark ===\n");
    printf("Row-wise traversal:    %.4f ms (sum = %.0f)\n", row_ms, sum_row);
    printf("Column-wise traversal: %.4f ms (sum = %.0f)\n", col_ms, sum_col);

    FILE *f_bm = fopen("traversal_benchmark.csv", "w");
    if (f_bm) {
        fprintf(f_bm, "layout_or_traversal,array_dimensions,time_ms,notes\n");
        fprintf(f_bm, "2D_Row_Wise,2000x2000,%.4f,Sequential memory access (cache-friendly)\n", row_ms);
        fprintf(f_bm, "2D_Column_Wise,2000x2000,%.4f,Strided memory access (16000-byte stride)\n", col_ms);
        fclose(f_bm);
    }

    free(big);
    return 0;
}

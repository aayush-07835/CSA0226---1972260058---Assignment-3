#include <stdio.h>

#define YEARS 3
#define DISTRICTS 4
#define MONTHS 12

/* Multi-year extension: rain[years][districts][months] */
int main(void)
{
    double rain[YEARS][DISTRICTS][MONTHS];

    for (int y = 0; y < YEARS; y++) {
        for (int d = 0; d < DISTRICTS; d++) {
            for (int m = 0; m < MONTHS; m++) {
                rain[y][d][m] = 50.0 + y * 10.0 + d * 5.0 + m * 2.5;
            }
        }
    }

    printf("=== 3D Rainfall Summary (Years = %d, Districts = %d, Months = %d) ===\n",
           YEARS, DISTRICTS, MONTHS);
    for (int y = 0; y < YEARS; y++) {
        double year_total = 0.0;
        for (int d = 0; d < DISTRICTS; d++) {
            double dist_total = 0.0;
            for (int m = 0; m < MONTHS; m++) {
                dist_total += rain[y][d][m];
            }
            year_total += dist_total;
        }
        printf("Year %d Total across %d districts: %.2f mm (Avg/district = %.2f mm)\n",
               2024 + y, DISTRICTS, year_total, year_total / DISTRICTS);
    }

    return 0;
}

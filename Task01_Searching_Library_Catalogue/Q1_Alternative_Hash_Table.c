#include <stdio.h>
#include <stdlib.h>

#define EMPTY_SLOT -1

/* Hash table with linear probing: h(key) = key % table_size */
typedef struct {
    int *table;
    int size;
} HashTable;

HashTable create_hash_table(int size)
{
    HashTable ht;
    ht.size = size;
    ht.table = malloc((size_t)size * sizeof(int));
    for (int i = 0; i < size; i++) {
        ht.table[i] = EMPTY_SLOT;
    }
    return ht;
}

void hash_insert(HashTable *ht, int key)
{
    int idx = key % ht->size;
    while (ht->table[idx] != EMPTY_SLOT) {
        idx = (idx + 1) % ht->size;
    }
    ht->table[idx] = key;
}

int hash_search(const HashTable *ht, int key, int *probes)
{
    *probes = 0;
    int idx = key % ht->size;
    int start = idx;
    while (ht->table[idx] != EMPTY_SLOT) {
        (*probes)++;
        if (ht->table[idx] == key) {
            return idx;
        }
        idx = (idx + 1) % ht->size;
        if (idx == start) break;
    }
    (*probes)++; /* final comparison confirming EMPTY_SLOT */
    return -1;
}

/* Interpolation search on uniformly distributed sorted array */
int interpolation_search(const int a[], int n, int key, int *probes)
{
    *probes = 0;
    int low = 0, high = n - 1;
    while (low <= high && key >= a[low] && key <= a[high]) {
        (*probes)++;
        if (low == high) {
            return (a[low] == key) ? low : -1;
        }
        long long num = (long long)(key - a[low]) * (high - low);
        int pos = low + (int)(num / (a[high] - a[low]));
        if (a[pos] == key) return pos;
        if (a[pos] < key) low = pos + 1;
        else high = pos - 1;
    }
    return -1;
}

int main(void)
{
    int accession[] = {1021, 1048, 1103, 1190, 1222, 1305, 1377, 1402, 1460, 1533};
    int n = sizeof(accession) / sizeof(accession[0]);
    int table_size = 23; /* Prime > 2*n for load factor < 0.5 */

    HashTable ht = create_hash_table(table_size);
    for (int i = 0; i < n; i++) {
        hash_insert(&ht, accession[i]);
    }

    int keys[] = {1021, 1305, 1533, 1400};
    printf("=== Alternative Methods on 10-Book Trial Catalogue ===\n");
    printf("Hash Table Size = %d (Load Factor = %.2f)\n", table_size, (double)n / table_size);
    for (int i = 0; i < 4; i++) {
        int h_probes = 0, i_probes = 0;
        int h_pos = hash_search(&ht, keys[i], &h_probes);
        int i_pos = interpolation_search(accession, n, keys[i], &i_probes);
        printf("Key %d -> Hash(slot=%2d, probes=%d) | Interpolation(idx=%2d, probes=%d)\n",
               keys[i], h_pos, h_probes, i_pos, i_probes);
    }

    free(ht.table);
    return 0;
}

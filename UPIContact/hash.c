/*
 * hash.c — Core Hash Table Engine
 * Collision Resolution: Linear Probing
 * Key: Mobile Number (string), Value: Contact record
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ── Slot states ─────────────────────────────────────────────────────────── */
#define EMPTY    0
#define OCCUPIED 1
#define DELETED  2

/* ── Data types ──────────────────────────────────────────────────────────── */
typedef struct {
    char mobile[16];  /* 10-digit Indian mobile number */
    char name[64];
    char upi_id[64];
    char bank[32];
    int  state;       /* EMPTY | OCCUPIED | DELETED */
} Contact;

typedef struct {
    Contact     *table;
    int          size;
    int          count;
    long long    collisions;
} HashTable;

/* ── Hash function ───────────────────────────────────────────────────────── */
/* Polynomial rolling hash on the mobile string */
static unsigned int hash_fn(const char *mobile, int size)
{
    unsigned long h = 5381UL;
    while (*mobile)
        h = h * 31UL + (unsigned char)(*mobile++);
    return (unsigned int)(h % (unsigned long)size);
}

/* ── Initialise / free ───────────────────────────────────────────────────── */
void ht_init(HashTable *ht, int size)
{
    int i;
    ht->table      = (Contact *)malloc((size_t)size * sizeof(Contact));
    ht->size       = size;
    ht->count      = 0;
    ht->collisions = 0;
    for (i = 0; i < size; i++)
        ht->table[i].state = EMPTY;
}

void ht_free(HashTable *ht)
{
    free(ht->table);
    ht->table  = NULL;
    ht->size   = 0;
    ht->count  = 0;
    ht->collisions = 0;
}

/* ── Insert ──────────────────────────────────────────────────────────────── */
/*  Returns:  1 = success, 0 = duplicate key, -1 = table full               */
int ht_insert(HashTable *ht,
              const char *mobile,
              const char *name,
              const char *upi_id,
              const char *bank)
{
    unsigned int idx, start;
    int first_deleted;

    if (ht->count >= ht->size)
        return -1;

    idx           = hash_fn(mobile, ht->size);
    start         = idx;
    first_deleted = -1;

    do {
        if (ht->table[idx].state == OCCUPIED) {
            if (strcmp(ht->table[idx].mobile, mobile) == 0)
                return 0;           /* duplicate */
            ht->collisions++;       /* occupied by a different key */
        } else if (ht->table[idx].state == DELETED) {
            if (first_deleted < 0)
                first_deleted = (int)idx;
        } else {
            /* EMPTY slot — insert here (or at first deleted slot) */
            int at = (first_deleted >= 0) ? first_deleted : (int)idx;
            strncpy(ht->table[at].mobile, mobile, 15);
            strncpy(ht->table[at].name,   name,   63);
            strncpy(ht->table[at].upi_id, upi_id, 63);
            strncpy(ht->table[at].bank,   bank,   31);
            ht->table[at].mobile[15] = '\0';
            ht->table[at].name[63]   = '\0';
            ht->table[at].upi_id[63] = '\0';
            ht->table[at].bank[31]   = '\0';
            ht->table[at].state = OCCUPIED;
            ht->count++;
            return 1;
        }
        idx = (idx + 1) % (unsigned int)ht->size;
    } while (idx != start);

    /* All slots scanned; use first deleted slot if found */
    if (first_deleted >= 0) {
        strncpy(ht->table[first_deleted].mobile, mobile, 15);
        strncpy(ht->table[first_deleted].name,   name,   63);
        strncpy(ht->table[first_deleted].upi_id, upi_id, 63);
        strncpy(ht->table[first_deleted].bank,   bank,   31);
        ht->table[first_deleted].mobile[15] = '\0';
        ht->table[first_deleted].name[63]   = '\0';
        ht->table[first_deleted].upi_id[63] = '\0';
        ht->table[first_deleted].bank[31]   = '\0';
        ht->table[first_deleted].state = OCCUPIED;
        ht->count++;
        return 1;
    }
    return -1; /* full */
}

/* ── Search ──────────────────────────────────────────────────────────────── */
/*  Returns slot index, or -1 if not found.                                  */
int ht_search(HashTable *ht, const char *mobile)
{
    unsigned int idx = hash_fn(mobile, ht->size);
    unsigned int start = idx;

    do {
        if (ht->table[idx].state == EMPTY)
            return -1;
        if (ht->table[idx].state == OCCUPIED &&
            strcmp(ht->table[idx].mobile, mobile) == 0)
            return (int)idx;
        idx = (idx + 1) % (unsigned int)ht->size;
    } while (idx != start);

    return -1;
}

/* ── Update ──────────────────────────────────────────────────────────────── */
/*  Returns 1 = success, 0 = not found. Mobile number is never changed.      */
int ht_update(HashTable *ht,
              const char *mobile,
              const char *name,
              const char *upi_id,
              const char *bank)
{
    int idx = ht_search(ht, mobile);
    if (idx < 0) return 0;
    strncpy(ht->table[idx].name,   name,   63);
    strncpy(ht->table[idx].upi_id, upi_id, 63);
    strncpy(ht->table[idx].bank,   bank,   31);
    ht->table[idx].name[63]   = '\0';
    ht->table[idx].upi_id[63] = '\0';
    ht->table[idx].bank[31]   = '\0';
    return 1;
}

/* ── Delete ──────────────────────────────────────────────────────────────── */
/*  Returns 1 = success, 0 = not found. Uses lazy deletion.                  */
int ht_delete(HashTable *ht, const char *mobile)
{
    int idx = ht_search(ht, mobile);
    if (idx < 0) return 0;
    ht->table[idx].state = DELETED;
    ht->count--;
    return 1;
}

/* ── Display ─────────────────────────────────────────────────────────────── */
void ht_display(HashTable *ht)
{
    int i, printed;
    printf("\n%-8s %-16s %-28s %-28s %-18s\n",
           "Index", "Mobile", "Name", "UPI ID", "Bank");
    printf("%-8s %-16s %-28s %-28s %-18s\n",
           "--------", "----------------",
           "----------------------------", "----------------------------",
           "------------------");
    printed = 0;
    for (i = 0; i < ht->size; i++) {
        if (ht->table[i].state == OCCUPIED) {
            printf("%-8d %-16s %-28s %-28s %-18s\n",
                   i,
                   ht->table[i].mobile,
                   ht->table[i].name,
                   ht->table[i].upi_id,
                   ht->table[i].bank);
            printed++;
        }
    }
    printf("\n  Total contacts shown: %d\n", printed);
}

/* ── Metrics ─────────────────────────────────────────────────────────────── */
float ht_load_factor(HashTable *ht)
{
    return (ht->size == 0) ? 0.0f
                           : (float)ht->count / (float)ht->size;
}

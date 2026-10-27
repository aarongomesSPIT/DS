#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EMPTY 0
#define OCCUPIED 1
#define DELETED 2

typedef struct
{
    char mobile[16];
    char name[64];
    char upi_id[64];
    char bank[32];
    int state;
} Contact;

typedef struct
{
    Contact *table;
    int size;
    int count;
    int collisions;
} HashTable;

int hash_fn(char *mobile, int size)
{
    int h = 0;
    int i;
    for (i = 0; mobile[i] != '\0'; i++)
    {
        h = (h * 31 + mobile[i]) % size;
    }
    if (h < 0)
    {
        h = -h;
    }
    return h;
}

void ht_init(HashTable *ht, int size)
{
    int i;
    ht->table = (Contact *)malloc(size * sizeof(Contact));
    ht->size = size;
    ht->count = 0;
    ht->collisions = 0;
    for (i = 0; i < size; i++)
    {
        ht->table[i].state = EMPTY;
    }
}

void ht_free(HashTable *ht)
{
    free(ht->table);
    ht->table = NULL;
    ht->size = 0;
    ht->count = 0;
    ht->collisions = 0;
}

int ht_insert(HashTable *ht, char *mobile, char *name, char *upi_id, char *bank)
{
    int idx, start, first_deleted;

    if (ht->count >= ht->size)
    {
        return -1;
    }

    idx = hash_fn(mobile, ht->size);
    start = idx;
    first_deleted = -1;

    do
    {
        if (ht->table[idx].state == OCCUPIED)
        {
            if (strcmp(ht->table[idx].mobile, mobile) == 0)
            {
                return 0;
            }
            ht->collisions++;
        }
        else if (ht->table[idx].state == DELETED)
        {
            if (first_deleted < 0)
            {
                first_deleted = idx;
            }
        }
        else
        {
            int at = (first_deleted >= 0) ? first_deleted : idx;
            strcpy(ht->table[at].mobile, mobile);
            strcpy(ht->table[at].name, name);
            strcpy(ht->table[at].upi_id, upi_id);
            strcpy(ht->table[at].bank, bank);
            ht->table[at].state = OCCUPIED;
            ht->count++;
            return 1;
        }
        idx = (idx + 1) % ht->size;
    } while (idx != start);

    if (first_deleted >= 0)
    {
        strcpy(ht->table[first_deleted].mobile, mobile);
        strcpy(ht->table[first_deleted].name, name);
        strcpy(ht->table[first_deleted].upi_id, upi_id);
        strcpy(ht->table[first_deleted].bank, bank);
        ht->table[first_deleted].state = OCCUPIED;
        ht->count++;
        return 1;
    }

    return -1;
}

int ht_search(HashTable *ht, char *mobile)
{
    int idx = hash_fn(mobile, ht->size);
    int start = idx;

    do
    {
        if (ht->table[idx].state == EMPTY)
        {
            return -1;
        }
        if (ht->table[idx].state == OCCUPIED && strcmp(ht->table[idx].mobile, mobile) == 0)
        {
            return idx;
        }
        idx = (idx + 1) % ht->size;
    } while (idx != start);

    return -1;
}

int ht_update(HashTable *ht, char *mobile, char *name, char *upi_id, char *bank)
{
    int idx = ht_search(ht, mobile);
    if (idx < 0)
    {
        return 0;
    }
    strcpy(ht->table[idx].name, name);
    strcpy(ht->table[idx].upi_id, upi_id);
    strcpy(ht->table[idx].bank, bank);
    return 1;
}

int ht_delete(HashTable *ht, char *mobile)
{
    int idx = ht_search(ht, mobile);
    if (idx < 0)
    {
        return 0;
    }
    ht->table[idx].state = DELETED;
    ht->count--;
    return 1;
}

void ht_display(HashTable *ht)
{
    int i, printed = 0;
    printf("\nIndex\tMobile\t\tName\t\tUPI ID\t\tBank\n");
    printf("----------------------------------------------------------------------\n");
    for (i = 0; i < ht->size; i++)
    {
        if (ht->table[i].state == OCCUPIED)
        {
            printf("%d\t%s\t%s\t%s\t%s\n",
                   i,
                   ht->table[i].mobile,
                   ht->table[i].name,
                   ht->table[i].upi_id,
                   ht->table[i].bank);
            printed++;
        }
    }
    printf("\nTotal contacts displayed: %d\n", printed);
}

float ht_load_factor(HashTable *ht)
{
    if (ht->size == 0)
        return 0.0f;
    return (float)ht->count / (float)ht->size;
}

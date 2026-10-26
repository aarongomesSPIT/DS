#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10007

typedef struct UserRecord
{
    char username[64];
    char fullname[128];
    char email[128];
    char regdate[20];
} UserRecord;

typedef struct Node
{
    UserRecord user;
    struct Node *next;
} Node;

typedef struct
{
    Node *buckets[TABLE_SIZE];
    int count;
    int collisions;
} HashTable;

int hash(char *key)
{
    unsigned long h = 5381;
    while (*key)
        h = h * 33 + (unsigned char)*key++;
    return (int)(h % TABLE_SIZE);
}

void ht_init(HashTable *ht)
{
    int i;
    ht->count = 0;
    ht->collisions = 0;
    for (i = 0; i < TABLE_SIZE; i++)
        ht->buckets[i] = NULL;
}

int ht_insert(HashTable *ht, UserRecord *u)
{
    int idx = hash(u->username);
    Node *cur = ht->buckets[idx];
    while (cur)
    {
        if (strcmp(cur->user.username, u->username) == 0)
            return 0;
        cur = cur->next;
    }
    if (ht->buckets[idx] != NULL)
        ht->collisions++;
    Node *n = (Node *)malloc(sizeof(Node));
    n->user = *u;
    n->next = ht->buckets[idx];
    ht->buckets[idx] = n;
    ht->count++;
    return 1;
}

UserRecord *ht_search(HashTable *ht, char *username)
{
    int idx = hash(username);
    Node *cur = ht->buckets[idx];
    while (cur)
    {
        if (strcmp(cur->user.username, username) == 0)
            return &cur->user;
        cur = cur->next;
    }
    return NULL;
}

int ht_delete(HashTable *ht, char *username)
{
    int idx = hash(username);
    Node *cur = ht->buckets[idx];
    Node *prev = NULL;
    while (cur)
    {
        if (strcmp(cur->user.username, username) == 0)
        {
            if (prev)
                prev->next = cur->next;
            else
                ht->buckets[idx] = cur->next;
            free(cur);
            ht->count--;
            return 1;
        }
        prev = cur;
        cur = cur->next;
    }
    return 0;
}

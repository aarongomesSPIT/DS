#include "hash.c"

HashTable ht;

void REGISTER_USER(char *username, char *fullname, char *email, char *regdate) {
    UserRecord u;
    strcpy(u.username, username);
    strcpy(u.fullname, fullname);
    strcpy(u.email, email);
    strcpy(u.regdate, regdate);
    if (ht_insert(&ht, &u))
        printf("User '%s' registered successfully.\n", username);
    else
        printf("Username '%s' is already taken.\n", username);
}

void CHECK_USERNAME(char *username) {
    if (ht_search(&ht, username))
        printf("Username '%s' is TAKEN.\n", username);
    else
        printf("Username '%s' is AVAILABLE.\n", username);
}

void UPDATE_USER(char *username, char *new_fullname, char *new_email) {
    UserRecord *u = ht_search(&ht, username);
    if (!u) {
        printf("User '%s' not found.\n", username);
        return;
    }
    if (new_fullname[0]) { memcpy(u->fullname, new_fullname, 127); u->fullname[127] = 0; }
    if (new_email[0])    { memcpy(u->email,    new_email,    127); u->email[127]    = 0; }
    printf("User '%s' updated.\n", username);
    printf("  Full Name : %s\n", u->fullname);
    printf("  Email     : %s\n", u->email);
}

void DELETE_USER(char *username) {
    if (ht_delete(&ht, username))
        printf("User '%s' deleted.\n", username);
    else
        printf("User '%s' not found.\n", username);
}

void DISPLAY_USERS() {
    int i, found = 0;
    printf("\n%-20s %-30s %-35s %-12s\n", "Username", "Full Name", "Email", "Reg. Date");
    printf("%-20s %-30s %-35s %-12s\n",
           "--------------------", "------------------------------",
           "-----------------------------------", "------------");
    for (i = 0; i < TABLE_SIZE; i++) {
        Node *cur = ht.buckets[i];
        while (cur) {
            printf("%-20s %-30s %-35s %-12s\n",
                   cur->user.username, cur->user.fullname,
                   cur->user.email, cur->user.regdate);
            found++;
            cur = cur->next;
        }
    }
    if (!found)
        printf("  (no users registered)\n");
    printf("\nTotal: %d users\n", found);
}

void TOTAL_COLLISIONS() {
    printf("Total collisions: %d\n", ht.collisions);
}

void LOAD_FACTOR() {
    printf("Load factor: %.4f  (%d / %d)\n",
           (double)ht.count / TABLE_SIZE, ht.count, TABLE_SIZE);
}

void bulk_seed(int n) {
    int i, inserted = 0;
    unsigned long s = 987654321UL;
    char chars[] = "abcdefghijklmnopqrstuvwxyz0123456789";
    int cs = 36;
    char uname[64], fname[128], email[128], date[20];
    char a[9], b[7], c[7];
    int y, m, d;

    for (i = 0; i < n; i++) {
        int j;
        for (j = 0; j < 8; j++) { s = s * 1664525UL + 1013904223UL; a[j] = chars[s % cs]; }
        a[8] = '\0';
        for (j = 0; j < 6; j++) { s = s * 1664525UL + 1013904223UL; b[j] = chars[s % cs]; }
        b[6] = '\0';
        for (j = 0; j < 6; j++) { s = s * 1664525UL + 1013904223UL; c[j] = chars[s % cs]; }
        c[6] = '\0';

        sprintf(uname,  "user_%s", a);
        sprintf(fname,  "%s %s", b, c);
        sprintf(email,  "%s@example.com", uname);

        s = s * 1664525UL + 1013904223UL;
        y = 2018 + (int)(s % 7);
        m = 1    + (int)((s >> 4) % 12);
        d = 1    + (int)((s >> 8) % 28);
        sprintf(date, "%04d-%02d-%02d", y, m, d);

        UserRecord u;
        strcpy(u.username, uname);
        strcpy(u.fullname, fname);
        strcpy(u.email,    email);
        strcpy(u.regdate,  date);
        if (ht_insert(&ht, &u)) inserted++;
    }
    printf("Bulk seed done. Inserted: %d\n", inserted);
    TOTAL_COLLISIONS();
    LOAD_FACTOR();
}
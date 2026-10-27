/*
 * upi.c — UPI Contact Platform Layer
 * Exactly seven platform operations as per the problem statement.
 * Include chain:  main.c → upi.c → hash.c
 */

#include "hash.c"

/* ── Global hash table instance ─────────────────────────────────────────── */
static HashTable g_ht;

/* ── Infrastructure ──────────────────────────────────────────────────────── */
void platform_init(int size)
{
    ht_init(&g_ht, size);
    printf("[INFO] Hash table initialised — size: %d  (linear probing)\n", size);
}

void platform_cleanup(void)
{
    ht_free(&g_ht);
}

/* Helper: consume leftover characters up to newline */
static void flush_stdin(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

/* Helper: read a line that may contain spaces, after a previous scanf */
static void read_line(char *buf, int max)
{
    flush_stdin();
    if (fgets(buf, max, stdin))
        buf[strcspn(buf, "\n")] = '\0';
}

/* ── 1. ADD-CONTACT ──────────────────────────────────────────────────────── */
/*  ADD-CONTACT MobileNumber Name UPI_ID BankName                            */
void add_contact(void)
{
    char mobile[16], name[64], upi_id[64], bank[32];
    int  res, idx;

    printf("  Mobile Number : "); scanf("%15s",  mobile);
    printf("  Name          : "); read_line(name,   sizeof(name));
    printf("  UPI ID        : "); scanf("%63s",  upi_id);
    printf("  Bank Name     : "); read_line(bank,   sizeof(bank));

    res = ht_insert(&g_ht, mobile, name, upi_id, bank);
    if (res == 1) {
        idx = ht_search(&g_ht, mobile);
        printf("[SUCCESS] Contact added at table index %d.\n", idx);
    } else if (res == 0) {
        printf("[ERROR]   Mobile %s already exists.\n", mobile);
    } else {
        printf("[ERROR]   Hash table is full.\n");
    }
}

/* ── 2. SEARCH-CONTACT ───────────────────────────────────────────────────── */
/*  SEARCH-CONTACT MobileNumber                                               */
void search_contact(void)
{
    char    mobile[16];
    int     idx;
    Contact *c;

    printf("  Mobile Number : "); scanf("%15s", mobile);

    idx = ht_search(&g_ht, mobile);
    if (idx < 0) {
        printf("[NOT FOUND] No contact for mobile: %s\n", mobile);
        return;
    }
    c = &g_ht.table[idx];
    printf("\n  ┌─ Contact Details ─────────────────────┐\n");
    printf("  │  Table Index : %-24d│\n", idx);
    printf("  │  Mobile      : %-24s│\n", c->mobile);
    printf("  │  Name        : %-24s│\n", c->name);
    printf("  │  UPI ID      : %-24s│\n", c->upi_id);
    printf("  │  Bank        : %-24s│\n", c->bank);
    printf("  └───────────────────────────────────────┘\n");
}

/* ── 3. UPDATE-CONTACT ───────────────────────────────────────────────────── */
/*  UPDATE-CONTACT MobileNumber Name UPI_ID BankName                         */
/*  Mobile number is the immutable key and cannot be changed.                 */
void update_contact(void)
{
    char mobile[16], name[64], upi_id[64], bank[32];

    printf("  Mobile Number (key — unchanged) : "); scanf("%15s", mobile);
    printf("  New Name                        : "); read_line(name,   sizeof(name));
    printf("  New UPI ID                      : "); scanf("%63s", upi_id);
    printf("  New Bank Name                   : "); read_line(bank,   sizeof(bank));

    if (ht_update(&g_ht, mobile, name, upi_id, bank))
        printf("[SUCCESS] Contact updated.\n");
    else
        printf("[NOT FOUND] No contact for mobile: %s\n", mobile);
}

/* ── 4. DELETE-CONTACT ───────────────────────────────────────────────────── */
/*  DELETE-CONTACT MobileNumber                                               */
void delete_contact(void)
{
    char mobile[16];

    printf("  Mobile Number : "); scanf("%15s", mobile);

    if (ht_delete(&g_ht, mobile))
        printf("[SUCCESS] Contact deleted.\n");
    else
        printf("[NOT FOUND] No contact for mobile: %s\n", mobile);
}

/* ── 5. DISPLAY-CONTACTS ─────────────────────────────────────────────────── */
/*  Lists every occupied slot with its table index and contact details.       */
void display_contacts(void)
{
    if (g_ht.count == 0) {
        printf("[INFO] Hash table is empty.\n");
        return;
    }
    ht_display(&g_ht);
}

/* ── 6. TOTAL-COLLISIONS ─────────────────────────────────────────────────── */
/*  Reports the cumulative collision count since the table was initialised.   */
void total_collisions(void)
{
    printf("  Total Collisions : %lld\n", g_ht.collisions);
}

/* ── 7. LOAD-FACTOR ──────────────────────────────────────────────────────── */
/*  α = Records Stored / Table Size                                           */
void load_factor(void)
{
    float lf = ht_load_factor(&g_ht);
    printf("  Stored Records   : %d\n",     g_ht.count);
    printf("  Table Size       : %d\n",     g_ht.size);
    printf("  Load Factor (α)  : %.4f  (%.2f%%)\n", lf, lf * 100.0f);
}
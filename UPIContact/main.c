/*
 * main.c — Smart UPI Contact Lookup System
 * Entry point with switch-case menu.
 * Include chain:  main.c → upi.c → hash.c
 */

#include "upi.c"

/* ── Bulk contact generator (performance evaluation — min 5000) ──────────── */
static void bulk_generate(HashTable *ht)
{
    static const char *banks[] = {
        "SBI", "HDFC", "ICICI", "Axis Bank", "Kotak",
        "PNB", "Bank of Baroda", "Canara", "IDFC First", "Yes Bank"
    };
    static const char *first_names[] = {
        "Aarav","Vivaan","Aditya","Vihaan","Arjun",
        "Sai","Rehan","Rohan","Karan","Dev",
        "Priya","Ananya","Isha","Neha","Pooja",
        "Riya","Sneha","Tanya","Usha","Vidya"
    };
    static const char *last_names[] = {
        "Sharma","Verma","Gupta","Singh","Kumar",
        "Patel","Shah","Mehta","Joshi","Nair"
    };

    int       n, capacity, added, i;
    char      mobile[16], name[64], upi_id[64], bank[32];
    long long base = 9000000000LL;

    printf("  Contacts to generate (min 5000) : "); scanf("%d", &n);
    if (n < 1) { printf("[ERROR] Invalid count.\n"); return; }

    capacity = ht->size - ht->count;
    if (n > capacity) {
        printf("[WARNING] Only %d free slots remain — capping to %d.\n",
               capacity, capacity);
        n = capacity;
    }

    added = 0;
    for (i = 0; i < n; i++) {
        long long mob = base + (long long)i;
        sprintf(mobile, "%lld", mob);
        sprintf(name,   "%s %s", first_names[i % 20], last_names[i % 10]);
        sprintf(upi_id, "%s%04lld@upi", first_names[i % 20], mob % 10000LL);
        strncpy(bank, banks[i % 10], 31); bank[31] = '\0';
        if (ht_insert(ht, mobile, name, upi_id, bank) == 1)
            added++;
    }

    printf("\n  ┌─ Bulk Generation Summary ─────────────────┐\n");
    printf("  │  Requested          : %-20d│\n", n);
    printf("  │  Inserted           : %-20d│\n", added);
    printf("  │  Total Collisions   : %-20lld│\n", ht->collisions);
    printf("  │  Load Factor (α)    : %-20.4f│\n", ht_load_factor(ht));
    printf("  └───────────────────────────────────────────┘\n");
}

/* ── Menu ────────────────────────────────────────────────────────────────── */
static void print_menu(void)
{
    printf("\n╔══════════════════════════════════════════════╗\n");
    printf("║      Smart UPI Contact Lookup System         ║\n");
    printf("╠══════════════════════════════════════════════╣\n");
    printf("║  1. ADD-CONTACT                              ║\n");
    printf("║  2. SEARCH-CONTACT                           ║\n");
    printf("║  3. UPDATE-CONTACT                           ║\n");
    printf("║  4. DELETE-CONTACT                           ║\n");
    printf("║  5. DISPLAY-CONTACTS                         ║\n");
    printf("║  6. TOTAL-COLLISIONS                         ║\n");
    printf("║  7. LOAD-FACTOR                              ║\n");
    printf("║  8. BULK-GENERATE  (min 5000 records)        ║\n");
    printf("║  0. EXIT                                     ║\n");
    printf("╚══════════════════════════════════════════════╝\n");
    printf("  Choice: ");
}

/* ── Main ────────────────────────────────────────────────────────────────── */
int main(void)
{
    int size, choice;

    printf("╔══════════════════════════════════════════════╗\n");
    printf("║   Sardar Patel Institute of Technology       ║\n");
    printf("║   Smart UPI Contact Lookup — Hash Table      ║\n");
    printf("╚══════════════════════════════════════════════╝\n\n");

    printf("Enter hash table size (recommended >= 6007 for 5000 records): ");
    if (scanf("%d", &size) != 1 || size <= 0) {
        printf("[ERROR] Invalid table size.\n");
        return 1;
    }

    platform_init(size);

    do {
        print_menu();
        if (scanf("%d", &choice) != 1) {
            flush_stdin();
            choice = -1;
        }

        switch (choice) {
        case 1:
            printf("\n-- ADD-CONTACT --\n");
            add_contact();
            break;
        case 2:
            printf("\n-- SEARCH-CONTACT --\n");
            search_contact();
            break;
        case 3:
            printf("\n-- UPDATE-CONTACT --\n");
            update_contact();
            break;
        case 4:
            printf("\n-- DELETE-CONTACT --\n");
            delete_contact();
            break;
        case 5:
            printf("\n-- DISPLAY-CONTACTS --\n");
            display_contacts();
            break;
        case 6:
            printf("\n-- TOTAL-COLLISIONS --\n");
            total_collisions();
            break;
        case 7:
            printf("\n-- LOAD-FACTOR --\n");
            load_factor();
            break;
        case 8:
            printf("\n-- BULK-GENERATE --\n");
            bulk_generate(&g_ht);
            break;
        case 0:
            printf("\n[INFO] Exiting. Goodbye!\n");
            break;
        default:
            printf("[ERROR] Invalid choice. Enter 0–8.\n");
            break;
        }
    } while (choice != 0);

    platform_cleanup();
    return 0;
}
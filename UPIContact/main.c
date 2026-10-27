#include "upi.c"

void bulk_generate()
{
    char *banks[] = {
        "SBI", "HDFC", "ICICI", "Axis Bank", "Kotak",
        "PNB", "Bank of Baroda", "Canara", "IDFC First", "Yes Bank"};
    char *first_names[] = {
        "Aarav", "Vivaan", "Aditya", "Vihaan", "Arjun",
        "Sai", "Rehan", "Rohan", "Karan", "Dev",
        "Priya", "Ananya", "Isha", "Neha", "Pooja",
        "Riya", "Sneha", "Tanya", "Usha", "Vidya"};
    char *last_names[] = {
        "Sharma", "Verma", "Gupta", "Singh", "Kumar",
        "Patel", "Shah", "Mehta", "Joshi", "Nair"};

    int n, capacity, added, i;
    char mobile[16], name[64], upi_id[64], bank[32];

    printf("Enter number of contacts to generate (min 5000): ");
    scanf("%d", &n);
    if (n < 1)
    {
        printf("Invalid count.\n");
        return;
    }

    capacity = ht.size - ht.count;
    if (n > capacity)
    {
        printf("Only %d free slots remain. Generating %d records.\n", capacity, capacity);
        n = capacity;
    }

    added = 0;
    for (i = 0; i < n; i++)
    {
        sprintf(mobile, "98000%05d", i);
        sprintf(name, "%s %s", first_names[i % 20], last_names[i % 10]);
        sprintf(upi_id, "%s%04d@upi", first_names[i % 20], i % 10000);
        strcpy(bank, banks[i % 10]);

        if (ht_insert(&ht, mobile, name, upi_id, bank) == 1)
        {
            added++;
        }
    }

    printf("\n--- Bulk Generation Summary ---\n");
    printf("Requested        : %d\n", n);
    printf("Inserted         : %d\n", added);
    printf("Total Collisions : %d\n", ht.collisions);
    printf("Load Factor      : %.4f\n", ht_load_factor(&ht));
}

void print_menu()
{
    printf("\n--- Smart UPI Contact Lookup System ---\n");
    printf("1. Add Contact\n");
    printf("2. Search Contact\n");
    printf("3. Update Contact\n");
    printf("4. Delete Contact\n");
    printf("5. Display Contacts\n");
    printf("6. Total Collisions\n");
    printf("7. Load Factor\n");
    printf("8. Bulk Generate (min 5000 records)\n");
    printf("0. Exit\n");
    printf("Enter your choice: ");
}

int main()
{
    int size, choice;

    printf("Enter hash table size (e.g. 7001 for 5000 records): ");
    if (scanf("%d", &size) != 1 || size <= 0)
    {
        printf("Invalid table size.\n");
        return 1;
    }

    platform_init(size);

    do
    {
        print_menu();
        if (scanf("%d", &choice) != 1)
        {
            flush_stdin();
            choice = -1;
        }

        switch (choice)
        {
        case 1:
            add_contact();
            break;
        case 2:
            search_contact();
            break;
        case 3:
            update_contact();
            break;
        case 4:
            delete_contact();
            break;
        case 5:
            display_contacts();
            break;
        case 6:
            total_collisions();
            break;
        case 7:
            load_factor();
            break;
        case 8:
            bulk_generate();
            break;
        case 0:
            printf("Exiting program.\n");
            break;
        default:
            printf("Invalid choice. Please enter a number between 0 and 8.\n");
            break;
        }
    } while (choice != 0);

    platform_cleanup();
    return 0;
}
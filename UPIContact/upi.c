#include "hash.c"

HashTable ht;

void platform_init(int size)
{
    ht_init(&ht, size);
    printf("Hash table initialised with size: %d\n", size);
}

void platform_cleanup()
{
    ht_free(&ht);
}

void flush_stdin()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void read_line(char *buf, int max)
{
    flush_stdin();
    if (fgets(buf, max, stdin))
    {
        buf[strcspn(buf, "\n")] = '\0';
    }
}

void add_contact()
{
    char mobile[16], name[64], upi_id[64], bank[32];
    int res, idx;

    printf("Enter Mobile Number: ");
    scanf("%15s", mobile);
    printf("Enter Name: ");
    read_line(name, sizeof(name));
    printf("Enter UPI ID: ");
    scanf("%63s", upi_id);
    printf("Enter Bank Name: ");
    read_line(bank, sizeof(bank));

    res = ht_insert(&ht, mobile, name, upi_id, bank);
    if (res == 1)
    {
        idx = ht_search(&ht, mobile);
        printf("Contact added successfully at index %d.\n", idx);
    }
    else if (res == 0)
    {
        printf("Error: Mobile number %s already exists.\n", mobile);
    }
    else
    {
        printf("Error: Hash table is full.\n");
    }
}

void search_contact()
{
    char mobile[16];
    int idx;
    Contact *c;

    printf("Enter Mobile Number to search: ");
    scanf("%15s", mobile);

    idx = ht_search(&ht, mobile);
    if (idx < 0)
    {
        printf("Contact not found for mobile: %s\n", mobile);
        return;
    }

    c = &ht.table[idx];
    printf("\n--- Contact Found ---\n");
    printf("Table Index : %d\n", idx);
    printf("Mobile      : %s\n", c->mobile);
    printf("Name        : %s\n", c->name);
    printf("UPI ID      : %s\n", c->upi_id);
    printf("Bank        : %s\n", c->bank);
}

void update_contact()
{
    char mobile[16], name[64], upi_id[64], bank[32];

    printf("Enter Mobile Number (key): ");
    scanf("%15s", mobile);
    printf("Enter New Name: ");
    read_line(name, sizeof(name));
    printf("Enter New UPI ID: ");
    scanf("%63s", upi_id);
    printf("Enter New Bank Name: ");
    read_line(bank, sizeof(bank));

    if (ht_update(&ht, mobile, name, upi_id, bank))
    {
        printf("Contact updated successfully.\n");
    }
    else
    {
        printf("Contact not found for mobile: %s\n", mobile);
    }
}

void delete_contact()
{
    char mobile[16];

    printf("Enter Mobile Number to delete: ");
    scanf("%15s", mobile);

    if (ht_delete(&ht, mobile))
    {
        printf("Contact deleted successfully.\n");
    }
    else
    {
        printf("Contact not found for mobile: %s\n", mobile);
    }
}

void display_contacts()
{
    if (ht.count == 0)
    {
        printf("Hash table is empty.\n");
        return;
    }
    ht_display(&ht);
}

void total_collisions()
{
    printf("Total Collisions: %d\n", ht.collisions);
}

void load_factor()
{
    float lf = ht_load_factor(&ht);
    printf("Stored Records : %d\n", ht.count);
    printf("Table Size     : %d\n", ht.size);
    printf("Load Factor    : %.4f (%.2f%%)\n", lf, lf * 100.0f);
}
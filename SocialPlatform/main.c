#include "platform.c"

#pragma GCC diagnostic ignored "-Wunused-result"

int main()
{
    char line[16];
    int choice;
    char username[64], fullname[128], email[128], regdate[20];
    char new_fullname[128], new_email[128];
    int n;

    ht_init(&ht);

    do
    {
        printf("\n1. REGISTER-USER\n");
        printf("2. CHECK-USERNAME\n");
        printf("3. UPDATE-USER\n");
        printf("4. DELETE-USER\n");
        printf("5. DISPLAY-USERS\n");
        printf("6. TOTAL-COLLISIONS\n");
        printf("7. LOAD-FACTOR\n");
        printf("8. BULK-SEED\n");
        printf("0. EXIT\n");
        printf("Choice: ");
        fgets(line, sizeof(line), stdin);
        choice = atoi(line);

        switch (choice)
        {
        case 1:
            printf("Username: ");
            fgets(username, 64, stdin);
            username[strcspn(username, "\n")] = 0;
            printf("Full Name: ");
            fgets(fullname, 128, stdin);
            fullname[strcspn(fullname, "\n")] = 0;
            printf("Email: ");
            fgets(email, 128, stdin);
            email[strcspn(email, "\n")] = 0;
            printf("Reg Date: ");
            fgets(regdate, 20, stdin);
            regdate[strcspn(regdate, "\n")] = 0;
            REGISTER_USER(username, fullname, email, regdate);
            break;

        case 2:
            printf("Username: ");
            fgets(username, 64, stdin);
            username[strcspn(username, "\n")] = 0;
            CHECK_USERNAME(username);
            break;

        case 3:
            printf("Username: ");
            fgets(username, 64, stdin);
            username[strcspn(username, "\n")] = 0;
            printf("New Full Name: ");
            fgets(new_fullname, 128, stdin);
            new_fullname[strcspn(new_fullname, "\n")] = 0;
            printf("New Email: ");
            fgets(new_email, 128, stdin);
            new_email[strcspn(new_email, "\n")] = 0;
            UPDATE_USER(username, new_fullname, new_email);
            break;

        case 4:
            printf("Username: ");
            fgets(username, 64, stdin);
            username[strcspn(username, "\n")] = 0;
            DELETE_USER(username);
            break;

        case 5:
            DISPLAY_USERS();
            break;

        case 6:
            TOTAL_COLLISIONS();
            break;

        case 7:
            LOAD_FACTOR();
            break;

        case 8:
            printf("Number of users (0 = 5000): ");
            fgets(line, sizeof(line), stdin);
            n = atoi(line);
            if (n <= 0)
                n = 5000;
            bulk_seed(n);
            break;

        case 0:
            printf("Goodbye!\n");
            break;

        default:
            printf("Invalid option.\n");
        }
    } while (choice != 0);

    return 0;
}
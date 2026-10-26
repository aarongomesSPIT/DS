#include "platform.c"

int main()
{
    int choice, n;
    char username[64], fullname[128], email[128], regdate[20];
    char new_fullname[128], new_email[128];

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
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Username: ");
            scanf(" %63[^\n]", username);
            printf("Full Name: ");
            scanf(" %127[^\n]", fullname);
            printf("Email: ");
            scanf(" %127[^\n]", email);
            printf("Reg Date: ");
            scanf(" %19[^\n]", regdate);
            REGISTER_USER(username, fullname, email, regdate);
            break;

        case 2:
            printf("Username: ");
            scanf(" %63[^\n]", username);
            CHECK_USERNAME(username);
            break;

        case 3:
            printf("Username: ");
            scanf(" %63[^\n]", username);
            printf("New Full Name: ");
            scanf(" %127[^\n]", new_fullname);
            printf("New Email: ");
            scanf(" %127[^\n]", new_email);
            UPDATE_USER(username, new_fullname, new_email);
            break;

        case 4:
            printf("Username: ");
            scanf(" %63[^\n]", username);
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
            scanf("%d", &n);
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
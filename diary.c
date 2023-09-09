#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Structure to represent a diary entry
struct DiaryEntry {
    char date[20];
    char content[500];
};

// Function to create a new diary entry
void createEntry() {
    struct DiaryEntry newEntry;
    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    strftime(newEntry.date, sizeof(newEntry.date), "%Y-%m-%d.txt", t); // Use date as the filename

    printf("Enter your diary entry (max 500 characters):\n");
    fgets(newEntry.content, sizeof(newEntry.content), stdin);

    FILE *file = fopen(newEntry.date, "w"); // Open a file with the date as the filename
    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }

    fprintf(file, "[%s]\n%s", newEntry.date, newEntry.content);
    fclose(file);

    printf("Entry added successfully!\n");
}

// Function to view all diary entries
void viewEntries() {
    printf("\nDiary Entries:\n");
    struct DiaryEntry entry;
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char currentDate[20];
    strftime(currentDate, sizeof(currentDate), "%Y-%m-%d", t);

    FILE *file;

    for (int i = 1; i <= 31; i++) {
        char date[20];
        snprintf(date, sizeof(date), "%s-%02d.txt", currentDate, i);
        file = fopen(date, "r");
        if (file != NULL) {
            printf("Entries for %s:\n", date);
            while (fgets(entry.content, sizeof(entry.content), file) != NULL) {
                printf("%s", entry.content);
            }
            fclose(file);
        }
    }
}

int main() {
    int choice;

    while (1) {
        printf("\nDiary Management System\n");
        printf("1. Create Entry\n");
        printf("2. View Entries\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        fflush(stdin); // Clear the input buffer

        switch (choice) {
            case 1:
                createEntry();
                break;
            case 2:
                viewEntries();
                break;
            case 3:
                printf("Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}

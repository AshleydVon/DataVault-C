
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    Record record;
    int choice, id;
    char searchTerm[50];
    char sortField[10];

    initDatabase();

    while(1) {
        printf("\n=== Database Management System ===\n");
        printf("1. Add Record\n");
        printf("2. View Record\n");
        printf("3. Update Record\n");
        printf("4. Delete Record\n");
        printf("5. Search Records\n");
        printf("6. Sort Records\n");
        printf("7. Display All Records\n");
        printf("0. Exit\n");
        printf("Choice: ");
        
        scanf("%d", &choice);
        clearInputBuffer();

        switch(choice) {
            case 0:
                printf("Goodbye!\n");
                return 0;

            case 1:
                printf("Enter ID: ");
                scanf("%d", &record.id);
                clearInputBuffer();
                
                printf("Enter Name: ");
                fgets(record.name, 50, stdin);
                record.name[strcspn(record.name, "\n")] = 0;
                
                printf("Enter Age: ");
                scanf("%d", &record.age);
                clearInputBuffer();
                
                printf("Enter Email: ");
                fgets(record.email, 100, stdin);
                record.email[strcspn(record.email, "\n")] = 0;
                
                addRecord(record);
                break;

            case 2:
                printf("Enter ID to view: ");
                scanf("%d", &id);
                record = getRecord(id);
                if(record.id != -1) {
                    printf("ID: %d\nName: %s\nAge: %d\nEmail: %s\n",
                           record.id, record.name, record.age, record.email);
                } else {
                    printf("Record not found!\n");
                }
                break;

            case 3:
                printf("Enter ID to update: ");
                scanf("%d", &id);
                clearInputBuffer();
                
                printf("Enter new Name: ");
                fgets(record.name, 50, stdin);
                record.name[strcspn(record.name, "\n")] = 0;
                
                printf("Enter new Age: ");
                scanf("%d", &record.age);
                clearInputBuffer();
                
                printf("Enter new Email: ");
                fgets(record.email, 100, stdin);
                record.email[strcspn(record.email, "\n")] = 0;
                
                record.id = id;
                updateRecord(id, record);
                break;

            case 4:
                printf("Enter ID to delete: ");
                scanf("%d", &id);
                deleteRecord(id);
                break;

            case 5:
                printf("Enter search term: ");
                fgets(searchTerm, 50, stdin);
                searchTerm[strcspn(searchTerm, "\n")] = 0;
                searchRecords(searchTerm);
                break;

            case 6:
                printf("Sort by (id/name/age/email): ");
                scanf("%s", sortField);
                sortRecords(sortField);
                break;

            case 7:
                displayAllRecords();
                break;

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}

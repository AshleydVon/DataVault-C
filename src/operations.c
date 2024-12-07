
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"

#define MAX_RECORDS 1000
#define DATABASE_FILE "data/records.dat"

// Helper function to check file existence
static int fileExists(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file) {
        fclose(file);
        return 1;
    }
    return 0;
}

void swapRecords(Record *a, Record *b) {
    Record temp = *a;
    *a = *b;
    *b = temp;
}

void searchRecords(char* searchTerm) {
    if (!fileExists(DATABASE_FILE)) {
        printf("Error: Database file does not exist\n");
        return;
    }

    Record record;
    FILE *file = fopen(DATABASE_FILE, "rb");
    if (file == NULL) {
        printf("Error: Cannot open database file\n");
        return;
    }
    
    int found = 0;
    while(fread(&record, sizeof(Record), 1, file)) {
        if(strstr(record.name, searchTerm) || 
           strstr(record.email, searchTerm) || 
           (atoi(searchTerm) == record.id) || 
           (atoi(searchTerm) == record.age)) {
            printf("Found: ID=%d, Name=%s, Age=%d, Email=%s\n", 
                   record.id, record.name, record.age, record.email);
            found = 1;
        }
    }
    
    if (!found) {
        printf("No matching records found.\n");
    }
    fclose(file);
}

void sortRecords(char* field) {
    if (!fileExists(DATABASE_FILE)) {
        printf("Error: Database file does not exist\n");
        return;
    }

    // Validate sort field
    if (strcmp(field, "id") != 0 && 
        strcmp(field, "name") != 0 && 
        strcmp(field, "age") != 0 && 
        strcmp(field, "email") != 0) {
        printf("Error: Invalid sort field. Use: id, name, age, or email\n");
        return;
    }

    // Allocate memory for records
    Record* records = (Record*)malloc(MAX_RECORDS * sizeof(Record));
    if (records == NULL) {
        printf("Error: Memory allocation failed\n");
        return;
    }

    FILE *file = fopen(DATABASE_FILE, "rb");
    if (file == NULL) {
        printf("Error: Cannot open database file\n");
        free(records);
        return;
    }

    int recordCount = 0;
    while(recordCount < MAX_RECORDS && 
          fread(&records[recordCount], sizeof(Record), 1, file) == 1) {
        recordCount++;
    }
    fclose(file);

    if (recordCount == 0) {
        printf("No records to sort.\n");
        free(records);
        return;
    }

    // Bubble sort with progress indicator
    printf("Sorting records...\n");
    for(int i = 0; i < recordCount-1; i++) {
        for(int j = 0; j < recordCount-i-1; j++) {
            int shouldSwap = 0;
            
            if(strcmp(field, "id") == 0) {
                shouldSwap = records[j].id > records[j+1].id;
            }
            else if(strcmp(field, "name") == 0) {
                shouldSwap = strcmp(records[j].name, records[j+1].name) > 0;
            }
            else if(strcmp(field, "age") == 0) {
                shouldSwap = records[j].age > records[j+1].age;
            }
            else if(strcmp(field, "email") == 0) {
                shouldSwap = strcmp(records[j].email, records[j+1].email) > 0;
            }
            
            if(shouldSwap) {
                swapRecords(&records[j], &records[j+1]);
            }
        }
        if (i % 10 == 0) {
            printf("Progress: %d%%\r", (i * 100) / (recordCount-1));
            fflush(stdout);
        }
    }

    // Write sorted records back to file
    file = fopen(DATABASE_FILE, "wb");
    if (file == NULL) {
        printf("Error: Cannot open database file for writing\n");
        free(records);
        return;
    }

    size_t written = fwrite(records, sizeof(Record), recordCount, file);
    if (written != recordCount) {
        printf("Error: Failed to write all records\n");
    } else {
        printf("\nRecords sorted successfully by %s\n", field);
    }

    fclose(file);
    free(records);
    displayAllRecords();
}

void displayAllRecords() {
    if (!fileExists(DATABASE_FILE)) {
        printf("Error: Database file does not exist\n");
        return;
    }

    Record record;
    FILE *file = fopen(DATABASE_FILE, "rb");
    if (file == NULL) {
        printf("Error: Cannot open database file\n");
        return;
    }

    printf("\n=== All Records ===\n");
    int count = 0;
    while(fread(&record, sizeof(Record), 1, file)) {
        printf("Record #%d:\n", count + 1);
        printf("  ID: %d\n  Name: %s\n  Age: %d\n  Email: %s\n", 
               record.id, record.name, record.age, record.email);
        printf("---------------\n");
        count++;
    }
    
    if (count == 0) {
        printf("No records found in database.\n");
    } else {
        printf("Total records: %d\n", count);
    }
    
    fclose(file);
}

int recordExists(int id) {
    if (!fileExists(DATABASE_FILE)) return 0;

    Record record;
    FILE *file = fopen(DATABASE_FILE, "rb");
    if (file == NULL) return 0;

    while(fread(&record, sizeof(Record), 1, file)) {
        if(record.id == id) {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

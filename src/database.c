
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"

#define DATABASE_FILE "data/records.dat"

void initDatabase() {
    FILE *file = fopen(DATABASE_FILE, "ab+");
    if (file == NULL) {
        printf("Error: Cannot open database file\n");
        exit(1);
    }
    fclose(file);
}

void addRecord(Record record) {
    if (recordExists(record.id)) {
        printf("Error: ID already exists\n");
        return;
    }

    FILE *file = fopen(DATABASE_FILE, "ab");
    if (file == NULL) {
        printf("Error: Cannot open database file\n");
        return;
    }
    fwrite(&record, sizeof(Record), 1, file);
    fclose(file);
    printf("Record added successfully!\n");
}

Record getRecord(int id) {
    Record record;
    FILE *file = fopen(DATABASE_FILE, "rb");
    if (file == NULL) {
        printf("Error: Cannot open database file\n");
        record.id = -1;
        return record;
    }
    
    while(fread(&record, sizeof(Record), 1, file)) {
        if(record.id == id) {
            fclose(file);
            return record;
        }
    }
    fclose(file);
    record.id = -1;
    return record;
}

void updateRecord(int id, Record newData) {
    FILE *file = fopen(DATABASE_FILE, "rb+");
    if (file == NULL) {
        printf("Error: Cannot open database file\n");
        return;
    }

    Record record;
    int found = 0;
    while(fread(&record, sizeof(Record), 1, file)) {
        if(record.id == id) {
            fseek(file, -sizeof(Record), SEEK_CUR);
            fwrite(&newData, sizeof(Record), 1, file);
            found = 1;
            break;
        }
    }
    fclose(file);
    
    if(found) printf("Record updated successfully!\n");
    else printf("Record not found!\n");
}

void deleteRecord(int id) {
    FILE *file = fopen(DATABASE_FILE, "rb");
    FILE *temp = fopen("data/temp.dat", "wb");
    
    if (file == NULL || temp == NULL) {
        printf("Error: Cannot open files\n");
        return;
    }

    Record record;
    int found = 0;
    while(fread(&record, sizeof(Record), 1, file)) {
        if(record.id != id) {
            fwrite(&record, sizeof(Record), 1, temp);
        } else {
            found = 1;
        }
    }
    
    fclose(file);
    fclose(temp);
    
    remove(DATABASE_FILE);
    rename("data/temp.dat", DATABASE_FILE);
    
    if(found) printf("Record deleted successfully!\n");
    else printf("Record not found!\n");
}

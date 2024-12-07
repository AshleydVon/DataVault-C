
#ifndef DATABASE_H
#define DATABASE_H

typedef struct {
    int id;
    char name[50];
    int age;
    char email[100];
} Record;

void initDatabase();
void addRecord(Record record);
Record getRecord(int id);
void updateRecord(int id, Record newData);
void deleteRecord(int id);
void searchRecords(char* searchTerm);
void sortRecords(char* field);
void displayAllRecords();
int recordExists(int id);

#endif

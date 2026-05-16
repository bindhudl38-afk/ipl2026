#include <stdio.h>
#include <stdlib.h>

struct Student {
    int id;
    char name[50];
    float marks;
};

// Function to write records to file
void writeRecords(const char *filename, int n) {
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    struct Student s;

    for (int i = 0; i < n; i++) {
        printf("\nEnter details for student %d\n", i + 1);
        printf("ID: ");
        scanf("%d", &s.id);
        printf("Name: ");
        scanf("%s", s.name);
        printf("Marks: ");
        scanf("%f", &s.marks);

        fwrite(&s, sizeof(struct Student), 1, fp);
    }

    fclose(fp);
}

// Function to read m-th record using fseek
void readRecord(const char *filename, int m) {
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    struct Student s;

    // Move to (m-1)th position
    fseek(fp, (m - 1) * sizeof(struct Student), SEEK_SET);

    if (fread(&s, sizeof(struct Student), 1, fp) == 1) {
        printf("\nRecord %d:\n", m);
        printf("ID: %d\nName: %s\nMarks: %.2f\n", s.id, s.name, s.marks);
    } else {
        printf("Record not found!\n");
    }

    fclose(fp);
}

// Function to delete a record
void deleteRecord(const char *filename, int del_id) {
    FILE *fp = fopen(filename, "rb");
    FILE *temp = fopen("temp.dat", "wb");

    if (fp == NULL || temp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    struct Student s;
    int found = 0;

    while (fread(&s, sizeof(struct Student), 1, fp)) {
        if (s.id != del_id) {
            fwrite(&s, sizeof(struct Student), 1, temp);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    if (found) {
        remove(filename);
        rename("temp.dat", filename);
        printf("Record deleted successfully.\n");
    } else {
        remove("temp.dat");
        printf("Record not found.\n");
    }
}

// Function to display all records
void displayAll(const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    struct Student s;
    printf("\nAll Records:\n");

    while (fread(&s, sizeof(struct Student), 1, fp)) {
        printf("ID: %d | Name: %s | Marks: %.2f\n", s.id, s.name, s.marks);
    }

    fclose(fp);
}

// Main function
int main() {
    int n, m, choice, del_id;
    char filename[] = "students.dat";

    printf("Enter number of records: ");
    scanf("%d", &n);

    writeRecords(filename, n);

    do {
        printf("\n--- MENU ---\n");
        printf("1. Display all records\n");
        printf("2. Read m-th record\n");
        printf("3. Delete a record\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayAll(filename);
                break;

            case 2:
                printf("Enter record number (m): ");
                scanf("%d", &m);
                readRecord(filename, m);
                break;

            case 3:
                printf("Enter ID to delete: ");
                scanf("%d", &del_id);
                deleteRecord(filename, del_id);
                break;

            case 4:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while (choice != 4);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Structure
struct student {
    int id;
    char name[50];
    float marks;
};

// Function to write records in ASCII file
void writeRecords(struct student s[], int n) {
    FILE *fp = fopen("data.txt", "w");
    if (fp == NULL) {
        printf("File error\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        fprintf(fp, "%d %s %f\n", s[i].id, s[i].name, s[i].marks);
    }

    fclose(fp);
}

// Function to store seek positions
int createIndex(long pos[], int max) {
    FILE *fp = fopen("data.txt", "r");
    if (fp == NULL) {
        printf("File error\n");
        return 0;
    }

    int count = 0;

    while (!feof(fp) && count < max) {
        pos[count] = ftell(fp);  // store position

        int id;
        char name[50];
        float marks;

        if (fscanf(fp, "%d %s %f", &id, name, &marks) != 3)
            break;

        count++;
    }

    fclose(fp);
    return count;
}

// Function to display record using position
void displayRecord(long position) {
    FILE *fp = fopen("data.txt", "r");
    if (fp == NULL) {
        printf("File error\n");
        return;
    }

    fseek(fp, position, SEEK_SET);

    struct student s;

    fscanf(fp, "%d %s %f", &s.id, s.name, &s.marks);

    printf("\nRecord:\n");
    printf("ID: %d\nName: %s\nMarks: %.2f\n", s.id, s.name, s.marks);

    fclose(fp);
}

// Main
int main() {
    struct student s[MAX];
    long pos[MAX];
    int n;

    printf("Enter number of records: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("\nEnter details for student %d\n", i + 1);
        printf("ID: ");
        scanf("%d", &s[i].id);
        printf("Name: ");
        scanf("%s", s[i].name);
        printf("Marks: ");
        scanf("%f", &s[i].marks);
    }

    writeRecords(s, n);

    int count = createIndex(pos, MAX);

    printf("\nStored positions:\n");
    for (int i = 0; i < count; i++) {
        printf("Record %d position: %ld\n", i + 1, pos[i]);
    }

    int choice;
    printf("\nEnter record number to display: ");
    scanf("%d", &choice);

    if (choice >= 1 && choice <= count) {
        displayRecord(pos[choice - 1]);
    } else {
        printf("Invalid choice\n");
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>

/* Structure */
struct Student {
    int id;
    char name[50];
    float marks;
};

/* Function declarations */
void writeRecords(struct Student s[], int n, FILE *fp);
void createIndex(FILE *fp, long pos[], int n);
void displayRecord(FILE *fp, long pos[], int index);

int main() {
    int n, i, choice;
    struct Student s[100];
    long pos[100];

    FILE *fp = fopen("students.txt", "w+");

    if (fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    printf("Enter number of records: ");
    scanf("%d", &n);

    /* Input data */
    for (i = 0; i < n; i++) {
        printf("\nEnter details for student %d\n", i + 1);
        printf("ID: ");
        scanf("%d", &s[i].id);
        printf("Name: ");
        scanf("%s", s[i].name);
        printf("Marks: ");
        scanf("%f", &s[i].marks);
    }

    /* Write to file */
    writeRecords(s, n, fp);

    /* Create index positions */
    createIndex(fp, pos, n);

    /* Display specific record */
    printf("\nEnter record number to display (1 to %d): ", n);
    scanf("%d", &choice);

    if (choice >= 1 && choice <= n)
        displayRecord(fp, pos, choice - 1);
    else
        printf("Invalid choice\n");

    fclose(fp);
    return 0;
}

/* Write records in ASCII format */
void writeRecords(struct Student s[], int n, FILE *fp) {
    int i;

    rewind(fp);

    for (i = 0; i < n; i++) {
        fprintf(fp, "%d %s %f\n", s[i].id, s[i].name, s[i].marks);
    }
}

/* Create array of positions */
void createIndex(FILE *fp, long pos[], int n) {
    int i = 0;
    struct Student temp;

    rewind(fp);

    while (!feof(fp) && i < n) {
        pos[i] = ftell(fp);  // store position

        if (fscanf(fp, "%d %s %f",
                   &temp.id, temp.name, &temp.marks) != 3)
            break;

        i++;
    }
}

/* Display record using position */
void displayRecord(FILE *fp, long pos[], int index) {
    struct Student s;

    fseek(fp, pos[index], SEEK_SET);

    fscanf(fp, "%d %s %f", &s.id, s.name, &s.marks);

    printf("\nRecord Found:\n");
    printf("ID: %d\n", s.id);
    printf("Name: %s\n", s.name);
    printf("Marks: %.2f\n", s.marks);
}
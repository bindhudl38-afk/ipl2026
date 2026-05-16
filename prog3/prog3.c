#include <stdio.h>

// Print bits
void printBits(int n) {
    for (int i = sizeof(int)*8 - 1; i >= 0; i--) {
        printf("%d", (n >> i) & 1);
    }
    printf("\n");
}

// Count 1s
int countOnes(int n) {
    int count = 0;
    while (n) {
        n = n & (n - 1);
        count++;
    }
    return count;
}

// Set bit
int setBit(int n, int pos) {
    return n | (1 << pos);
}

// Clear bit
int clearBit(int n, int pos) {
    return n & ~(1 << pos);
}

// Toggle bit
int toggleBit(int n, int pos) {
    return n ^ (1 << pos);
}

// Check bit
int checkBit(int n, int pos) {
    return (n >> pos) & 1;
}

// Check Endianness
void checkEndian() {
    int x = 1;
    char *c = (char*)&x;

    if (*c == 1)
        printf("Little Endian\n");
    else
        printf("Big Endian\n");
}

int main() {
    int choice, n, pos;

    while (1) {
        printf("\n===== BIT OPERATIONS MENU =====\n");
        printf("1. Print Bits\n");
        printf("2. Count 1 Bits\n");
        printf("3. Set Bit\n");
        printf("4. Clear Bit\n");
        printf("5. Toggle Bit\n");
        printf("6. Check Bit\n");
        printf("7. Left Shift\n");
        printf("8. Right Shift\n");
        printf("9. Check Endianness\n");
        printf("0. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 0) break;

        if (choice >= 1 && choice <= 8) {
            printf("Enter number: ");
            scanf("%d", &n);
        }

        switch (choice) {
            case 1:
                printBits(n);
                break;

            case 2:
                printf("Number of 1s = %d\n", countOnes(n));
                break;

            case 3:
                printf("Enter bit position: ");
                scanf("%d", &pos);
                n = setBit(n, pos);
                printf("Result = %d\n", n);
                printBits(n);
                break;

            case 4:
                printf("Enter bit position: ");
                scanf("%d", &pos);
                n = clearBit(n, pos);
                printf("Result = %d\n", n);
                printBits(n);
                break;

            case 5:
                printf("Enter bit position: ");
                scanf("%d", &pos);
                n = toggleBit(n, pos);
                printf("Result = %d\n", n);
                printBits(n);
                break;

            case 6:
                printf("Enter bit position: ");
                scanf("%d", &pos);
                printf("Bit = %d\n", checkBit(n, pos));
                break;

            case 7:
                printf("Enter shift value: ");
                scanf("%d", &pos);
                n = n << pos;
                printf("Result = %d\n", n);
                printBits(n);
                break;

            case 8:
                printf("Enter shift value: ");
                scanf("%d", &pos);
                n = n >> pos;
                printf("Result = %d\n", n);
                printBits(n);
                break;

            case 9:
                checkEndian();
                break;

            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}
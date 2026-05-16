#include <stdio.h>

typedef unsigned char decision;  // 8-bit container

// Set bit
void setBit(decision *d, int pos) {
    *d |= (1 << pos);
}

// Clear bit
void clearBit(decision *d, int pos) {
    *d &= ~(1 << pos);
}

// Get bit
int getBit(decision d, int pos) {
    return (d >> pos) & 1;
}

// Input
decision input() {
    decision d = 0;
    int temp;

    printf("Enter (0/1):\n");

    printf("Your choice: ");
    scanf("%d", &temp);
    if (temp) setBit(&d, 0);

    printf("Mother's choice: ");
    scanf("%d", &temp);
    if (temp) setBit(&d, 1);

    printf("Father's choice: ");
    scanf("%d", &temp);
    if (temp) setBit(&d, 2);

    printf("Socially acceptable: ");
    scanf("%d", &temp);
    if (temp) setBit(&d, 3);

    printf("Financially viable: ");
    scanf("%d", &temp);
    if (temp) setBit(&d, 4);

    printf("Aptitude: ");
    scanf("%d", &temp);
    if (temp) setBit(&d, 5);

    printf("Do you like it: ");
    scanf("%d", &temp);
    if (temp) setBit(&d, 6);

    return d;
}

// Decision logic
void make_decision(decision *d) {
    int your = getBit(*d, 0);
    int mother = getBit(*d, 1);
    int father = getBit(*d, 2);
    int social = getBit(*d, 3);
    int money = getBit(*d, 4);
    int aptitude = getBit(*d, 5);
    int like = getBit(*d, 6);

    int result =
        (your && like && aptitude && money) ||
        (mother && father && social);

    if (result)
        setBit(d, 7);
    else
        clearBit(d, 7);
}

// Print narrative
void print_decision(decision d) {
    printf("\n--- Decision Analysis ---\n");

    if (getBit(d, 7))
        printf("Decision: GO AHEAD ✅\n");
    else
        printf("Decision: NOT RECOMMENDED ❌\n");

    printf("Flags value = %u\n", d);
}

// Interpret flags
void print_conclusion(decision d) {
    if (d == 255)
        printf("Perfect case 🔥\n");
    else if (d > 200)
        printf("Very strong case 👍\n");
    else if (d > 100)
        printf("Mixed situation 🤔\n");
    else
        printf("Weak case ⚠️\n");
}
   int main() {
    decision d = input();

    make_decision(&d);

    print_decision(d);

    print_conclusion(d);

    return 0;
}
#include <stdio.h>

// Define bitfield structure
struct Bitfield {
    unsigned int firstbit  : 1;  // 1 bit
    unsigned int secondbit : 2;  // 2 bits
    unsigned int thirdbit  : 3;  // 3 bits
};

int main() {
    struct Bitfield a;

    // Assign values
    a.firstbit = 1;   // valid: 0 or 1
    a.secondbit = 3;  // max for 2 bits = 3
    a.thirdbit = 5;   // max for 3 bits = 7

    // Display values
    printf("firstbit  = %u\n", a.firstbit);
    printf("secondbit = %u\n", a.secondbit);
    printf("thirdbit  = %u\n", a.thirdbit);

    return 0;
}
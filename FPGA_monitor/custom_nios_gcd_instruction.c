#include <stdint.h>
#include <stdio.h>

//define custom instruction for compiler
#define GCD_CI(input1, input2) __builtin_custom_inii(0, (input1), (input2))

//timer avalon memory interface
volatile uint32_t * const TIMER_CONT = (uint32_t *) 0xFF202004;
volatile uint32_t * const TIMER_START_VAL = (uint32_t *) 0xFF202008;
volatile uint32_t * const TIMER_SNAPSHOT = (uint32_t *) 0xFF202010;

//write to avalon memory interface to start timer
void start_timer() {
    *TIMER_CONT = 0x00000008;
    *TIMER_START_VAL = 0xFFFFFFFF;
    *TIMER_CONT = 0x00000004;
}

//read from avalon memory interface to get and print the time
void get_and_print_time() {
    //tell the timer module to take a snapshot
    *TIMER_SNAPSHOT = 0x00000000;
    //calculate and print cycles
    printf("Cycles to calculate result: %u\n", 0x0000FFFF - *TIMER_SNAPSHOT);
}

uint32_t get_GCF_32(uint32_t a, uint32_t b) {
    // Swap if B > A
    if (a < b) {
        uint32_t temp = a;
        a = b;
        b = temp;
    }

    // Euclid's subtraction algorithm
    while (a != b) {
        if (a > b) {
            a = a - b;
        } else {
            b = b - a;
        }
    }
    return a;
}

uint32_t get_hw_GCF_32(uint32_t a, uint32_t b) {
    return GCD_CI(a,b);
}

int main() {
    uint32_t REG_A;
    uint32_t REG_B;

    while(1) {
        //ask for user input 32 bit values
        printf("Enter an unsigned 32 bit number for reg A: ");
        scanf("%u", &REG_A);
        printf("Enter an unsigned 32 bit number for reg B: ");
        scanf("%u", &REG_B);

        //calculate result in software
        printf("\nBegin software gcd:\n");
        uint32_t GCF = get_GCF_32(REG_A, REG_B);
        printf("GCD = %u\n\n", GCF);

        //calculate result in hardware
        printf("\nBegin hardware gcd:\n");
        GCF = get_hw_GCF_32(REG_A, REG_B);
        printf("GCD = %u\n\n", GCF);
           
    }
    return 0;
}

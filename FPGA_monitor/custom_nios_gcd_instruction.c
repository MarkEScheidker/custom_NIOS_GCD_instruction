#include <stdint.h>
#include <stdio.h>

//define custom instruction for compiler
#define GCD_CI(input1, input2) __builtin_custom_inii(0, (input1), (input2))

//timer avalon memory interface
volatile uint16_t * const TIMER_CONT = (uint32_t *) 0xFF202004;
volatile uint16_t * const TIMER_START_VAL_LO = (uint32_t *) 0xFF202008;
volatile uint16_t * const TIMER_START_VAL_HI = (uint32_t *) 0xFF20200C;
volatile uint16_t * const TIMER_SNAPSHOT_LO = (uint32_t *) 0xFF202010;
volatile uint16_t * const TIMER_SNAPSHOT_HI = (uint32_t *) 0xFF202014;

//write to avalon memory interface to start timer
void start_timer() {
    *TIMER_CONT = 0x00000008;
    *TIMER_START_VAL_LO = 0xFFFF;
    *TIMER_START_VAL_HI = 0xFFFF;
    *TIMER_CONT = 0x00000004;
}

//read from avalon memory interface to get and print the time
uint32_t get_time() {
    //tell the timer module to take a snapshot
    *TIMER_SNAPSHOT_LO = 0x0000;
    *TIMER_START_VAL_HI = 0x0000;

    //calculate and return cycles
    return 0xFFFFFFFF - (((uint32_t) *TIMER_SNAPSHOT_LO) + ((uint32_t)(*TIMER_SNAPSHOT_HI << 16)));
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
    uint32_t elapsed_time;

    while(1) {
        //ask for user input 32 bit values
        printf("Enter an unsigned 32 bit number for reg A: ");
        scanf("%u", &REG_A);
        printf("Enter an unsigned 32 bit number for reg B: ");
        scanf("%u", &REG_B);

        //calculate result in software
        printf("\nBegin software gcd:\n");
        start_timer();
        uint32_t GCF = get_GCF_32(REG_A, REG_B);
        elapsed_time = get_time();
        printf("GCD = %u\n", GCF);
        printf("Time: %u Cycles\n\n", elapsed_time);

        //calculate result in hardware
        printf("\nBegin hardware gcd:\n");
        start_timer();
        GCF = get_hw_GCF_32(REG_A, REG_B);
        elapsed_time = get_time();
        printf("GCD = %u\n\n", GCF);
        printf("Time: %u Cycles\n\n", elapsed_time);
           
    }
    return 0;
}

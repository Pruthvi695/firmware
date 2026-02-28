#include <stdio.h>
#include <stdint.h>

volatile uint8_t HARDWARE_REGISTER = 0x00;

int main() {
    printf("Initial register value: 0x%02X\n", HARDWARE_REGISTER);
    
    HARDWARE_REGISTER = 0xFF;
    printf("After writing 0xFF: 0x%02X\n", HARDWARE_REGISTER);
    
    uint8_t value = HARDWARE_REGISTER;
    printf("Read value: 0x%02X\n", value);
    
    if (HARDWARE_REGISTER & (1 << 7)) {
        printf("Bit 7 is SET\n");
    }
    
    return 0;
}
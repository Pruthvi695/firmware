#include <stdio.h>
#include <stdint.h>

int main() {
    uint8_t register_value = 0b10101010;
    
    printf("Initial value: 0x%02X\n", register_value);
    
    register_value |= (1 << 0);
    printf("After SET bit 0: 0x%02X\n", register_value);
    
    register_value &= ~(1 << 1);
    printf("After CLEAR bit 1: 0x%02X\n", register_value);
    
    register_value ^= (1 << 7);
    printf("After TOGGLE bit 7: 0x%02X\n", register_value);
    
    return 0;
}
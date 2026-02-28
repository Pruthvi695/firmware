#include <stdio.h>

#define SET_BIT(reg, bit) ((reg) |= (1 << (bit)))
#define CLEAR_BIT(reg, bit) ((reg) &= ~(1 << (bit)))
#define CHECK_BIT(reg, bit) (((reg) >> (bit)) & 1)
#define TOGGLE_BIT(reg, bit) ((reg) ^= (1 << (bit)))

int main() {
    unsigned char register_value = 0x00;
    
    SET_BIT(register_value, 3);
    printf("After SET_BIT(3): 0x%02X\n", register_value);
    
    if (CHECK_BIT(register_value, 3)) {
        printf("Bit 3 is SET\n");
    }
    
    CLEAR_BIT(register_value, 3);
    printf("After CLEAR_BIT(3): 0x%02X\n", register_value);
    
    TOGGLE_BIT(register_value, 5);
    printf("After TOGGLE_BIT(5): 0x%02X\n", register_value);
    
    return 0;
}
#include <stdio.h>
#include <stdint.h>

struct UART_Registers {
    volatile uint8_t data_register;
    volatile uint8_t control_register;
    volatile uint8_t status_register;
};

int main() {
    struct UART_Registers uart;
    
    uart.data_register = 0x41;
    uart.control_register = 0x80;
    uart.status_register = 0x10;
    
    printf("UART Register Block:\n");
    printf("Data Register: 0x%02X\n", uart.data_register);
    printf("Control Register: 0x%02X\n", uart.control_register);
    printf("Status Register: 0x%02X\n", uart.status_register);
    
    printf("\nThis struct MODELS a real hardware device!\n");
    printf("In real firmware, this maps to actual memory addresses.\n");
    
    return 0;
}
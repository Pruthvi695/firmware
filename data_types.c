#include <stdio.h>
#include <stdint.h>

int main() {
    uint8_t pin_number = 13;
    uint16_t voltage_mv = 5000;
    int32_t temperature = -20;
    
    printf("Pin Number: %u\n", pin_number);
    printf("Voltage: %u mV\n", voltage_mv);
    printf("Temperature: %d°C\n", temperature);
    
    return 0;
}
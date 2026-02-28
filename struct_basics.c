#include <stdio.h>
#include <stdint.h>

struct GPIO_Pin {
    uint8_t pin_number;
    uint8_t pin_state;
    char* pin_name;
};

int main() {
    struct GPIO_Pin led;
    led.pin_number = 13;
    led.pin_state = 1;
    led.pin_name = "LED";
    
    printf("Pin: %s\n", led.pin_name);
    printf("Number: %u\n", led.pin_number);
    printf("State: %u\n", led.pin_state);
    
    struct GPIO_Pin button;
    button.pin_number = 2;
    button.pin_state = 0;
    button.pin_name = "BUTTON";
    
    printf("\nPin: %s\n", button.pin_name);
    printf("Number: %u\n", button.pin_number);
    printf("State: %u\n", button.pin_state);
    
    return 0;
}
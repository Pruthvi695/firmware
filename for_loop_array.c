#include <stdio.h>

int main() {
    int gpio_pins[8] = {2, 3, 4, 5, 6, 7, 8, 9};
    
    printf("Looping through GPIO pins:\n");
    for (int i = 0; i < 8; i++) {
        printf("Pin %d: GPIO %d\n", i, gpio_pins[i]);
    }
    
    printf("\nLooping backwards:\n");
    for (int i = 7; i >= 0; i--) {
        printf("Pin %d: GPIO %d\n", i, gpio_pins[i]);
    }
    
    return 0;
}
#include <stdio.h>

int main() {
    printf("=== While Loops ===\n\n");
    
    // Simple while loop
    printf("Test 1: Simple Counter\n");
    int i = 0;
    while (i < 5) {
        printf("i = %d\n", i);
        i++;
    }
    
    // While loop with condition
    printf("\nTest 2: Countdown\n");
    int countdown = 5;
    while (countdown > 0) {
        printf("Countdown: %d\n", countdown);
        countdown--;
    }
    printf("Blastoff!\n");
    
    // While loop with break
    printf("\nTest 3: Loop with Break\n");
    int button_press = 0;
    while (1) {  // Infinite loop
        printf("Waiting for button press... (%d)\n", button_press);
        button_press++;
        if (button_press == 3) {
            printf("Button pressed! Breaking out of loop.\n");
            break;
        }
    }
    
    // While loop with continue
    printf("\nTest 4: Loop with Continue\n");
    int j = 0;
    while (j < 7) {
        j++;
        if (j == 3 || j == 5) {
            continue;  // Skip to next iteration
        }
        printf("j = %d\n", j);
    }
    
    // Real-world example: LED blinking simulation
    printf("\nTest 5: LED Binking (Simulated)\n");
    int blink_count = 0;
    int max_blinks = 4;
    int led_state = 0;  // 0 = OFF, 1 = ON
    
    while (blink_count < max_blinks) {
        led_state = !led_state;  // Toggle LED
        printf("LED is %s\n", led_state ? "ON" : "OFF");
        blink_count++;
    }
    
    return 0;
}

#include <stdio.h>

typedef void (*callback_t)(int);

void on_button_pressed(int pin) {
    printf("Button on pin %d was pressed!\n", pin);
}

void on_led_toggled(int pin) {
    printf("LED on pin %d was toggled!\n", pin);
}

void trigger_event(callback_t callback, int pin) {
    printf("Triggering event...\n");
    callback(pin);
}

int main() {
    callback_t my_callback = on_button_pressed;
    
    trigger_event(my_callback, 13);
    
    my_callback = on_led_toggled;
    trigger_event(my_callback, 12);
    
    return 0;
}
#include <stdio.h>

void increment_counter() {
    static int counter = 0;
    counter++;
    printf("Counter: %d\n", counter);
}

int main() {
    printf("Calling increment_counter 5 times:\n");
    increment_counter();  // Output: Counter: 1
    increment_counter();  // Output: Counter: 2
    increment_counter();  // Output: Counter: 3
    increment_counter();  // Output: Counter: 4
    increment_counter();  // Output: Counter: 5
    
    printf("\nStatic variable PERSISTS between calls!\n");
    return 0;
}
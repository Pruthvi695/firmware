#include <stdio.h>

int main() {
    printf("=== IF-ELSE Basics ===\n\n");
    
    int age = 25;
    if (age >= 18) {
        printf("You are an adult (age: %d)\n", age);
    } else {
        printf("You are a minor\n");
    }
    
    int temperature = 35;
    if (temperature > 30) {
        printf("It's hot! Temperature: %d°C\n", temperature);
    } else if (temperature > 20) {
        printf("It's warm. Temperature: %d°C\n", temperature);
    } else if (temperature > 10) {
        printf("It's cool. Temperature: %d°C\n", temperature);
    } else {
        printf("It's cold! Temperature: %d°C\n", temperature);
    }
    
    int x = 15, y = 20;
    if (x > 10) {
        if (y > 15) {
            printf("Both x and y are greater than their thresholds\n");
        } else {
            printf("x is > 10, but y is <= 15\n");
        }
    } else {
        printf("x is <= 10\n");
    }
    
    return 0;
}
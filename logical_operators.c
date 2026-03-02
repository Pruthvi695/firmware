#include <stdio.h>

int main() {
    printf("=== Logical Operators ===\n\n");
    
    int a = 10;
    int b = 20;
    int c = 30;
    
    // AND operator (&&)
    printf("AND Operator (&&):\n");
    if (a < b && b < c) {
        printf("a < b AND b < c is TRUE\n");
    }
    
    if (a > b && b < c) {
        printf("a > b AND b < c is TRUE\n");
    } else {
        printf("a > b AND b < c is FALSE\n");
    }
    
    // OR operator (||)
    printf("\nOR Operator (||):\n");
    if (a < b || a > c) {
        printf("a < b OR a > c is TRUE\n");
    }
    
    if (a > 50 || b > 50) {
        printf("a > 50 OR b > 50 is TRUE\n");
    } else {
        printf("a > 50 OR b > 50 is FALSE\n");
    }
    
    // NOT operator (!)
    printf("\nNOT Operator (!):\n");
    int is_running = 1;
    
    if (!is_running) {
        printf("System is stopped\n");
    } else {
        printf("System is running\n");
    }
    
    // Complex logical expressions
    printf("\nComplex Expressions:\n");
    int voltage = 5;
    int current = 2;
    int temperature = 45;
    
    if ((voltage >= 4 && voltage <= 6) && (current < 3) && (temperature < 50)) {
        printf("Device parameters are SAFE\n");
    } else {
        printf("Device parameters are OUT OF RANGE\n");
    }
    
    return 0;
}


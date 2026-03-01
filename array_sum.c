#include <stdio.h>

int main() {
    int sensor_data[10] = {50, 55, 60, 65, 70, 75, 80, 85, 90, 95};
    int sum = 0;
    int average = 0;
    
    printf("Sensor Data Array:\n");
    for (int i = 0; i < 10; i++) {
        printf("Index %d: %d\n", i, sensor_data[i]);
        sum += sensor_data[i];
    }
    
    average = sum / 10;
    
    printf("\nSum of all sensors: %d\n", sum);
    printf("Average reading: %d\n", average);
    
    return 0;
}
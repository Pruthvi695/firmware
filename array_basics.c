 #include <stdio.h>

int main() {
    int sensor_readings[6];
    
    sensor_readings[0] = 100;
    sensor_readings[1] = 105;
    sensor_readings[2] = 98;
    sensor_readings[3] = 102;
    sensor_readings[4] = 99;
    sensor_readings[5] = 108;
    
    printf("Sensor Readings:\n");
    printf("Sensor 0: %d\n", sensor_readings[0]);
    printf("Sensor 1: %d\n", sensor_readings[1]);
    printf("Sensor 2: %d\n", sensor_readings[2]);
    printf("Sensor 3: %d\n", sensor_readings[3]);
    printf("Sensor 4: %d\n", sensor_readings[4]);
    printf("Sensor 5: %d\n", sensor_readings[5]);

    return 0;
}
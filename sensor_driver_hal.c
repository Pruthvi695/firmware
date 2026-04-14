#include <stdio.h>
#include <string.h>
#include "FreeRTOS.h"
#include "task.h"

// ============================================
// SENSOR DRIVER ABSTRACTION LAYER
// ============================================

// Sensor Configuration
typedef struct {
    int sensor_id;
    int interface_type;  // 0=I2C, 1=SPI
    float temperature;
} Sensor_Config_t;

// HAL: Initialize sensor (application doesn't care how!)
void Sensor_Init(Sensor_Config_t *config) {
    printf("[SENSOR HAL] Initializing Sensor ID %d\n", config->sensor_id);
    
    if(config->interface_type == 0) {
        printf("[SENSOR HAL] Using I2C interface\n");
        printf("[SENSOR HAL] Setting I2C address, registers, etc.\n");
    } else {
        printf("[SENSOR HAL] Using SPI interface\n");
        printf("[SENSOR HAL] Setting SPI clock, CS pin, etc.\n");
    }
    
    printf("[SENSOR HAL] Sensor initialized successfully\n\n");
}

// HAL: Read sensor value (application doesn't care about protocol!)
float Sensor_Read(Sensor_Config_t *config) {
    // Simulate reading from sensor
    config->temperature += 0.5f;  // Simulate temperature change
    
    printf("[SENSOR HAL] Reading from Sensor ID %d...\n", config->sensor_id);
    
    if(config->interface_type == 0) {
        printf("[SENSOR HAL] I2C: Read register 0xF7, 0xF8, 0xF9\n");
        printf("[SENSOR HAL] Bytes received: 3\n");
    } else {
        printf("[SENSOR HAL] SPI: Transmitted 8-bit commands\n");
        printf("[SENSOR HAL] Bytes received: 4\n");
    }
    
    printf("[SENSOR HAL] Temperature value: %.2f°C\n\n", config->temperature);
    
    return config->temperature;
}

// ============================================
// APPLICATION CODE (USES SENSOR DRIVER ONLY)
// ============================================

void vTemperatureMonitorTask(void *pvParameters) {
    printf("=== Temperature Monitor Application ===\n");
    printf("Application doesn't care about I2C or SPI!\n\n");
    
    // Create sensor configurations
    Sensor_Config_t sensor1;
    sensor1.sensor_id = 1;
    sensor1.interface_type = 0;  // I2C
    sensor1.temperature = 20.0f;
    
    Sensor_Config_t sensor2;
    sensor2.sensor_id = 2;
    sensor2.interface_type = 1;  // SPI
    sensor2.temperature = 22.0f;
    
    // Initialize sensors using HAL
    printf("[APP] Initializing temperature sensors...\n\n");
    Sensor_Init(&sensor1);
    Sensor_Init(&sensor2);
    
    int reading_count = 1;
    
    while(1) {
        printf("=== Reading Cycle %d ===\n", reading_count);
        
        // Application reads sensors - doesn't care about protocol!
        printf("[APP] Reading Sensor 1 (I2C)\n");
        float temp1 = Sensor_Read(&sensor1);
        
        printf("[APP] Reading Sensor 2 (SPI)\n");
        float temp2 = Sensor_Read(&sensor2);
        
        // Application logic
        printf("[APP] Temperature Average: %.2f°C\n", (temp1 + temp2) / 2.0f);
        
        if(temp1 > 30.0f || temp2 > 30.0f) {
            printf("[APP] WARNING: Temperature exceeds 30°C!\n");
        }
        
        printf("[APP] All systems OK\n\n");
        
        reading_count++;
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

int main(void) {
    printf("=== Sensor Driver with HAL Abstraction ===\n");
    printf("HAL abstracts the communication protocol\n");
    printf("Application uses same interface for I2C or SPI!\n\n");
    
    xTaskCreate(vTemperatureMonitorTask,  // Task function
                "Temp Monitor",          // Task name
                configMINIMAL_STACK_SIZE,  // Stack size
                NULL,                    // Parameter
                2,                       // Priority
                NULL);
    
    vTaskStartScheduler();
    
    return 0;
}
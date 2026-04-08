#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"

// Sensor reading task
void vSensorTask(void *pvParameters) {
    int sensor_id = (int)pvParameters;
    
    while(1) {
        printf("[SENSOR %d] Reading temperature from sensor...\n", sensor_id);
        vTaskDelay(pdMS_TO_TICKS(1500));  // 1.5 second read time
        
        printf("[SENSOR %d] Temperature = 25°C\n", sensor_id);
        vTaskDelay(pdMS_TO_TICKS(2000));  // 2 second wait before next read
    }
}

// Controller task
void vControlTask(void *pvParameters) {
    while(1) {
        printf("    [CONTROLLER] Checking all sensors...\n");
        vTaskDelay(pdMS_TO_TICKS(2000));  // 2 second check interval
        
        printf("    [CONTROLLER] All systems OK\n");
        vTaskDelay(pdMS_TO_TICKS(1500));  // 1.5 second delay
    }
}

int main(void) {
    printf("=== Real-World Example: Sensor + Controller ===\n\n");
    
    // Create SENSOR task (higher priority)
    xTaskCreate(vSensorTask,            // Task function
                "Sensor Task 1",        // Task name
                configMINIMAL_STACK_SIZE,  // Stack size
                (void*)1,               // Parameter (Sensor ID)
                2,                      // Priority (HIGH)
                NULL);                  // Task handle
    
    // Create CONTROLLER task (lower priority)
    xTaskCreate(vControlTask,           // Task function
                "Controller Task",      // Task name
                configMINIMAL_STACK_SIZE,  // Stack size
                NULL,                   // Parameter
                1,                      // Priority (LOW)
                NULL);                  // Task handle
    
    // Start scheduler
    vTaskStartScheduler();
    
    return 0;
}
#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"

// High priority task
void vHighPriorityTask(void *pvParameters) {
    while(1) {
        printf(">>> HIGH PRIORITY task is running\n");
        vTaskDelay(pdMS_TO_TICKS(2000));  // 2 second delay
    }
}

// Low priority task
void vLowPriorityTask(void *pvParameters) {
    while(1) {
        printf("    Low priority task is running\n");
        vTaskDelay(pdMS_TO_TICKS(3000));  // 3 second delay
    }
}

int main(void) {
    printf("=== FreeRTOS Task Priority Demo ===\n\n");
    printf("High priority = 2, Low priority = 1\n");
    printf("Highest priority runs first!\n\n");
    
    // Create HIGH priority task
    xTaskCreate(vHighPriorityTask,   // Task function
                "High Priority",    // Task name
                configMINIMAL_STACK_SIZE,  // Stack size
                NULL,               // Parameter
                2,                  // Priority (HIGHER = 2)
                NULL);              // Task handle
    
    // Create LOW priority task
    xTaskCreate(vLowPriorityTask,    // Task function
                "Low Priority",     // Task name
                configMINIMAL_STACK_SIZE,  // Stack size
                NULL,               // Parameter
                1,                  // Priority (LOWER = 1)
                NULL);              // Task handle
    
    // Start scheduler
    vTaskStartScheduler();
    
    return 0;
}
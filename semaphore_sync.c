#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

// Semaphore handle (global)
SemaphoreHandle_t xBinarySemaphore = NULL;

// Task that waits for semaphore
void vWaitTask(void *pvParameters) {
    while(1) {
        printf("[WAIT TASK] Waiting for semaphore...\n");
        
        // Wait (take) semaphore
        if(xSemaphoreTake(xBinarySemaphore, pdMS_TO_TICKS(10000))) {
            printf("[WAIT TASK] Semaphore received! Proceeding...\n");
            
            // Do some work
            printf("[WAIT TASK] Processing...\n");
            vTaskDelay(pdMS_TO_TICKS(1000));
            
            printf("[WAIT TASK] Work complete!\n");
        } else {
            printf("[WAIT TASK] Timeout waiting for semaphore\n");
        }
        
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

// Task that signals semaphore
void vSignalTask(void *pvParameters) {
    int count = 0;
    
    while(1) {
        vTaskDelay(pdMS_TO_TICKS(3000));
        
        count++;
        printf("    [SIGNAL TASK] Giving semaphore (count: %d)\n", count);
        
        // Give (signal) semaphore
        xSemaphoreGive(xBinarySemaphore);
    }
}

int main(void) {
    printf("=== FreeRTOS Semaphore: Task Synchronization ===\n\n");
    printf("Wait Task waits for Signal Task to give semaphore\n\n");
    
    // Create binary semaphore (0 initial state = locked)
    xBinarySemaphore = xSemaphoreCreateBinary();
    
    if(xBinarySemaphore == NULL) {
        printf("Failed to create semaphore\n");
        return 1;
    }
    
    // Create wait task (higher priority - will run first)
    xTaskCreate(vWaitTask,              // Task function
                "Wait Task",            // Task name
                configMINIMAL_STACK_SIZE,  // Stack size
                NULL,                   // Parameter
                2,                      // Priority (HIGH)
                NULL);
    
    // Create signal task (lower priority)
    xTaskCreate(vSignalTask,            // Task function
                "Signal Task",          // Task name
                configMINIMAL_STACK_SIZE,  // Stack size
                NULL,                   // Parameter
                1,                      // Priority (LOW)
                NULL);
    
    vTaskStartScheduler();
    
    return 0;
}
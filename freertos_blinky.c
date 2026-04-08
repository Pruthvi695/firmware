#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"

// LED blinking task function
void vLedTask(void *pvParameters) {
    int led_pin = (int)pvParameters;
    
    while(1) {
        printf("LED %d is ON\n", led_pin);
        vTaskDelay(pdMS_TO_TICKS(1000));  // 1 second delay
        
        printf("LED %d is OFF\n", led_pin);
        vTaskDelay(pdMS_TO_TICKS(1000));  // 1 second delay
    }
}

int main(void) {
    printf("=== FreeRTOS LED Blinking Demo ===\n\n");
    
    // Create first LED task (pin 13)
    xTaskCreate(vLedTask,           // Task function
                "LED Task 1",       // Task name
                configMINIMAL_STACK_SIZE,  // Stack size
                (void*)13,          // Parameter (LED pin)
                1,                  // Priority
                NULL);              // Task handle
    
    // Create second LED task (pin 12)
    xTaskCreate(vLedTask,           // Task function
                "LED Task 2",       // Task name
                configMINIMAL_STACK_SIZE,  // Stack size
                (void*)12,          // Parameter (LED pin)
                1,                  // Priority
                NULL);              // Task handle
    
    // Start the scheduler - tasks will run from here
    vTaskStartScheduler();
    
    // Should never reach here
    return 0;
}
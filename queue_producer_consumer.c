#include <stdio.h>
#include <string.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

// Queue handle (global)
QueueHandle_t xQueue = NULL;

// Data structure to send through queue
typedef struct {
    int sensor_id;
    float temperature;
} SensorData_t;

// Producer task - generates data
void vProducerTask(void *pvParameters) {
    SensorData_t sensorData;
    int sensor_id = (int)pvParameters;
    
    while(1) {
        // Simulate reading sensor
        sensorData.sensor_id = sensor_id;
        sensorData.temperature = 20.0f + (sensor_id * 2);  // Simulated temp
        
        printf("[PRODUCER %d] Sending temp: %.1f°C\n", 
               sensorData.sensor_id, sensorData.temperature);
        
        // Send data to queue
        xQueueSend(xQueue, &sensorData, pdMS_TO_TICKS(1000));
        
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

// Consumer task - receives data
void vConsumerTask(void *pvParameters) {
    SensorData_t receivedData;
    
    while(1) {
        // Wait for data from queue
        if(xQueueReceive(xQueue, &receivedData, pdMS_TO_TICKS(5000))) {
            printf("    [CONSUMER] Received: Sensor %d = %.1f°C\n", 
                   receivedData.sensor_id, receivedData.temperature);
            
            // Simulate processing
            if(receivedData.temperature > 30.0f) {
                printf("    [CONSUMER] WARNING: Temperature too high!\n");
            }
        } else {
            printf("    [CONSUMER] No data received (timeout)\n");
        }
    }
}

int main(void) {
    printf("=== FreeRTOS Queue: Producer/Consumer Pattern ===\n\n");
    
    // Create queue (size=10, item=SensorData_t)
    xQueue = xQueueCreate(10, sizeof(SensorData_t));
    
    if(xQueue == NULL) {
        printf("Failed to create queue\n");
        return 1;
    }
    
    // Create producer task
    xTaskCreate(vProducerTask,          // Task function
                "Producer",             // Task name
                configMINIMAL_STACK_SIZE,  // Stack size
                (void*)1,               // Parameter (Sensor ID)
                2,                      // Priority
                NULL);
    
    // Create consumer task
    xTaskCreate(vConsumerTask,          // Task function
                "Consumer",             // Task name
                configMINIMAL_STACK_SIZE,  // Stack size
                NULL,                   // Parameter
                1,                      // Priority
                NULL);
    
    vTaskStartScheduler();
    
    return 0;
}
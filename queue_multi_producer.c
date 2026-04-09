#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

// Queue handle (global)
QueueHandle_t xDataQueue = NULL;

// Data structure
typedef struct {
    int producer_id;
    int data_value;
} DataPacket_t;

// Producer 1 task
void vProducer1Task(void *pvParameters) {
    DataPacket_t packet;
    int counter = 0;
    
    while(1) {
        packet.producer_id = 1;
        packet.data_value = 100 + counter;
        
        printf("[PRODUCER 1] Sending: %d\n", packet.data_value);
        xQueueSend(xDataQueue, &packet, pdMS_TO_TICKS(1000));
        
        counter++;
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

// Producer 2 task
void vProducer2Task(void *pvParameters) {
    DataPacket_t packet;
    int counter = 0;
    
    while(1) {
        packet.producer_id = 2;
        packet.data_value = 200 + counter;
        
        printf("[PRODUCER 2] Sending: %d\n", packet.data_value);
        xQueueSend(xDataQueue, &packet, pdMS_TO_TICKS(1000));
        
        counter++;
        vTaskDelay(pdMS_TO_TICKS(2500));
    }
}

// Consumer task - receives from both producers
void vConsumerTask(void *pvParameters) {
    DataPacket_t receivedPacket;
    
    while(1) {
        if(xQueueReceive(xDataQueue, &receivedPacket, pdMS_TO_TICKS(5000))) {
            printf("    [CONSUMER] Received from Producer %d: %d\n", 
                   receivedPacket.producer_id, receivedPacket.data_value);
            
            // Simulate processing
            vTaskDelay(pdMS_TO_TICKS(500));
        } else {
            printf("    [CONSUMER] No data (queue empty)\n");
        }
    }
}

int main(void) {
    printf("=== FreeRTOS Queue: Multiple Producers, One Consumer ===\n\n");
    printf("2 Producers send data to shared queue\n");
    printf("1 Consumer receives from both\n\n");
    
    // Create queue (size=20)
    xDataQueue = xQueueCreate(20, sizeof(DataPacket_t));
    
    if(xDataQueue == NULL) {
        printf("Failed to create queue\n");
        return 1;
    }
    
    // Create Producer 1
    xTaskCreate(vProducer1Task,         // Task function
                "Producer 1",           // Task name
                configMINIMAL_STACK_SIZE,  // Stack size
                NULL,                   // Parameter
                2,                      // Priority
                NULL);
    
    // Create Producer 2
    xTaskCreate(vProducer2Task,         // Task function
                "Producer 2",           // Task name
                configMINIMAL_STACK_SIZE,  // Stack size
                NULL,                   // Parameter
                2,                      // Priority
                NULL);
    
    // Create Consumer
    xTaskCreate(vConsumerTask,          // Task function
                "Consumer",             // Task name
                configMINIMAL_STACK_SIZE,  // Stack size
                NULL,                   // Parameter
                1,                      // Priority
                NULL);
    
    vTaskStartScheduler();
    
    return 0;
}
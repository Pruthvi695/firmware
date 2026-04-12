#include <stdio.h>
#include <string.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

// UART Queue for data transmission
QueueHandle_t xUARTQueue = NULL;

// Data structure for UART packets
typedef struct {
    char data[50];
    int length;
} UARTPacket_t;

// UART Transmitter Task - sends data via UART
void vUARTTxTask(void *pvParameters) {
    UARTPacket_t packet;
    int message_count = 1;
    
    while(1) {
        // Create UART message
        sprintf(packet.data, "UART Message #%d: Hello from Firmware!", message_count);
        packet.length = strlen(packet.data);
        
        printf("[UART TX] Transmitting: %s\n", packet.data);
        printf("[UART TX] Length: %d bytes\n", packet.length);
        
        // Send to UART Queue
        xQueueSend(xUARTQueue, &packet, pdMS_TO_TICKS(1000));
        
        message_count++;
        vTaskDelay(pdMS_TO_TICKS(3000));  // Send every 3 seconds
    }
}

// UART Receiver Task - receives data from UART
void vUARTRxTask(void *pvParameters) {
    UARTPacket_t receivedPacket;
    int bytes_received = 0;
    
    while(1) {
        // Wait for data from UART Queue
        if(xQueueReceive(xUARTQueue, &receivedPacket, pdMS_TO_TICKS(5000))) {
            printf("    [UART RX] Received: %s\n", receivedPacket.data);
            printf("    [UART RX] Bytes: %d\n", receivedPacket.length);
            
            bytes_received += receivedPacket.length;
            printf("    [UART RX] Total bytes received: %d\n\n", bytes_received);
            
            // Simulate processing delay
            vTaskDelay(pdMS_TO_TICKS(500));
        } else {
            printf("    [UART RX] Waiting for UART data...\n");
        }
    }
}

int main(void) {
    printf("=== UART Communication with FreeRTOS ===\n");
    printf("TX Task sends messages via UART Queue\n");
    printf("RX Task receives and processes messages\n\n");
    
    // Create UART Queue
    xUARTQueue = xQueueCreate(10, sizeof(UARTPacket_t));
    
    if(xUARTQueue == NULL) {
        printf("Failed to create UART queue\n");
        return 1;
    }
    
    // Create UART TX Task
    xTaskCreate(vUARTTxTask,            // Task function
                "UART TX",              // Task name
                configMINIMAL_STACK_SIZE,  // Stack size
                NULL,                   // Parameter
                2,                      // Priority (HIGH)
                NULL);
    
    // Create UART RX Task
    xTaskCreate(vUARTRxTask,            // Task function
                "UART RX",              // Task name
                configMINIMAL_STACK_SIZE,  // Stack size
                NULL,                   // Parameter
                1,                      // Priority (LOW)
                NULL);
    
    vTaskStartScheduler();
    
    return 0;
}
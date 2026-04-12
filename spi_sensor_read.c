#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

// SPI Data Queue
QueueHandle_t xSPIDataQueue = NULL;

// SPI Data Packet
typedef struct {
    int sensor_id;
    float sensor_value;
    int byte_count;
} SPIData_t;

// SPI Master Task - reads from SPI slave
void vSPIMasterTask(void *pvParameters) {
    SPIData_t spiData;
    int reading = 0;
    
    while(1) {
        printf("[SPI MASTER] Initiating SPI transfer...\n");
        printf("[SPI MASTER] SCK (Clock): Active\n");
        printf("[SPI MASTER] CS (Chip Select): LOW\n");
        
        // Simulate SPI clock transmission (8 bits)
        printf("[SPI MASTER] Shifting 8 bits on MOSI/MISO lines\n");
        vTaskDelay(pdMS_TO_TICKS(100));
        
        // Simulate reading sensor value via SPI
        spiData.sensor_id = 1;
        spiData.sensor_value = 25.5f + (reading * 0.5f);
        spiData.byte_count = 2;  // SPI typically uses 2-4 bytes
        
        printf("[SPI MASTER] Data received: %.1f (2 bytes)\n", spiData.sensor_value);
        printf("[SPI MASTER] CS (Chip Select): HIGH\n\n");
        
        // Send SPI data to queue
        xQueueSend(xSPIDataQueue, &spiData, pdMS_TO_TICKS(1000));
        
        reading++;
        vTaskDelay(pdMS_TO_TICKS(2000));  // SPI read every 2 seconds
    }
}

// SPI Slave Task - simulates SPI slave device responding
void vSPISlaveTask(void *pvParameters) {
    SPIData_t spiData;
    int total_reads = 0;
    
    while(1) {
        if(xQueueReceive(xSPIDataQueue, &spiData, pdMS_TO_TICKS(5000))) {
            printf("    [SPI SLAVE] CS asserted - communication started\n");
            printf("    [SPI SLAVE] Received from Master: %.1f\n", spiData.sensor_value);
            printf("    [SPI SLAVE] Sensor ID: %d, Bytes transferred: %d\n", 
                   spiData.sensor_id, spiData.byte_count);
            
            total_reads++;
            printf("    [SPI SLAVE] Total SPI transactions: %d\n\n", total_reads);
            
            // Simulate SPI slave response processing
            vTaskDelay(pdMS_TO_TICKS(500));
        } else {
            printf("    [SPI SLAVE] Waiting for SPI master...\n");
        }
    }
}

int main(void) {
    printf("=== SPI Communication Protocol ===\n");
    printf("SPI = Synchronous Peripheral Interface\n");
    printf("Wires: SCK (Clock), MOSI (Master Out), MISO (Master In), CS (Chip Select)\n");
    printf("Master controls clock - Slave synchronizes to it\n\n");
    
    // Create SPI Queue
    xSPIDataQueue = xQueueCreate(10, sizeof(SPIData_t));
    
    if(xSPIDataQueue == NULL) {
        printf("Failed to create SPI queue\n");
        return 1;
    }
    
    // Create SPI Master Task
    xTaskCreate(vSPIMasterTask,         // Task function
                "SPI Master",           // Task name
                configMINIMAL_STACK_SIZE,  // Stack size
                NULL,                   // Parameter
                2,                      // Priority (HIGH)
                NULL);
    
    // Create SPI Slave Task
    xTaskCreate(vSPISlaveTask,          // Task function
                "SPI Slave",            // Task name
                configMINIMAL_STACK_SIZE,  // Stack size
                NULL,                   // Parameter
                1,                      // Priority (LOW)
                NULL);
    
    vTaskStartScheduler();
    
    return 0;
}
#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

// I2C Data Queue
QueueHandle_t xI2CQueue = NULL;

// I2C Sensor Data
typedef struct {
    int device_address;  // I2C device address (7-bit)
    int register_addr;   // Register to read
    float sensor_reading;
    char sensor_name[30];
} I2CData_t;

// I2C Master Task - reads from multiple I2C slaves on same bus
void vI2CMasterTask(void *pvParameters) {
    I2CData_t i2cData;
    int device_count = 0;
    
    while(1) {
        printf("[I2C MASTER] Starting I2C transaction...\n");
        printf("[I2C MASTER] SDA/SCL lines: Active\n");
        
        // I2C Addresses and sensor names
        struct {
            int address;
            char name[30];
            float value;
        } sensors[] = {
            {0x68, "Accelerometer (MPU6050)", 9.8f},
            {0x77, "Barometer (BMP280)", 1013.25f},
            {0x5A, "Humidity (DHT22)", 65.5f}
        };
        
        int sensor_index = device_count % 3;
        
        i2cData.device_address = sensors[sensor_index].address;
        i2cData.register_addr = 0x3B + sensor_index;  // Different registers
        i2cData.sensor_reading = sensors[sensor_index].value + (device_count * 0.1f);
        sprintf(i2cData.sensor_name, "%s", sensors[sensor_index].name);
        
        printf("[I2C MASTER] Device Address: 0x%02X (%s)\n", 
               i2cData.device_address, i2cData.sensor_name);
        printf("[I2C MASTER] Register: 0x%02X\n", i2cData.register_addr);
        printf("[I2C MASTER] Value: %.2f\n", i2cData.sensor_reading);
        printf("[I2C MASTER] Data transferred: 1-2 bytes\n\n");
        
        // Send I2C data to queue
        xQueueSend(xI2CQueue, &i2cData, pdMS_TO_TICKS(1000));
        
        device_count++;
        vTaskDelay(pdMS_TO_TICKS(2000));  // Poll every 2 seconds
    }
}

// I2C Slave Task - processes data from multiple devices
void vI2CSlaveTask(void *pvParameters) {
    I2CData_t i2cData;
    int total_transactions = 0;
    
    while(1) {
        if(xQueueReceive(xI2CQueue, &i2cData, pdMS_TO_TICKS(5000))) {
            printf("    [I2C SLAVE] Device 0x%02X ACK received\n", i2cData.device_address);
            printf("    [I2C SLAVE] Sensor: %s\n", i2cData.sensor_name);
            printf("    [I2C SLAVE] Register 0x%02X = %.2f\n", 
                   i2cData.register_addr, i2cData.sensor_reading);
            
            total_transactions++;
            printf("    [I2C SLAVE] Total I2C transactions: %d\n", total_transactions);
            
            // Simulate acknowledgment (ACK bit on SDA)
            printf("    [I2C SLAVE] Sending ACK bit on SDA line\n");
            printf("    [I2C SLAVE] Data validation: OK\n\n");
            
            vTaskDelay(pdMS_TO_TICKS(500));
        } else {
            printf("    [I2C SLAVE] Waiting for I2C master transaction...\n");
        }
    }
}

int main(void) {
    printf("=== I2C (TWI) Communication Protocol ===\n");
    printf("I2C = Inter-Integrated Circuit (Two-Wire Interface)\n");
    printf("Wires: SDA (Data), SCL (Clock) with pull-up resistors\n");
    printf("Multi-device on same 2-wire bus - each device has unique 7-bit address\n\n");
    printf("Connected Devices:\n");
    printf("  0x68 = Accelerometer (MPU6050)\n");
    printf("  0x77 = Barometer (BMP280)\n");
    printf("  0x5A = Humidity Sensor (DHT22)\n\n");
    
    // Create I2C Queue
    xI2CQueue = xQueueCreate(10, sizeof(I2CData_t));
    
    if(xI2CQueue == NULL) {
        printf("Failed to create I2C queue\n");
        return 1;
    }
    
    // Create I2C Master Task
    xTaskCreate(vI2CMasterTask,         // Task function
                "I2C Master",           // Task name
                configMINIMAL_STACK_SIZE,  // Stack size
                NULL,                   // Parameter
                2,                      // Priority (HIGH)
                NULL);
    
    // Create I2C Slave Task
    xTaskCreate(vI2CSlaveTask,          // Task function
                "I2C Slave",            // Task name
                configMINIMAL_STACK_SIZE,  // Stack size
                NULL,                   // Parameter
                1,                      // Priority (LOW)
                NULL);
    
    vTaskStartScheduler();
    
    return 0;
}
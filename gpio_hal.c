#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"

// ============================================
// HARDWARE ABSTRACTION LAYER (HAL) FOR GPIO
// ============================================

// GPIO Port definition
typedef enum {
    GPIO_PORT_A = 0,
    GPIO_PORT_B = 1,
    GPIO_PORT_C = 2
} GPIO_Port_t;

// GPIO Pin definition
typedef enum {
    GPIO_PIN_0 = 0,
    GPIO_PIN_1 = 1,
    GPIO_PIN_2 = 2,
    GPIO_PIN_3 = 3,
    GPIO_PIN_4 = 4,
    GPIO_PIN_5 = 5
} GPIO_Pin_t;

// GPIO Mode definition
typedef enum {
    GPIO_MODE_INPUT = 0,
    GPIO_MODE_OUTPUT = 1
} GPIO_Mode_t;

// Simple GPIO register simulation
typedef struct {
    unsigned int data;      // Pin data (0 or 1)
    unsigned int direction; // 0=input, 1=output
} GPIO_Register_t;

// Simulate GPIO ports
GPIO_Register_t GPIO_PortA[6] = {0};
GPIO_Register_t GPIO_PortB[6] = {0};
GPIO_Register_t GPIO_PortC[6] = {0};

// HAL Function: Initialize GPIO pin
void GPIO_Init(GPIO_Port_t port, GPIO_Pin_t pin, GPIO_Mode_t mode) {
    printf("[HAL] GPIO_Init(Port=%d, Pin=%d, Mode=%s)\n", 
           port, pin, mode == GPIO_MODE_OUTPUT ? "OUTPUT" : "INPUT");
    
    // Simulate hardware initialization
    if(port == GPIO_PORT_A) {
        GPIO_PortA[pin].direction = mode;
        GPIO_PortA[pin].data = 0;
    } else if(port == GPIO_PORT_B) {
        GPIO_PortB[pin].direction = mode;
        GPIO_PortB[pin].data = 0;
    } else if(port == GPIO_PORT_C) {
        GPIO_PortC[pin].direction = mode;
        GPIO_PortC[pin].data = 0;
    }
}

// HAL Function: Set GPIO pin HIGH
void GPIO_Set(GPIO_Port_t port, GPIO_Pin_t pin) {
    printf("[HAL] GPIO_Set(Port=%d, Pin=%d) -> HIGH\n", port, pin);
    
    if(port == GPIO_PORT_A) {
        GPIO_PortA[pin].data = 1;
    } else if(port == GPIO_PORT_B) {
        GPIO_PortB[pin].data = 1;
    } else if(port == GPIO_PORT_C) {
        GPIO_PortC[pin].data = 1;
    }
}

// HAL Function: Clear GPIO pin LOW
void GPIO_Clear(GPIO_Port_t port, GPIO_Pin_t pin) {
    printf("[HAL] GPIO_Clear(Port=%d, Pin=%d) -> LOW\n", port, pin);
    
    if(port == GPIO_PORT_A) {
        GPIO_PortA[pin].data = 0;
    } else if(port == GPIO_PORT_B) {
        GPIO_PortB[pin].data = 0;
    } else if(port == GPIO_PORT_C) {
        GPIO_PortC[pin].data = 0;
    }
}

// HAL Function: Read GPIO pin
int GPIO_Read(GPIO_Port_t port, GPIO_Pin_t pin) {
    int value = 0;
    
    if(port == GPIO_PORT_A) {
        value = GPIO_PortA[pin].data;
    } else if(port == GPIO_PORT_B) {
        value = GPIO_PortB[pin].data;
    } else if(port == GPIO_PORT_C) {
        value = GPIO_PortC[pin].data;
    }
    
    printf("[HAL] GPIO_Read(Port=%d, Pin=%d) = %d\n", port, pin, value);
    return value;
}

// ============================================
// APPLICATION CODE (USES HAL ONLY)
// ============================================

void vLEDTask(void *pvParameters) {
    printf("\n[APP] LED Control Task Starting...\n");
    printf("[APP] Initializing GPIO Port B Pin 3 as OUTPUT\n\n");
    
    // Application uses HAL - doesn't care about hardware details!
    GPIO_Init(GPIO_PORT_B, GPIO_PIN_3, GPIO_MODE_OUTPUT);
    
    int iteration = 1;
    
    while(1) {
        printf("=== LED Blink Iteration %d ===\n", iteration);
        
        // Turn LED ON
        printf("[APP] Turning LED ON\n");
        GPIO_Set(GPIO_PORT_B, GPIO_PIN_3);
        printf("[APP] LED State: %d\n", GPIO_Read(GPIO_PORT_B, GPIO_PIN_3));
        vTaskDelay(pdMS_TO_TICKS(1000));
        
        // Turn LED OFF
        printf("[APP] Turning LED OFF\n");
        GPIO_Clear(GPIO_PORT_B, GPIO_PIN_3);
        printf("[APP] LED State: %d\n\n", GPIO_Read(GPIO_PORT_B, GPIO_PIN_3));
        vTaskDelay(pdMS_TO_TICKS(1000));
        
        iteration++;
    }
}

void vButtonTask(void *pvParameters) {
    printf("[APP] Button Input Task Starting...\n");
    printf("[APP] Initializing GPIO Port A Pin 0 as INPUT\n\n");
    
    // Initialize button as input
    GPIO_Init(GPIO_PORT_A, GPIO_PIN_0, GPIO_MODE_INPUT);
    
    while(1) {
        printf("[APP] Checking button...\n");
        int button_state = GPIO_Read(GPIO_PORT_A, GPIO_PIN_0);
        printf("[APP] Button = %s\n\n", button_state ? "PRESSED" : "RELEASED");
        
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

int main(void) {
    printf("=== GPIO Hardware Abstraction Layer (HAL) ===\n");
    printf("Application uses generic GPIO functions\n");
    printf("Hardware-specific code hidden in HAL\n");
    printf("Same app code works on any microcontroller!\n\n");
    
    // Create LED control task
    xTaskCreate(vLEDTask,               // Task function
                "LED Task",             // Task name
                configMINIMAL_STACK_SIZE,  // Stack size
                NULL,                   // Parameter
                2,                      // Priority
                NULL);
    
    // Create button input task
    xTaskCreate(vButtonTask,            // Task function
                "Button Task",          // Task name
                configMINIMAL_STACK_SIZE,  // Stack size
                NULL,                   // Parameter
                1,                      // Priority
                NULL);
    
    vTaskStartScheduler();
    
    return 0;
}
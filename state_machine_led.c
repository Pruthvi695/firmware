#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"

// ============================================
// STATE MACHINE FOR LED CONTROL
// ============================================

// LED States
typedef enum {
    LED_STATE_OFF = 0,
    LED_STATE_BLINKING = 1,
    LED_STATE_ON = 2
} LED_State_t;

// Events that trigger state transitions
typedef enum {
    EVENT_BUTTON_PRESSED = 0,
    EVENT_TIMEOUT = 1,
    EVENT_NONE = 2
} LED_Event_t;

// Current state
LED_State_t current_state = LED_STATE_OFF;
int blink_count = 0;

// State machine: Process event and transition to new state
void LED_StateTransition(LED_Event_t event) {
    printf("[STATE MACHINE] Current State: ");
    
    switch(current_state) {
        case LED_STATE_OFF:
            printf("OFF ");
            if(event == EVENT_BUTTON_PRESSED) {
                printf("-> EVENT_BUTTON_PRESSED -> Transition to BLINKING\n");
                current_state = LED_STATE_BLINKING;
                blink_count = 0;
            } else {
                printf("-> No transition\n");
            }
            break;
            
        case LED_STATE_BLINKING:
            printf("BLINKING ");
            if(event == EVENT_TIMEOUT) {
                blink_count++;
                if(blink_count >= 5) {
                    printf("-> EVENT_TIMEOUT (5 blinks done) -> Transition to ON\n");
                    current_state = LED_STATE_ON;
                } else {
                    printf("-> EVENT_TIMEOUT (blink %d) -> Stay in BLINKING\n", blink_count);
                }
            } else if(event == EVENT_BUTTON_PRESSED) {
                printf("-> EVENT_BUTTON_PRESSED -> Transition to OFF\n");
                current_state = LED_STATE_OFF;
            }
            break;
            
        case LED_STATE_ON:
            printf("ON ");
            if(event == EVENT_BUTTON_PRESSED) {
                printf("-> EVENT_BUTTON_PRESSED -> Transition to OFF\n");
                current_state = LED_STATE_OFF;
            } else {
                printf("-> No transition\n");
            }
            break;
    }
}

// Execute state (what to do in this state)
void LED_StateExecute(void) {
    printf("[STATE EXECUTE] ");
    
    switch(current_state) {
        case LED_STATE_OFF:
            printf("LED is OFF (dark)\n");
            break;
            
        case LED_STATE_BLINKING:
            printf("LED is BLINKING (on/off rapidly)\n");
            break;
            
        case LED_STATE_ON:
            printf("LED is ON (bright)\n");
            break;
    }
}

// LED State Machine Task
void vLEDStateMachineTask(void *pvParameters) {
    printf("=== LED State Machine Started ===\n");
    printf("States: OFF -> BLINKING -> ON\n");
    printf("Transitions on BUTTON_PRESSED and TIMEOUT events\n\n");
    
    int event_counter = 0;
    
    while(1) {
        // Execute current state
        LED_StateExecute();
        
        // Simulate events
        if(event_counter < 3) {
            // Press button initially
            printf("[EVENT] Button pressed!\n");
            LED_StateTransition(EVENT_BUTTON_PRESSED);
            event_counter++;
        } else if(event_counter < 8) {
            // Timeout events during blinking
            printf("[EVENT] Timeout occurred!\n");
            LED_StateTransition(EVENT_TIMEOUT);
            event_counter++;
        } else if(event_counter == 8) {
            // Press button to turn off
            printf("[EVENT] Button pressed again!\n");
            LED_StateTransition(EVENT_BUTTON_PRESSED);
            event_counter++;
        } else {
            // Restart cycle
            event_counter = 0;
        }
        
        printf("\n");
        vTaskDelay(pdMS_TO_TICKS(1500));
    }
}

int main(void) {
    printf("=== LED Control with State Machine Pattern ===\n");
    printf("State machines organize complex firmware behavior\n");
    printf("Each state has: Entry actions, Exit actions, Transitions\n\n");
    
    xTaskCreate(vLEDStateMachineTask,   // Task function
                "LED SM Task",          // Task name
                configMINIMAL_STACK_SIZE,  // Stack size
                NULL,                   // Parameter
                2,                      // Priority
                NULL);
    
    vTaskStartScheduler();
    
    return 0;
}
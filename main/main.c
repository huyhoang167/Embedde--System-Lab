#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "driver/gpio.h"
#include "freertos/timers.h"

#define PERIOD_TIMER1 2000
#define PERIOD_TIMER2 3000

#define TIMER1_MAX_TIME 10
#define TIMER2_MAX_TIME 5

int counter_timer1 = 0;
int counter_timer2 = 0;

void Timer_Callback(TimerHandle_t xTimer){
    if (counter_timer1 > TIMER1_MAX_TIME || counter_timer2 > TIMER2_MAX_TIME){
        xTimerStop(xTimer,0);
    }
    if (pvTimerGetTimerID(xTimer) == (void *)1){
        printf("ahihi. At %ds\n", (counter_timer1 + 1) * (PERIOD_TIMER1/1000));
        counter_timer1++;
         if (counter_timer1 == TIMER1_MAX_TIME){
            printf("Stop Timer1\n");
            xTimerStop(xTimer,0);
        }
    }
    else{
        
        printf("ihaha. At %ds\n", (counter_timer2 + 1) * (PERIOD_TIMER2/1000));
        counter_timer2++;
        if (counter_timer2 == TIMER2_MAX_TIME){
            printf("Stop Timer2\n");
            xTimerStop(xTimer,0);
        }
    }
}

void app_main(void)
{ 
    TimerHandle_t Timer1_Handle = xTimerCreate("Timer1", (PERIOD_TIMER1/ portTICK_PERIOD_MS) , pdTRUE, (void *)1, Timer_Callback);
    TimerHandle_t Timer2_Handle = xTimerCreate("Timer2", (PERIOD_TIMER2/ portTICK_PERIOD_MS) , pdTRUE, (void *)2, Timer_Callback);
    xTimerStart(Timer1_Handle,0);
    xTimerStart(Timer2_Handle,0);
}

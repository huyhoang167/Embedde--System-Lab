#include <stdio.h>
#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "driver/gpio.h"
#include "esp_timer.h"
#include "sdkconfig.h"
#include <string.h>

#define QUEUE_LENGTH 10

struct Queue_data{
    int request_ID;
    char msg[30];
    int request_Reject_counter;
};

struct Task_data{
    int Task_ID;
    char Task_Name[30];
};

struct Task_data Task1 = {.Task_Name = "Task 1", .Task_ID = 0};
struct Task_data Task2 = {.Task_Name = "Task 2", .Task_ID = 1};
struct Task_data Task3 = {.Task_Name = "Task 3", .Task_ID = 2};

QueueHandle_t xQueue;

void Queue_Controller(void * pvParameter){
    xQueue = xQueueCreate(QUEUE_LENGTH,sizeof(struct Queue_data));
    if (xQueue == NULL){
        printf("[Error] Failed to create the queue\n");
    }
    vTaskDelete(NULL);
} 

void Send_request(void * pvParameter){
    while(1){
        while(xQueue == NULL){};
        int request_ID = rand()%4;
        int Ran_delay = rand()%5 + 1;
        struct Queue_data * Request_data = malloc(sizeof(struct Queue_data));
        if (Request_data != NULL){
            switch(request_ID){
                case 0:
                    Request_data->request_ID = 0;
                    strcpy(Request_data->msg,"Task 1");
                    Request_data->request_Reject_counter = 0;
                    break;
                case 1:
                    Request_data->request_ID = 1;
                    strcpy(Request_data->msg,"Task 2");
                    Request_data->request_Reject_counter = 0;
                    break;
                case 2:
                    Request_data->request_ID = 2;
                    strcpy(Request_data->msg,"Task 3");
                    Request_data->request_Reject_counter = 0;
                    break;
                case 3:
                    Request_data->request_ID = 88;
                    strcpy(Request_data->msg,"Stranger");
                    Request_data->request_Reject_counter = 0;
                    break;
                default:
                    break;
            }
            if (xQueueSend(xQueue,(void *) &Request_data,(TickType_t)100) != pdTRUE){
                printf("[Error] Failed to send message to the Queue\n");
            }
        }
        else
            printf("[Error] Failed to allocate a struct\n");
        vTaskDelay(pdMS_TO_TICKS(100 * Ran_delay));
    }
    vTaskDelete(NULL);
}
void Process_request(void *pvParameter){
    while(1){
        struct Task_data * task = (struct Task_data *) pvParameter;
        struct Queue_data * Received_request;
        if (xQueue != NULL){
            if(xQueueReceive(xQueue,&Received_request,(TickType_t)10) == pdPASS){
                if(Received_request->request_ID == task->Task_ID){
                    printf("%s's message is: %s\n", task->Task_Name, Received_request->msg);
                    free(Received_request);
                } 
                else{
                    printf("%s received message: %s. But it's not my Task\n",task->Task_Name, Received_request->msg);
                    if (Received_request->request_Reject_counter < 2){
                        Received_request->request_Reject_counter++;
                        xQueueSendToFront(xQueue,(void *)&Received_request,(TickType_t)10);
                    }
                    else{
                        printf("Skipping this task with message: %s, because it's rejected %d times\n",Received_request->msg,Received_request->request_Reject_counter + 1);
                        free(Received_request);
                    }
                }
            }
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }
    vTaskDelete(NULL);
}
void app_main(void)
{
    xTaskCreate(&Queue_Controller,"Queue Controller",2048, NULL,3, NULL);
    xTaskCreate(&Send_request,"Send Request",2048, NULL,3, NULL);
    xTaskCreate(&Process_request,"Process Request for Task 1",2048,(void *)&Task1,3, NULL);
    xTaskCreate(&Process_request,"Process Request for Task 2",2048,(void *)&Task2,3, NULL);
    xTaskCreate(&Process_request,"Process Request for Task 3",2048,(void *)&Task3,3, NULL);
}
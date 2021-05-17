#ifndef INCLUDE_SETUP_TASKS_H__
#define INCLUDE_SETUP_TASKS_H__
#include<heltec.h>

#include "tasks/receive_weight_lora.hpp"

TaskHandle_t receive_weight_lora_task;

SemaphoreHandle_t lora_semaphore;

void core_zero(int core = 0) {
  xTaskCreatePinnedToCore(receive_weight_lora_code, "receive", 5000, NULL, 1, &receive_weight_lora_task, core);
}
void core_one(int core = 1) {
  
}

void setup_tasks() {
  lora_semaphore = xSemaphoreCreateMutex();
  
  core_zero();
  core_one();
}

#endif // INCLUDE_SETUP_TASKS_H__
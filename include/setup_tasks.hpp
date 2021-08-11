#ifndef INCLUDE_SETUP_TASKS_H__
#define INCLUDE_SETUP_TASKS_H__
#include<heltec.h>

TaskHandle_t plot_oled_task;
TaskHandle_t receive_weight_lora_task;

QueueHandle_t plot_oled_queue_time;
QueueHandle_t plot_oled_queue_altitude;
QueueHandle_t plot_oled_queue_recovery;

SemaphoreHandle_t lora_semaphore;

#include "tasks/receive_weight_lora.hpp"
#include "tasks/plot_oled.hpp"

void core_zero(int core = 0) {
  xTaskCreatePinnedToCore(receive_weight_lora_code, "receive", 5000, NULL, 1, &receive_weight_lora_task, core);
}
void core_one(int core = 1) {
  xTaskCreatePinnedToCore(plot_oled_code, "oled", 2000, NULL, 1, &plot_oled_task, core);
}

void setup_tasks() {
  lora_semaphore = xSemaphoreCreateMutex();

  plot_oled_queue_altitude = xQueueCreate(1, sizeof(float));
  plot_oled_queue_time = xQueueCreate(1, sizeof(uint64_t));
  plot_oled_queue_recovery = xQueueCreate(1, sizeof(bool));

  core_zero();
  core_one();
}

#endif // INCLUDE_SETUP_TASKS_H__
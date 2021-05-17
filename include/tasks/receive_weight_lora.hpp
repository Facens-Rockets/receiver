#ifndef INCLUDE_RECEIVE_WEIGHT_LORA_H__
#define INCLUDE_RECEIVE_WEIGHT_LORA_H__

#include "setup_tasks.hpp"
#include "lora_callback.hpp"

extern SemaphoreHandle_t lora_semaphore;

void receive_weight_lora_code(void* parameters) {
  while (true) {
    if(xSemaphoreTake(lora_semaphore, 1)) {
      on_receive_lora_callback(LoRa.parsePacket());
      xSemaphoreGive(lora_semaphore);
    }
    vTaskDelay(1);
  }
}

#endif // INCLUDE_RECEIVE_WEIGHT_LORA_H__
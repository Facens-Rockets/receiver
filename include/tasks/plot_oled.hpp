#ifndef INCLUDE_TASKS_PLOT_OLED_H__
#define INCLUDE_TASKS_PLOT_OLED_H__

#include "heltec.h"
#include "setup_tasks.hpp"

void plot_oled_code(void* parameters) {
  uint8_t init_receive = 0;
  int packet_rssi = 0;

  // char* load = "";

  byte relay_response = 0x00;

  while (true) {
    xQueueReceive(ignition_queue, &ignition_send, 1);
    // xQueueReceive(load_queue, &load, 1);
    xQueueReceive(relay_response_queue, &relay_response, 1);
    xQueueReceive(packet_rssi_queue, &packet_rssi, 1);

    Heltec.display->clear();

    Heltec.display->setFont(ArialMT_Plain_10);
    Heltec.display->drawString(0, 0, "Init: " + init_receive ? "Iniciado" : "Aguardando...");
    Heltec.display->drawString(0, 10, "RSSI: " + String(packet_rssi, DEC));

    Heltec.display->setFont(ArialMT_Plain_16);
    // Heltec.display->drawString(0, 30, "Load: "+ message.payload);
    Heltec.display->drawString(0, 30, "MAX: " + String(packet_rssi, DEC));

    Heltec.display->display();

    vTaskDelay(1);
  }
}

#endif  // INCLUDE_TASKS_PLOT_OLED_H__

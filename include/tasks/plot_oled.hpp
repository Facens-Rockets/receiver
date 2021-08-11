#ifndef INCLUDE_TASKS_PLOT_OLED_H__
#define INCLUDE_TASKS_PLOT_OLED_H__
#include "setup_tasks.hpp"

void plot_oled_code(void* parameters) {
  float altitude = 0.00;
  uint64_t time = 0;
  bool recovery = false;
  
  while (true) {
    xQueueReceive(plot_oled_queue_altitude, &altitude, portMAX_DELAY);
    xQueueReceive(plot_oled_queue_time, &time, portMAX_DELAY);
    xQueueReceive(plot_oled_queue_recovery, &recovery, portMAX_DELAY);
    Heltec.display->clear();

    Heltec.display->setFont(ArialMT_Plain_10);

    Heltec.display->drawString(0, 0, "Altitude:\t" + String(altitude) + " mts");
    // Heltec.display->drawString(0, 10, "Time:\t" + time + " ms");
    Heltec.display->drawString(0, 20, "Recovery:\t" + String(recovery));

    Heltec.display->display();
    vTaskDelay(1);
  }
}

#endif  // INCLUDE_TASKS_PLOT_OLED_H__

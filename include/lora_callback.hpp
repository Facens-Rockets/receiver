#ifndef INCLUDE_LORA_CALLBACK_H__
#define INCLUDE_LORA_CALLBACK_H__

#include "setup_tasks.hpp"

byte destination = 0;
byte local_address = 0;
String payload = "";

void on_receive_lora_callback(int packet_size) {
  if (packet_size <= 0) return;
  float weight = 0;
  uint8_t buffer[sizeof(weight)];
  uint64_t time = 0;
  uint8_t bufferTime[sizeof(time)];
  float altitude = 0;
  uint8_t buffer_altitude[sizeof(altitude)];
  bool recovery = false;

  destination = LoRa.read();
  if (destination == 0xFF) {
    local_address = LoRa.read();
    if (local_address == 0xF2) {
      LoRa.readBytes(buffer, sizeof(weight));
      weight = *((float*)buffer);
      LoRa.readBytes(bufferTime, sizeof(time));
      time = *((uint64_t*)bufferTime);

      // Serial.print(destination, HEX);
      // Serial.print("\t");
      // Serial.print(local_address, HEX);
      // Serial.print("\t");
      Serial.print(weight * -1);
      Serial.print("\t");
      Serial.print(time);
      // Serial.print("\t");
      Serial.println();
      // Serial.println(LoRa.packetRssi(), DEC);
    } else if (local_address == 0xF3) {
      LoRa.readBytes(buffer_altitude, sizeof(altitude));
      altitude = *((float*)buffer_altitude);
      LoRa.readBytes(bufferTime, sizeof(time));
      time = *((uint64_t*)bufferTime);
      recovery = LoRa.read();

      Serial.print(time);
      Serial.print("\t");
      Serial.print(altitude);
      Serial.print("\t");
      Serial.print(recovery);
      Serial.print("\n");
    }
  } else {
    payload = LoRa.readString();
    // Serial.print(destination, HEX);
    // Serial.print("\t");
    // Serial.println(payload);
  }
}

#endif  // INCLUDE_LORA_CALLBACK_H__

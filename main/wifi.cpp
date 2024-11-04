#include "wifi.h"

void WiFiController::connect() {
  delay(1500);
  Serial.print("Attempting to connect to WPA SSID : ");
  Serial.println(ssid);
  status = WiFi.begin(ssid, pass);
  while (status != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to the network.");
}
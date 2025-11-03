#include <WiFi.h>
#include "settings.h"
#include "led_control.h"
#include "light_sensor.h"
#include "web_server.h"
#include "rtc_manager.h"
#include <SPIFFS.h>

const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

void setup() {
  Serial.begin(115200);
  delay(100);

  if(!SPIFFS.begin(true)) Serial.println("SPIFFS failed");

  strip.begin();
  strip.show();

  setupLightSensor(34);
  loadSettings();
  applySettings();

  WiFi.begin(ssid, password);
  unsigned long start = millis();
  while(WiFi.status() != WL_CONNECTED && millis() - start < 15000) delay(500);

  setupRTC();
  setupWebServer();
}

void loop() {
  handleLighting();
  delay(50);
}

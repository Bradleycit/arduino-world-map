#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoOTA.h>
#include <LittleFS.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "settings.h"
#include "led_control.h"
#include "light_sensor.h"
#include "rtc_manager.h"
#include "web_server.h"

// Default WiFi AP fallback
const char* ap_ssid = "WMAP_Config";
const char* ap_password = "worldmap123";

void setup() {
  Serial.begin(115200);
  delay(100);

  // Filesystem
  if(!LittleFS.begin(true)) {
    Serial.println("LittleFS failed to mount");
  } else Serial.println("LittleFS mounted");

  // Load settings
  loadSettings();

  // Init hardware modules
  strip.begin();
  strip.show();
  setupLightSensor(34); // LDR on GPIO34
  setupRTC();

  // WiFi: try connect; if not, start AP for config
  WiFi.mode(WIFI_STA);
  if (settings.wifi_ssid != "" && settings.wifi_password != "") {
    WiFi.begin(settings.wifi_ssid.c_str(), settings.wifi_password.c_str());
    Serial.print("Connecting to WiFi");
    unsigned long start = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - start < 15000) {
      Serial.print(".");
      delay(500);
    }
  }

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("\\nStarting AP for configuration");
    WiFi.mode(WIFI_AP);
    WiFi.softAP(ap_ssid, ap_password);
    Serial.print("AP IP: "); Serial.println(WiFi.softAPIP());
  } else {
    Serial.println("\\nWiFi connected: "); Serial.println(WiFi.localIP());
  }

  // OTA
  ArduinoOTA.onStart([](){ Serial.println("OTA Start"); });
  ArduinoOTA.onEnd([](){ Serial.println("\\nOTA End"); });
  ArduinoOTA.onError([](ota_error_t e){ Serial.printf("OTA Error[%u]\\n", e); });
  ArduinoOTA.begin();
  Serial.println("OTA ready");

  // Web server and API
  setupWebServer();
}

void loop() {
  ArduinoOTA.handle();
  handleLighting();
  delay(20);
}

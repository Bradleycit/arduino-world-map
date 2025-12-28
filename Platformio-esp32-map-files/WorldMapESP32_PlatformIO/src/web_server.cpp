#include "web_server.h"
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>
#include "settings.h"
#include "light_sensor.h"

extern AsyncWebServer server;

AsyncWebServer server(80);

String getColorHex(){
  char buf[8];
  sprintf(buf, "#%02X%02X%02X", settings.colorR, settings.colorG, settings.colorB);
  return String(buf);
}

void setupWebServer(){
  // Serve files
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *req){
    if(LittleFS.exists("/index.html")){
      req->send(LittleFS, "/index.html", "text/html");
    } else {
      req->send(200, "text/plain", "Index not found");
    }
  });

  server.on("/getsettings", HTTP_GET, [](AsyncWebServerRequest *req){
    char js[256];
    sprintf(js, "{\"mode\":%d,\"brightness\":%d,\"color\":\"%s\",\"autoDim\":%s,\"darkTheme\":%s,\"rainbowSpeed\":%d}",
      settings.mode, settings.brightness, getColorHex().c_str(),
      settings.autoDim ? "true":"false",
      settings.darkTheme ? "true":"false",
      settings.rainbowSpeed);
    req->send(200, "application/json", js);
  });

  server.on("/light", HTTP_GET, [](AsyncWebServerRequest *req){
    req->send(200, "text/plain", String(readLightLevel()));
  });

  server.on("/time", HTTP_GET, [](AsyncWebServerRequest *req){
    struct tm t;
    if(getLocalTime(&t)){
      char buf[64];
      sprintf(buf, "%02d:%02d:%02d", t.tm_hour, t.tm_min, t.tm_sec);
      req->send(200, "text/plain", buf);
    } else {
      req->send(200, "text/plain", "no-time");
    }
  });

  server.on("/set", HTTP_GET, [](AsyncWebServerRequest *req){
    if(req->hasParam("mode")) settings.mode = req->getParam("mode")->value().toInt();
    if(req->hasParam("brightness")) settings.brightness = req->getParam("brightness")->value().toInt();
    if(req->hasParam("color")){
      String hex = req->getParam("color")->value();
      if(hex.startsWith("#")) hex.remove(0,1);
      long n = strtol(hex.c_str(), NULL, 16);
      settings.colorR = (n >> 16) & 0xFF;
      settings.colorG = (n >> 8) & 0xFF;
      settings.colorB = n & 0xFF;
    }
    if(req->hasParam("autodim")) settings.autoDim = req->getParam("autodim")->value().toInt() == 1;
    if(req->hasParam("darkTheme")) settings.darkTheme = req->getParam("darkTheme")->value().toInt() == 1;
    if(req->hasParam("rainbowSpeed")) settings.rainbowSpeed = req->getParam("rainbowSpeed")->value().toInt();
    if(req->hasParam("ssid")) settings.wifi_ssid = req->getParam("ssid")->value();
    if(req->hasParam("pass")) settings.wifi_password = req->getParam("pass")->value();
    saveSettings();
    applySettings();
    req->send(200, "text/plain", "OK");
  });

  server.begin();
}

#include "web_server.h"
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include "settings.h"
#include "light_sensor.h"
AsyncWebServer server(80);

void setupWebServer(){
  server.on("/",HTTP_GET,[](AsyncWebServerRequest* req){ req->send(SPIFFS,"/index.html","text/html"); });
  server.on("/getsettings",HTTP_GET,[](AsyncWebServerRequest* req){
    char js[256];
    sprintf(js,"{\"mode\":%d,\"brightness\":%d,\"color\":\"#%02X%02X%02X\",\"autoDim\":%s,\"darkTheme\":%s,\"rainbowSpeed\":%d}",
      settings.mode,settings.brightness,settings.colorR,settings.colorG,settings.colorB,
      settings.autoDim?"true":"false",
      settings.darkTheme?"true":"false",
      settings.rainbowSpeed);
    req->send(200,"application/json",js);
  });
  server.on("/light",HTTP_GET,[](AsyncWebServerRequest* req){ req->send(200,"text/plain",String(readLightLevel())); });
  server.on("/set",HTTP_GET,[](AsyncWebServerRequest* req){
    if(req->hasParam("mode")) settings.mode=req->getParam("mode")->value().toInt();
    if(req->hasParam("brightness")) settings.brightness=req->getParam("brightness")->value().toInt();
    if(req->hasParam("color")){
      String h=req->getParam("color")->value(); if(h.startsWith("#")) h.remove(0,1);
      long n=strtol(h.c_str(),NULL,16);
      settings.colorR=(n>>16)&0xFF; settings.colorG=(n>>8)&0xFF; settings.colorB=n&0xFF;
    }
    if(req->hasParam("autodim")) settings.autoDim=req->getParam("autodim")->value().toInt()==1;
    if(req->hasParam("darkTheme")) settings.darkTheme=req->getParam("darkTheme")->value().toInt()==1;
    if(req->hasParam("rainbowSpeed")) settings.rainbowSpeed=req->getParam("rainbowSpeed")->value().toInt();
    saveSettings(); req->send(200,"text/plain","OK");
  });
  server.begin();
}

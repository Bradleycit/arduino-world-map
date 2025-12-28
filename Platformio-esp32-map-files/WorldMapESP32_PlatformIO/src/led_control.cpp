#include "led_control.h"
#include "light_sensor.h"
#include <Arduino.h>

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
int rainbowIndex = 0;

void handleLighting() {
  int effective = settings.brightness;
  if (settings.autoDim) effective = scaleBrightnessForAmbient(settings.brightness);
  strip.setBrightness(effective);

  switch (settings.mode) {
    case 0: showSunlight(); break;
    case 1: showRainbow(); break;
    case 2: showSolid(); break;
    default: strip.clear(); strip.show(); break;
  }
}

void showSunlight() {
  struct tm t;
  if(!getLocalTime(&t)) return;
  int hour = t.tm_hour;
  for(int i=0;i<LED_COUNT;i++){
    int b = max(0, 255 - abs((i - (hour * LED_COUNT / 24)) * 10));
    b = b * settings.brightness / 255;
    strip.setPixelColor(i, strip.Color(b, b/2, 0));
  }
  strip.show();
}

void showRainbow() {
  for(int i=0;i<LED_COUNT;i++){
    int idx = (i + rainbowIndex) & 255;
    strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(idx * 65536L / 256)));
  }
  strip.show();
  rainbowIndex += settings.rainbowSpeed;
}

void showSolid() {
  strip.fill(strip.Color(settings.colorR, settings.colorG, settings.colorB));
  strip.show();
}

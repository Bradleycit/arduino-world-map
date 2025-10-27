#include "led_control.h"
#include "light_sensor.h"

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
int rainbowIndex = 0;

void handleLighting() {
  int b = settings.brightness;
  if(settings.autoDim) b = scaleBrightnessForAmbient(settings.brightness);
  strip.setBrightness(b);

  switch(settings.mode){
    case SUNLIGHT: showSunlight(); break;
    case RAINBOW: showRainbow(); break;
    case SOLID: showSolid(); break;
    case OFF: strip.clear(); strip.show(); break;
  }
}

void showSunlight(){
  struct tm t;
  if(!getLocalTime(&t)) return;
  int h = t.tm_hour;
  for(int i=0;i<LED_COUNT;i++){
    int br = max(0,255 - abs((i - (h*LED_COUNT/24))*10));
    br = br*settings.brightness/255;
    strip.setPixelColor(i, strip.Color(br,br/2,0));
  }
  strip.show();
}

void showRainbow(){
  for(int i=0;i<LED_COUNT;i++){
    int idx = (i+rainbowIndex)&255;
    strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(idx*65536L/256)));
  }
  strip.show();
  rainbowIndex+=settings.rainbowSpeed;
}

void showSolid(){
  strip.fill(strip.Color(settings.colorR,settings.colorG,settings.colorB));
  strip.show();
}

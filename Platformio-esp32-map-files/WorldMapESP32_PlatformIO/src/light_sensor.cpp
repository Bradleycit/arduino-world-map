#include "light_sensor.h"
#include <Arduino.h>

static int ldrPin = 34;
static const int SMOOTH = 8;
static int readings[SMOOTH];
static int idx = 0;
static bool initd = false;
static int darkThreshold = 800;

void setupLightSensor(int pin){
  ldrPin = pin;
  pinMode(ldrPin, INPUT);
  for(int i=0;i<SMOOTH;i++) readings[i]=analogRead(ldrPin);
  initd = true;
}

int readLightLevel(){
  if(!initd) return 0;
  readings[idx] = analogRead(ldrPin);
  idx = (idx + 1) % SMOOTH;
  long s=0; for(int i=0;i<SMOOTH;i++) s += readings[i];
  return s / SMOOTH;
}

bool isRoomDark(){ return readLightLevel() < darkThreshold; }

int scaleBrightnessForAmbient(int maxBrightness){
  int v = readLightLevel();
  if(v >= darkThreshold) return maxBrightness;
  int scaled = map(v, 0, darkThreshold, 0, maxBrightness);
  return constrain(scaled, 0, maxBrightness);
}

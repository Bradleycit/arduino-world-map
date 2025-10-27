#include "light_sensor.h"
#include <Arduino.h>

static int ldrPin = 34;
static const int SMOOTH_SIZE = 8;
static int readings[SMOOTH_SIZE];
static int idx = 0;
static bool initialized = false;
static int darkThreshold = 800;

void setupLightSensor(int pin){
  ldrPin=pin;
  pinMode(ldrPin, INPUT);
  for(int i=0;i<SMOOTH_SIZE;i++) readings[i]=analogRead(ldrPin);
  initialized=true;
}

int readLightLevel(){
  if(!initialized) return 0;
  readings[idx]=analogRead(ldrPin);
  idx=(idx+1)%SMOOTH_SIZE;
  long s=0; for(int i=0;i<SMOOTH_SIZE;i++) s+=readings[i];
  return (int)(s/SMOOTH_SIZE);
}

bool isRoomDark(){ return readLightLevel()<darkThreshold; }
int scaleBrightnessForAmbient(int maxB){
  int v=readLightLevel();
  if(v>=darkThreshold) return maxB;
  int s = map(v,0,darkThreshold,0,maxB);
  return constrain(s,0,maxB);
}

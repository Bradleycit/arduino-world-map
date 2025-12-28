#pragma once
void setupLightSensor(int pin);
int readLightLevel();
bool isRoomDark();
int scaleBrightnessForAmbient(int maxBrightness);

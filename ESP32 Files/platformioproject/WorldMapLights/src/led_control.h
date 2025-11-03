#pragma once
#include <Adafruit_NeoPixel.h>
#include "settings.h"

#define LED_PIN 18
#define LED_COUNT 60

extern Adafruit_NeoPixel strip;
extern int rainbowIndex;

void handleLighting();
void showSunlight();
void showRainbow();
void showSolid();

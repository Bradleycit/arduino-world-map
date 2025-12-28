#pragma once
#include <Adafruit_NeoPixel.h>
#include "settings.h"
#include <time.h>

#define LED_PIN 23
#define LED_COUNT 150

extern Adafruit_NeoPixel strip;
extern int rainbowIndex;

void handleLighting();
void showSunlight();
void showRainbow();
void showSolid();

#pragma once
#include <Arduino.h>

enum Mode { SUNLIGHT=0, RAINBOW=1, SOLID=2, OFF=3 };

struct Settings {
  int mode;
  int brightness;
  int colorR;
  int colorG;
  int colorB;
  bool autoDim;
  bool darkTheme;
  int rainbowSpeed;
};

extern Settings settings;
void saveSettings();
void loadSettings();
void applySettings();

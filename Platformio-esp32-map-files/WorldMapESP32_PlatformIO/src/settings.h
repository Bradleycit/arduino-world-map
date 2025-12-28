#pragma once
#include <Arduino.h>

struct Settings {
  int mode = 0;
  int brightness = 100;
  int colorR = 255;
  int colorG = 255;
  int colorB = 255;
  bool autoDim = false;
  bool darkTheme = true;
  int rainbowSpeed = 4;
  String wifi_ssid = "";
  String wifi_password = "";
};

extern Settings settings;
void saveSettings();
void loadSettings();
void applySettings();

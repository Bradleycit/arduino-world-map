#include "settings.h"
#include <Preferences.h>

Preferences prefs;
Settings settings;

void saveSettings() {
  prefs.begin("worldmap", false);
  prefs.putInt("mode", settings.mode);
  prefs.putInt("brightness", settings.brightness);
  prefs.putInt("colorR", settings.colorR);
  prefs.putInt("colorG", settings.colorG);
  prefs.putInt("colorB", settings.colorB);
  prefs.putBool("autoDim", settings.autoDim);
  prefs.putBool("darkTheme", settings.darkTheme);
  prefs.putInt("rainbowSpeed", settings.rainbowSpeed);
  prefs.end();
}

void loadSettings() {
  prefs.begin("worldmap", true);
  settings.mode = prefs.getInt("mode",0);
  settings.brightness = prefs.getInt("brightness",100);
  settings.colorR = prefs.getInt("colorR",255);
  settings.colorG = prefs.getInt("colorG",255);
  settings.colorB = prefs.getInt("colorB",255);
  settings.autoDim = prefs.getBool("autoDim",false);
  settings.darkTheme = prefs.getBool("darkTheme",true);
  settings.rainbowSpeed = prefs.getInt("rainbowSpeed",4);
  prefs.end();
}

void applySettings(){}

#include <WiFi.h>
#include <Adafruit_NeoPixel.h>
#include <ESPAsyncWebServer.h>
#include <Preferences.h>
#include <time.h>

#define LED_PIN 18
#define LED_COUNT 60

// WiFi credentials
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// NeoPixel setup
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// Web server
AsyncWebServer server(80);
Preferences prefs;

// Lighting modes
enum Mode { SUNLIGHT = 0, RAINBOW = 1, SOLID = 2, OFF = 3 };

struct Settings {
  int mode;
  int brightness;
  int colorR;
  int colorG;
  int colorB;
} settings;

// Time zone setup (UTC)
const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 0;
const int daylightOffset_sec = 0;

// Rainbow animation
int rainbowIndex = 0;

// Function declarations
void handleLighting();
void showSunlight();
void showRainbow();
void showSolid();
void applySettings();
void saveSettings();
void loadSettings();

// =========================================================
// Setup
// =========================================================
void setup() {
  Serial.begin(115200);
  strip.begin();
  strip.show();
  strip.setBrightness(100);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");
  Serial.println(WiFi.localIP());

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  prefs.begin("worldmap", false);
  loadSettings();
  applySettings();

  // Web interface
  server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
    String html = "<html><head><title>World Map Lights</title>"
                  "<style>body{font-family:sans-serif;text-align:center;}label{display:block;margin:10px;}</style></head><body>";
    html += "<h2>World Map Lighting</h2>";
    html += "<form action=\"/set\" method=\"GET\">";
    html += "<label>Mode: <select name=\"mode\">";
    html += "<option value=\"0\"" + String(settings.mode == 0 ? " selected" : "") + ">Sunlight</option>";
    html += "<option value=\"1\"" + String(settings.mode == 1 ? " selected" : "") + ">Rainbow</option>";
    html += "<option value=\"2\"" + String(settings.mode == 2 ? " selected" : "") + ">Solid Color</option>";
    html += "<option value=\"3\"" + String(settings.mode == 3 ? " selected" : "") + ">Off</option>";
    html += "</select></label>";
    html += "<label>Brightness: <input type=\"range\" name=\"brightness\" min=\"0\" max=\"255\" value=\"" + String(settings.brightness) + "\"></label>";
    html += "<label>Color: <input type=\"color\" name=\"color\" value=\"#";
    char hexColor[8];
    sprintf(hexColor, "%02X%02X%02X", settings.colorR, settings.colorG, settings.colorB);
    html += String(hexColor) + "\"></label>";
    html += "<input type=\"submit\" value=\"Apply\"></form></body></html>";
    request->send(200, "text/html", html);
  });

  server.on("/set", HTTP_GET, [](AsyncWebServerRequest* request) {
    if (request->hasParam("mode")) settings.mode = request->getParam("mode")->value().toInt();
    if (request->hasParam("brightness")) settings.brightness = request->getParam("brightness")->value().toInt();
    if (request->hasParam("color")) {
      String hex = request->getParam("color")->value();
      if (hex.startsWith("#")) hex.remove(0, 1);
      long number = strtol(hex.c_str(), NULL, 16);
      settings.colorR = (number >> 16) & 0xFF;
      settings.colorG = (number >> 8) & 0xFF;
      settings.colorB = number & 0xFF;
    }
    applySettings();
    saveSettings();
    request->redirect("/");
  });

  server.begin();
}

// =========================================================
// Main loop
// =========================================================
void loop() {
  handleLighting();
  delay(50);
}

// =========================================================
// Lighting logic
// =========================================================
void handleLighting() {
  switch (settings.mode) {
    case SUNLIGHT: showSunlight(); break;
    case RAINBOW: showRainbow(); break;
    case SOLID: showSolid(); break;
    case OFF:
      strip.clear();
      strip.show();
      break;
  }
}

// =========================================================
// Lighting modes
// =========================================================
void showSunlight() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) return;

  int hour = timeinfo.tm_hour;
  for (int i = 0; i < LED_COUNT; i++) {
    int brightness = max(0, 255 - abs((i - (hour * LED_COUNT / 24)) * 10));
    strip.setPixelColor(i, strip.Color(brightness, brightness / 2, 0));
  }
  strip.show();
}

void showRainbow() {
  for (int i = 0; i < LED_COUNT; i++) {
    int pixelIndex = (i + rainbowIndex) & 255;
    uint32_t color = strip.gamma32(strip.ColorHSV(pixelIndex * 65536L / 256));
    strip.setPixelColor(i, color);
  }
  strip.show();
  rainbowIndex++;
}

void showSolid() {
  strip.fill(strip.Color(settings.colorR, settings.colorG, settings.colorB));
  strip.show();
}

// =========================================================
// Settings management
// =========================================================
void applySettings() {
  strip.setBrightness(settings.brightness);
  strip.show();
}

void saveSettings() {
  prefs.putInt("mode", settings.mode);
  prefs.putInt("brightness", settings.brightness);
  prefs.putInt("colorR", settings.colorR);
  prefs.putInt("colorG", settings.colorG);
  prefs.putInt("colorB", settings.colorB);
}

void loadSettings() {
  settings.mode = prefs.getInt("mode", 0);
  settings.brightness = prefs.getInt("brightness", 100);
  settings.colorR = prefs.getInt("colorR", 255);
  settings.colorG = prefs.getInt("colorG", 255);
  settings.colorB = prefs.getInt("colorB", 255);
}

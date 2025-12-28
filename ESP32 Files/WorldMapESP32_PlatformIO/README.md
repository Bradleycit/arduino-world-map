# WorldMapESP32 PlatformIO Project (LittleFS, OTA)

## What is included
- PlatformIO project configured for ESP32 Dev Module
- LittleFS data folder (`/data/index.html`) for web UI
- OTA support via ArduinoOTA
- DS3231 RTC support via RTClib
- NeoPixel control with Adafruit NeoPixel library
- Photoresistor (LDR) ambient dimming

## How to use
1. Open this folder in VS Code with PlatformIO installed.
2. Edit `platformio.ini` if you use a different board.
3. Put your Wi-Fi credentials in Settings via the web UI (or hardcode in `settings.cpp` for testing).
4. Upload filesystem:
   ```bash
   pio run -t uploadfs
   ```
5. Upload firmware:
   ```bash
   pio run -t upload
   ```
6. Monitor serial output:
   ```bash
   pio device monitor -p /dev/ttyUSB0 -b 115200
   ```

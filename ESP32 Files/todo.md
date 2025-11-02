# 🌎 World Map Lighting Project — To-Do List & Roadmap

A long-term plan for building a global lighting display with smart automation, weather data, and event-driven effects.

---

## ✅ Stage 1: Current ESP32-Based System (Core Lighting Setup)
**Goal:** Stable, self-contained lighting controller with web UI, RTC, and photosensor dimming.

- [ ] Confirm final ESP32 board (preferably 4 MB Flash, 5 V-tolerant NeoPixel output)
- [ ] Wire NeoPixel strip → GPIO 18 (or chosen pin)
- [ ] Wire photoresistor to ADC pin + resistor divider
- [ ] Add RTC (if external) or NTP sync for time keeping
- [ ] Upload current `.ino` firmware with:
  - Web interface (mode, color, brightness controls)
  - Dark-theme toggle in UI
  - Photosensor auto-dimming logic
- [ ] Test modes → Sunlight / Rainbow / Solid / Off
- [ ] Verify brightness and mode save via Preferences

---

## ⚙️ Stage 2: Hybrid ESP32 + Raspberry Pi System
**Goal:** Add the Pi as a brain for automation, logging, and expanded web interface.

- [ ] Set up Raspberry Pi Zero 2 W or Pi 4
- [ ] Install Node-RED or Flask / Python backend
- [ ] Connect to ESP32 over Wi-Fi (via HTTP API or MQTT)
- [ ] Choose communication method:
  - [ ] HTTP (simple, direct)
  - [ ] MQTT (advanced, scalable)
- [ ] Build Pi dashboard for: Mode / Color / Brightness / Status
- [ ] Add logging to SQLite or InfluxDB for event history
- [ ] Auto-sync time + restore last known state on boot

---

## ☁️ Stage 3: Data Integration & Dynamic Lighting
**Goal:** Pull real-world data to influence lighting patterns.

- [ ] Integrate NASA Blue Marble or day/night overlay data
- [ ] Fetch weather or storm data from OpenWeatherMap / NOAA
- [ ] Compute sunrise/sunset globally for daylight animation
- [ ] Implement region-based color zones (tornado, storm, etc.)
- [ ] (Optional) Add audio cues for special events (e.g., lightning)

---

## 💬 Stage 4: Notifications & Automation
**Goal:** Send updates and control commands from/to Discord or Telegram.

- [ ] Set up Discord bot (token + webhook)
- [ ] Or create Telegram bot via [@BotFather](https://t.me/BotFather)
- [ ] Write Python or Node-RED flows to send messages on events:
  - Mode change
  - Weather alert activation
  - Sunrise / sunset triggers
  - New Year’s Eve midnight sequence
- [ ] Optional: Allow chat commands → ESP32 (`/rainbow`, `/off`)
- [ ] Generate daily summary messages (“Today 4 lighting changes…”)

---

## 🧠 Stage 5: Expansion & Smart Integration
**Goal:** Fully connected and automated world display.

- [ ] Connect to Home Assistant or local automation system
- [ ] Implement real-time ISS tracking / aurora lighting
- [ ] Sync lighting to music during events
- [ ] Add physical buttons or mobile app controls
- [ ] (Optional) Add visual world-map display on Pi screen

---

## 🧰 Hardware Wishlist

| Component | Purpose |
|------------|----------|
| ESP32 DevKit (4 MB Flash, USB-C preferred) | Core controller |
| Raspberry Pi Zero 2 W / Pi 4 | Automation & data hub |
| NeoPixel LED strip (60 LED/m or custom) | World lighting |
| Photoresistor + 10 kΩ resistor | Ambient light sensing |
| RTC module (DS3231 optional) | Time backup |
| 5 V 10 A PSU (shared ground) | Power source |
| Logic level shifter (optional) | 3.3 → 5 V signal boost |

---

## 🗓️ Future Ideas

- [ ] Weather pattern simulation (e.g., lightning strikes)
- [ ] Global New Year’s countdown light show
- [ ] Historical event playback (e.g., eclipses, storms)
- [ ] AI-driven color themes based on world events
- [ ] Integration with NASA APIs for live imagery

---

**Last updated:** _2025-11-01_  
**Author:** Bradley  
**Project Scope:** Expandable from ESP32 to Raspberry Pi + IoT-connected world lighting system.

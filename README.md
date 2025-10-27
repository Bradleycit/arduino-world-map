# Arduino World Map 🌍  

[![Arduino](https://img.shields.io/badge/Built%20with-Arduino-blue?logo=arduino)](https://www.arduino.cc/)
[![ESP32](https://img.shields.io/badge/Powered%20by-ESP32-orange?logo=espressif)](https://www.espressif.com/)
[![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)
[![Made with Love](https://img.shields.io/badge/Made%20with-%F0%9F%92%9E-red)](#)

An interactive, wall-mounted **Arduino-powered World Map** that blends electronics, design, and embedded code to create a stunning illuminated world display.  
This project unites **Arduino or ESP32 control**, **LED animation**, and **custom fabrication** to bring geography to life.

---

## 🖼️ Project Preview

| World Map Display | Wiring & Layout | Finished Assembly |
|-------------------|----------------|-------------------|
| ![World Map Overview](/1%20-%20Fgv0gnK.png) | ![Circuit Wiring Example](/10%20-%20KGwefPr.jpg) | ![Mounted Display](/16%20-%20NP3Rcuw.png) |

---

## 📁 Repository Overview


---

## 🧭 Overview

The **Arduino World Map** lights up different parts of a world map using LEDs.  
It can show:
- Current world time zones 🌐  
- Custom animations and transitions 💡  
- Country-specific or region-based highlights ✈️  

You can build it as an educational tool, interactive décor, or a world clock centerpiece.

---

## ✨ Features

- 🕒 **World Clock mode** (RTC + ESP32 capable)
- 💡 **LED animations** with Adafruit NeoPixel
- 🧩 Modular hardware + software design
- 🖥️ **Fritzing-based wiring** and reference diagrams
- ⚙️ Expandable with sensors or IoT integration
- 🧱 Ready-to-use Arduino + ESP32 sketches

---

## ⚙️ Hardware Requirements

| Component | Description |
|------------|-------------|
| **Microcontroller** | Arduino Uno/Nano or ESP32 |
| **LEDs** | WS2812B / NeoPixel |
| **RTC Module** | DS3231 or similar (for clock mode) |
| **Power Supply** | 5V DC with adequate amperage |
| **Map Board** | Custom MDF or acrylic cutout |
| **Optional** | Sensors (PIR, light), WiFi control |

---

## 💻 Software Setup

### Arduino IDE
1. Install [Arduino IDE](https://www.arduino.cc/en/software)
2. Add required libraries:  
   - `Adafruit_NeoPixel`  
   - `RTClib`
3. Open `ESP32 Files/clock.ino`
4. Adjust pin configuration and LED count if needed
5. Upload to board → watch the map come to life!

---

## 🧩 Included Libraries

- [`Adafruit_NeoPixel`](World-Clock/Arduino%20Libraries/Adafruit_NeoPixel/)  
  For LED animation and color control.  
- [`RTClib`](World-Clock/Arduino%20Libraries/RTClib/)  
  For managing real-time clock synchronization.

*(Included locally for convenience — no external downloads needed.)*

---

## 🔌 Wiring Diagram Preview

| ATmega328 Pinout Reference |
|-----------------------------|
| ![ATmega328 Pinout](/ATmega328-Pinout.png.webp) |

*Use this pinout to identify proper LED, power, and sensor connections when building your circuit.*

If using ESP32, refer to GPIO pinout compatibility in the Arduino IDE documentation.

---

## 🔧 Assembly Guide

1. **Prepare the Map:**  
   Cut or print the world map base. Drill holes or mount LED slots.

2. **Install LEDs:**  
   Use addressable strips or individual RGB LEDs behind each section.

3. **Wire Components:**  
   Reference included Fritzing diagrams. Keep wiring neat and power stable.

4. **Upload Firmware:**  
   Load `clock.ino` or modify your own patterns.

5. **Mount & Power Up:**  
   Test lighting, then mount the finished piece on your wall or desk display.

---

## 🧠 Customization Ideas

- 🌍 Use WiFi (ESP32) for **NTP-based world time**
- 🧭 Animate **day/night zones** with brightness gradients
- ✈️ Light up **visited countries** via buttons or web control
- 🌦️ Sync LED colors to **live weather or temperature**
- 🕹️ Add remote or sensor-based triggers

---

## 🧰 Fritzing & CAD

The repo includes Fritzing installers (`.AppImage`, `.dmg`, `.msi`) for modifying schematics.  
Reference pinouts (e.g., `ATmega328-Pinout.png.webp`) are included to help map connections precisely.

---

## 📸 Gallery

Some highlights from the project build:

![LED Map Layout](/1%20-%20Fgv0gnK.png)  
*Initial LED layout concept*

![Fritzing Diagram](/3%20-%20o23TLHJ.png)  
*Arduino circuit and wiring layout*

![Mounted Display](/10%20-%20KGwefPr.jpg)  
*Finished and mounted world map display*

---

## 🤝 Contributing

Contributions and ideas are always welcome!  
To contribute:
1. Fork this repo  
2. Create a feature branch (`feature/my-improvement`)  
3. Commit and push  
4. Submit a Pull Request  

---

## 📄 License

You may use an **MIT License** for open collaboration:


---

## 🧭 Credits

- **Author:** Bradley  
- **Core Libraries:** Adafruit NeoPixel, RTClib  
- **Tools:** Arduino IDE, Fritzing, CAD design  
- **Concept:** Visualizing the world through light and code  

---

> “The world is your circuit — light it up.”

---

[![Made with Love](https://img.shields.io/badge/Made%20with-%F0%9F%92%9E-red)](#)


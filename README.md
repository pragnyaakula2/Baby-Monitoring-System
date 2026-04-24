# 🍼 Baby Monitoring System

An Arduino-based embedded system that monitors environmental conditions and infant activity in real time, providing visual and audible alerts when abnormal conditions are detected.

---

##  Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Hardware Components](#hardware-components)
- [Circuit & Pin Configuration](#circuit--pin-configuration)
- [How It Works](#how-it-works)
- [Setup & Installation](#setup--installation)
- [Demo Screenshots](#demo-screenshots)
- [Future Improvements](#future-improvements)

---

## Overview

The Baby Monitoring System uses an **Arduino Uno** as its central processing unit to continuously collect data from multiple sensors and determine the baby's status. It alternates between displaying temperature data and baby activity status on a 16×2 LCD, while triggering a buzzer for alerts in unsafe conditions.

---

## Features

-  **Temperature Monitoring** — Reads ambient temperature via DHT11; alerts if it exceeds the threshold (34°C)
-  **Motion Detection** — IR sensor detects baby movement and triggers alerts if baby goes outside the room 
-  **Automatic Night Light** — LDR detects low light and automatically turns on a night light
-  **LCD Display** — Real-time status messages shown on a 16×2 I2C LCD
-  **Buzzer Alerts** — Immediate audio feedback for critical conditions

---

## Hardware Components

| Component | Quantity | Purpose |
|---|---|---|
| Arduino Uno | 1 | Central microcontroller |
| DHT11 Sensor | 1 | Temperature & humidity sensing |
| IR Sensor | 1 | Motion detection |
| LDR Module | 1 | Light intensity detection |
| 16×2 LCD (I2C) | 1 | Real-time display |
| Buzzer | 1 | Audio alert |
| LED / Night Light | 1 | Automatic room lighting |
| Jumper Wires | Several | Connections |
| Breadboard | 1 | Prototyping |

---

## Circuit & Pin Configuration

| Component | Arduino Pin |
|---|---|
| DHT11 Data | Pin 2 |
| IR Sensor Output | Pin 3 |
| LDR Digital Output | Pin 6 |
| Night Light (LED) | Pin 13 |
| Buzzer | Pin 8 |
| LCD SDA | A4 |
| LCD SCL | A5 |

> **Note:** The LCD communicates over I2C at address `0x27`.

---

## How It Works

1. **Startup** — The LCD displays "Baby Monitor" for 2 seconds, then clears.

2. **Cyclic Display Loop** — Every 2 seconds, the display toggles between two screens:
   - **Screen 1 (Temperature):** Shows current temperature. If it exceeds 34°C, the buzzer activates and displays "High Temp!".
   - **Screen 2 (Motion):** Shows baby movement status. If the IR sensor detects motion, the buzzer activates and displays "Baby Moving!".

3. **Night Light Logic** — The LDR constantly monitors ambient light. When the room is dark (LDR reads HIGH), the night light turns ON automatically.

4. **Serial Monitor** — All events are also logged to the Serial Monitor at 9600 baud for debugging.

---

## Setup & Installation

### Prerequisites

- [Arduino IDE](https://www.arduino.cc/en/software)
- Libraries (install via Library Manager):
  - `DHT sensor library` by Adafruit
  - `LiquidCrystal_I2C` by Frank de Brabander

### Steps

1. Clone or download this repository.
2. Open `baby_monitor.ino` in the Arduino IDE.
3. Install the required libraries via **Sketch → Include Library → Manage Libraries**.
4. Connect all components as per the pin configuration above.
5. Select **Board: Arduino Uno** and the correct **COM Port**.
6. Click **Upload**.

---

## Demo Screenshots

### Figure 1 — LCD Displaying Temperature

![LCD displaying temperature reading](images/s3.jpg)

*The LCD shows the current room temperature. If it exceeds 34°C, the second line changes to "High Temp!" and the buzzer sounds.*

---

### Figure 2 — Night Light Triggered by Darkness

![Night light activated when room turns dark](images/s1.jpg)

*When the LDR detects low ambient light (night/dark room), the system automatically activates the night light on Pin 13.*

---

### Figure 3 — Motion Detection via IR Sensor

![IR sensor detecting baby motion](images/s2.jpg)

*When the IR sensor detects the baby moving, the LCD displays "Baby Moving!" and the buzzer triggers to alert the caregiver.*

---

## Future Improvements

- Add **humidity threshold alerts** (DHT11 also provides humidity data)
- Integrate a **Wi-Fi module (ESP8266/ESP32)** for remote monitoring via smartphone
- Add a **camera module** for visual monitoring
- Use a **battery pack** to make the system portable
- Log sensor data to an **SD card** for historical analysis

---

## License

This project is open-source and free to use for educational and personal purposes.
# 🌱 Smart IoT Irrigation System

An embedded C project for **LPC2148 ARM7** microcontroller that automatically monitors and controls field irrigation using IoT — sending real-time sensor data to **ThingSpeak Cloud** via an **ESP01 WiFi module**.

---

## 📋 Table of Contents
- [Overview](#overview)
- [Hardware Requirements](#hardware-requirements)
- [Software Requirements](#software-requirements)
- [Pin Configuration](#pin-configuration)
- [Project Structure](#project-structure)
- [How It Works](#how-it-works)
- [Setup & Configuration](#setup--configuration)
- [ThingSpeak Setup](#thingspeak-setup)
- [Building with Keil uVision](#building-with-keil-uvision)
- [Flashing with Flash Magic](#flashing-with-flash-magic)

---

## Overview

This system:
- Reads **Temperature & Humidity** from a **DHT11** sensor
- Reads **Soil Moisture** (digital & analog) from a soil moisture sensor
- Displays readings on a **16x2 LCD**
- Automatically **turns ON/OFF the water motor** (LED in demo) based on soil moisture
- Uses **temperature as a secondary parameter** for smarter irrigation durations
- Sends all data to **ThingSpeak Cloud** every 15 seconds via **ESP01 WiFi**
- Uses the built-in **RTC** to manage upload timing

---

## Hardware Requirements

| Component | Description |
|---|---|
| LPC2148 | ARM7TDMI-S Microcontroller |
| DHT11 | Temperature & Humidity Sensor |
| 16x2 LCD | Character LCD (4-bit mode) |
| ESP01 | WiFi Module (AT Commands) |
| Soil Moisture Sensor | Capacitive or resistive, analog + digital output |
| SPDT Relay | For controlling 12V water motor |
| LED | Used instead of actual motor (as per instructions) |
| DB-9 / USB-UART | For UART0 debug and Flash Magic programming |
| 12V Power Supply | For water motor |
| 3.3V Regulator | For ESP01 power supply |

---

## Software Requirements

| Tool | Purpose |
|---|---|
| Keil uVision 5 | IDE & C Compiler (ARM-MDK) |
| Embedded C | Programming language |
| Flash Magic | Firmware flashing via UART |
| ThingSpeak Account | IoT cloud platform |
| Hyper Terminal / PuTTY | UART debug monitor |

---

## Pin Configuration

### LPC2148 Pin Mapping

| Peripheral | Pin | Direction |
|---|---|---|
| LCD RS | P0.4 | Output |
| LCD EN | P0.5 | Output |
| LCD D4-D7 | P0.12-P0.15 | Output |
| DHT11 Data | P0.6 | Bidirectional |
| Soil Moisture (Digital) | P0.7 | Input |
| Soil Moisture (Analog) | P0.28 / AD0.1 | Analog Input |
| Motor / Relay / LED | P0.10 | Output |
| UART0 TX (Debug) | P0.0 | Output |
| UART0 RX (Debug) | P0.1 | Input |
| UART1 TX (ESP01) | P0.8 | Output |
| UART1 RX (ESP01) | P0.9 | Input |

---

## Project Structure

```
SmartIoTIrrigation/
├── src/
│   ├── main.c              # Main application logic
│   ├── lcd.c               # LCD 16x2 driver (4-bit)
│   ├── delay.c             # Software delay functions
│   ├── uart.c              # UART0 (debug) & UART1 (ESP01)
│   ├── dht11.c             # DHT11 temperature & humidity driver
│   ├── esp01.c             # ESP01 WiFi + ThingSpeak driver
│   ├── soil_moisture.c     # Soil moisture sensor (digital & ADC)
│   ├── motor.c             # Motor/relay/LED control driver
│   └── rtc.c               # Built-in RTC driver
├── include/
│   ├── lcd.h
│   ├── delay.h
│   ├── uart.h
│   ├── dht11.h
│   ├── esp01.h
│   ├── soil_moisture.h
│   ├── motor.h
│   └── rtc.h
├── SmartIoTIrrigation.uvprojx  # Keil uVision project file
└── README.md
```

---

## How It Works

### Irrigation Logic (Smart Control)

```
Read Soil Moisture Sensor
         │
    Soil DRY?
    ├── YES → Check Temperature
    │         ├── Temp >= 30°C → Motor ON for 3 minutes (hot weather)
    │         └── Temp < 30°C  → Motor ON for 1 minute  (normal weather)
    │         → Send "Motor ON" to ThingSpeak
    │         → Wait duration → Motor OFF
    │         → Send "Motor OFF" to ThingSpeak
    └── NO  → Motor stays OFF
```

### ThingSpeak Fields

| Field | Data |
|---|---|
| Field 1 | Temperature (°C) |
| Field 2 | Humidity (%) |
| Field 3 | Soil Moisture ADC (0–1023) |
| Field 4 | Motor Status (0 = OFF, 1 = ON) |

---

## Setup & Configuration

### 1. Edit WiFi Credentials

Open `include/esp01.h` and update:

```c
#define WIFI_SSID       "YOUR_WIFI_SSID"
#define WIFI_PASSWORD   "YOUR_WIFI_PASSWORD"
```

### 2. Edit ThingSpeak API Key

```c
#define THINGSPEAK_API_KEY  "YOUR_API_KEY_HERE"
```

### 3. Calibrate Soil Moisture Sensor

Open `include/soil_moisture.h` and adjust thresholds based on your sensor:

```c
#define SOIL_DRY_THRESHOLD   600   /* ADC value above this = DRY */
#define SOIL_WET_THRESHOLD   300   /* ADC value below this = WET */
```

---

## ThingSpeak Setup

1. Create a free account at [thingspeak.com](https://thingspeak.com)
2. Create a new **Channel** with 4 fields:
   - Field 1: Temperature
   - Field 2: Humidity
   - Field 3: Soil Moisture
   - Field 4: Motor Status
3. Go to **API Keys** tab and copy your **Write API Key**
4. Paste the key into `include/esp01.h`

---

## Building with Keil uVision

1. Open **Keil uVision 5**
2. Go to **Project → Open Project**
3. Select `SmartIoTIrrigation.uvprojx`
4. Press **F7** or click **Build** to compile
5. Ensure no errors — warnings are acceptable
6. The `.hex` file will be generated in `output/`

> **Include Path**: Set to `.\include` in Project → Options → C/C++ → Include Paths

---

## Flashing with Flash Magic

1. Connect LPC2148 to PC via DB-9 or USB-UART converter
2. Put LPC2148 in **ISP mode**: Hold ISP button, press Reset, release ISP
3. Open **Flash Magic**:
   - Device: `LPC2148`
   - COM Port: Select your COM port
   - Baud Rate: `9600` (or `115200`)
   - Interface: `None (ISP)`
   - Oscillator (MHz): `12`
4. Browse to `output/SmartIoTIrrigation.hex`
5. Check **Erase all Flash** and click **Start**
6. After flashing, press Reset to run the program

---

## LCD Display Format

```
Line 1:  T:28C H:65%
Line 2:  Soil:40%  M:OFF
```

---

## Debug Output (UART0 @ 9600 baud)

Connect a serial terminal to UART0 to see debug messages:

```
=============================
 Smart IoT Irrigation System
=============================
[INIT] All peripherals initialized
[INIT] RTC set
[WIFI] Connecting to MyWiFi...
[WIFI] Connected!
[MAIN] Entering main loop...
[SENSOR] Temp:28C  Hum:65%
[SENSOR] Soil ADC:720  Pct:22%
[INFO] Soil dry + normal temp -> Motor ON 1 min
[INFO] Motor turned OFF
[INFO] Uploading to ThingSpeak...
[INFO] Upload complete
```

---

## Notes

- Use **LED** instead of the actual water motor during testing (as per project instructions)
- ESP01 requires **3.3V** power — do not power it from 5V
- Connect a **10kΩ pull-up resistor** on the DHT11 data line
- ThingSpeak free tier allows updates every **15 seconds minimum**
- CCLK = 60 MHz, PCLK = 15 MHz (VPB divider = 4)

---

## License

This project is for educational purposes under Vector India training program.

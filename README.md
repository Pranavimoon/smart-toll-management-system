# Smart Toll Management System

![Arduino](https://img.shields.io/badge/Platform-ESP32-blue?style=for-the-badge&logo=arduino)
![RFID](https://img.shields.io/badge/Technology-RFID-green?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-yellow?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-Completed-brightgreen?style=for-the-badge)

> An automated, RFID-based toll collection system that distinguishes between **local** and **global** vehicles — enabling cashless, contactless toll management with real-time gate control and LCD feedback.

---

## Table of Contents

- [About the Project](#about-the-project)
- [Features](#features)
- [System Architecture](#system-architecture)
- [Hardware Components](#hardware-components)
- [Circuit Diagram](#circuit-diagram)
- [Demo](#demo)
- [Libraries Required](#libraries-required)
- [Pin Configuration](#pin-configuration)
- [How to Run](#how-to-run)
- [How It Works](#how-it-works)
- [Project Report](#project-report)

---

## About the Project

With the rapid rise of vehicles on Indian roads, traditional toll booths cause massive congestion, fuel wastage, and manual errors. This **Smart Toll Management System** solves that using **RFID technology** and an **ESP32 microcontroller**.

- **Local vehicles** (pre-registered residents) → Gate opens, **no toll deducted**
- **Global vehicles** (all others) → Toll is **automatically deducted**, gate opens
- **Unregistered tags** → **Access denied**

Built as a mini project for the Department of Electronics & Telecommunication Engineering, **Bharati Vidyapeeth's College of Engineering for Women, Pune-43** (2024–25).

---

## Features

- Automatic RFID tag scanning via EM-18 module
- Differentiates local vs. global vs. unregistered vehicles
- Servo motor-controlled barrier gate
- Real-time LCD status display (I2C)
- Cashless and contactless toll collection
- Low cost (~₹2050 total BOM)
- Expandable: FASTag, cloud, and solar power ready

---

## System Architecture

```
system_architecture.png

```

---

## Hardware Components

| Component | Specification | Cost (INR) |
|-----------|--------------|------------|
| RFID Module (EM-18) | 125 kHz, 5V DC, 2–5 cm range | ₹200 |
| Microcontroller | ESP32-WROOM-32, Dual-core, Wi-Fi + BT | ₹450 |
| LCD Display | 16x2, I2C interface, 5V | ₹150 |
| Servo Motor | SG90, PWM controlled, 5V | — |
| Motor Driver + DC Motor | L298N, gate control | ₹200 |
| Passive Components | Resistors, LEDs, Capacitors, Transformer, etc. | ₹600 |
| Power Supply Unit | 12V regulated | ₹450 |
| **Total** | | **₹2050** |

---

## Circuit Diagram

> See `/docs/circuit_diagram.png` for the full schematic.

Key connections:

| Module | ESP32 Pin |
|--------|-----------|
| EM-18 RFID TX | RX2 (GPIO 16) |
| Servo Motor | GPIO 26 |
| LCD SDA | GPIO 21 |
| LCD SCL | GPIO 22 |
| Power | VIN / GND |

---

## Demo

> See `/demo/` folder for hardware photos.

| Scenario | LCD Output | Gate |
|----------|-----------|------|
| Local Vehicle scanned | `Local Vehicle / No Toll Deducted` | Opens |
| Global Vehicle scanned | `Global Vehicle / Toll Deducted!` | Opens |
| Unknown tag | `Non-Tag Vehicle / Access Denied` | Stays closed |

---

## Libraries Required

Install these via **Arduino IDE → Library Manager**:

| Library | Version | Purpose |
|---------|---------|---------|
| `ESP32Servo` by Kevin Harrington | 3.0.6 | Servo motor control on ESP32 |
| `LiquidCrystal_I2C` by Frank de Brabander | 1.1.2 | I2C LCD display control |
| `Wire` | Built-in | I2C communication |
| `HardwareSerial` | Built-in | UART communication with RFID |

---

## How to Run

### Prerequisites
- Arduino IDE (v1.8+ or v2.x)
- ESP32 board package installed
  - Go to **File → Preferences → Additional Board URLs** and add:
    ```
    https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
    ```
  - Then: **Tools → Board → Boards Manager** → search `esp32` → Install

### Steps

1. **Clone this repository**
   ```bash
   git clone https://github.com/YOUR_USERNAME/smart-toll-management-system.git
   cd smart-toll-management-system
   ```

2. **Open the code**
   ```
   Open /code/smart_toll_system.ino in Arduino IDE
   ```

3. **Install libraries**
   - `ESP32Servo` v3.0.6
   - `LiquidCrystal_I2C` v1.1.2

4. **Add your RFID tag IDs** in the code:
   ```cpp
   // Local/exempted vehicles
   String exemptedRFIDs[] = { "YOUR_TAG_ID_HERE" };

   // Global/non-exempted vehicles
   String nonExemptedRFIDs[] = { "TAG_ID_1", "TAG_ID_2" };
   ```

5. **Select board and port**
   - Board: `ESP32 Dev Module`
   - Upload Speed: `115200`
   - Port: Your COM port

6. **Upload and open Serial Monitor** at `115200 baud` to debug

---

## How It Works

1. System powers on → LCD shows `Toll Plaza:`
2. Vehicle approaches → RFID tag scanned by EM-18 reader
3. ESP32 receives tag ID via UART and checks against stored lists:
   - **Exempted list** → `Local Vehicle / No Toll Deducted` → Servo opens gate
   - **Non-exempted list** → `Global Vehicle / Toll Deducted!` → Servo opens gate
   - **Unknown** → `Access Denied` → Gate stays closed
4. Gate stays open for **5 seconds**, then closes
5. LCD resets to `Toll Plaza:`

---

## Project Report

The full project report is available at `/docs/Smart_Toll_Management_Report.pdf`

Includes: Literature Survey, System Architecture, PCB Layout, Simulation, Testing Procedure, Performance Analysis, and Conclusion.

---

## License

This project is licensed under the **MIT License** — feel free to use, modify, and distribute with attribution.

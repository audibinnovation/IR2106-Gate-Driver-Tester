# IR2106 Gate Driver Test (Arduino UNO/Nano)

This project provides a simple Arduino sketch to generate complementary PWM signals with dead-time for testing the **IR2106 half-bridge gate driver** on a UPS/inverter PCB. It includes a heartbeat LED indicator and a duty cycle sweep for dynamic validation.

---

## ✨ Features
- Hardware **Timer1 PWM** at ~10 kHz
- Complementary outputs on pins **9 (OC1A)** and **10 (OC1B)**
- ~2.5 µs dead-time insertion to prevent shoot-through
- Duty cycle sweep from **10% → 90% → 10%**
- On-board LED (pin 13) blinks **twice every 5 seconds** as a heartbeat

---

## 🔧 Hardware Connections
- **Arduino Pin 9 (OC1A)** → IR2106 `HIN`
- **Arduino Pin 10 (OC1B)** → IR2106 `LIN`
- **IR2106 HO** → High-side MOSFET gate
- **IR2106 LO** → Low-side MOSFET gate
- **Bootstrap capacitor (100 nF)** between VB and VS
- **Bootstrap diode** from VCC to VB
- **Decoupling capacitor (100 nF)** close to VCC–COM

---

## ⚡ Usage
1. Upload the sketch to Arduino UNO/Nano.
2. Power Arduino via USB.
3. Supply IR2106 with **12–15 V VCC** and bootstrap network.
4. Probe HO and LO outputs with an oscilloscope before connecting MOSFETs.
5. Start with a **low DC bus voltage (12–24 V)** for safe testing.
6. Observe duty cycle sweep and LED heartbeat.

---

## 🧪 Testing Notes
- Adjust `ICR1` for frequency changes (e.g., 800 → 20 kHz).
- Modify `OCR1A`/`OCR1B` for duty cycle and dead-time tuning.
- Use resistive loads (lamp, dummy resistor) for first PCB tests.
- Always confirm bootstrap capacitor charging before applying full load.

---

## 📂 Repository Contents
- `IR2106_Test.ino` → Arduino sketch with PWM + LED heartbeat
- `README.md` → Project documentation
- (Optional) `schematic.txt` → Text-based wiring diagram for PCB layout

---

## 📜 License
Open-source under MIT License. Free to use and modify for hardware testing and educational purposes.

# Automatic Feeder (ESP32 + ESP-IDF)

A simple WiFi-enabled automatic fish feeder built using ESP32 and a 28BYJ-48 stepper motor.

This is a hobby project focused on building a reliable, connected feeder with remote control and scheduling capabilities.

---

## Features (WIP)

- Stepper motor-based feeding mechanism
- Configurable feeding control
- WiFi connectivity (planned)
- Remote control via mobile app (planned)
- Daily status with Picture (Planned)
- Provision to remotely control additonal equipment (Planned)

---

## Hardware

- ESP32
- 28BYJ-48 Stepper Motor
- ULN2003A Driver Board
- External 5V supply

---

## Project Structure

- `drivers/stepper_uln2003/`  
  Reusable driver for ULN2003A + 28BYJ-48 motor (ESP-IDF compatible)

- `main/`  
  Application code (currently used for testing and integration)

---

## Notes

- A simple stepper driver is already implemented and can be reused independently.
- Current implementation is focused on motor control and basic testing.
- More features (WiFi, scheduling, app control) will be added incrementally.

---

## Status

🚧 Work in progress

---

## Future Plans

- WiFi provisioning (captive portal)
- Time-based feeding (SNTP)
- MQTT / cloud control
- Android app

## Enclosure

The enclosure for the project is 3D printed from the following developer:

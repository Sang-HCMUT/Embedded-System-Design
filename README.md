#  Fire and Intrusion Alarm System with Remote Control using ESP32 and SIM Module

## 📝 Project Overview
This project presents an **embedded smart system** designed to detect and alert users in case of **fire hazards** or **unauthorized intrusion**. The system is built on the **ESP32** microcontroller, equipped with environmental sensors, and utilizes the **SIMCOM A7680C 4G module** to send **real-time SMS alerts**. Additionally, it integrates the **Blynk IoT platform** for remote monitoring and control via a mobile app.

## 🛠️ Hardware Components
| Component           | Description                              |
|---------------------|------------------------------------------|
| ESP32               | Main microcontroller                     |
| DHT11               | Temperature and humidity sensor          |
| KY-026              | Flame detection sensor                   |
| PIR Sensor          | Motion detection sensor                  |
| SIMCOM A7680C       | 4G LTE module for SMS communication      |
| Buzzer              | Alarm siren                              |
| 3.7V Battery        | Power supply for SIM module              |

## ⚙️ Key Features
- **24/7 real-time monitoring**
- **Fire detection** (based on temperature > 50°C and flame signal)
- **Intrusion detection** using PIR motion sensor
- **Instant SMS alert** sent to the user's phone
- **Local alarm activation** using buzzer
- **Remote control via Blynk app**
- **Low-power mode** support using ESP32's deep sleep

## 📱 User Interface
- **Blynk App (Mobile)**:
  - Monitor temperature and humidity
  - Remotely control the buzzer (ON/OFF)
- **SMS Alerts**:
  - Immediate notifications upon fire or intrusion detection

## 📊 System Algorithm
1. Initialize UART and configure I/O pins
2. Continuously read sensor data (DHT11, KY-026, PIR)
3. Analyze sensor conditions:
   - If fire is detected (high temperature + flame), trigger buzzer and send SMS
   - If motion is detected, trigger intrusion alert
4. Provide user access via Blynk to monitor data and control the system remotely

## 🧪 Test Results
- System runs stably during demo scenarios
- Alarm is triggered immediately upon detection
- SMS alerts are sent within 1–2 seconds
- Buzzer can be turned off remotely via Blynk app

## 🧑‍💻 Team Members
- **Nguyễn Hoàng Sang** – Software development (Team Leader)
- **Phan Thành Sang** – System planning and report preparation
- **Võ Tuấn Thành** – Software development
- **Lưu Đức Nam** – Hardware design
- **Trần Thị Như Hảo** – Hardware design

## 📆 Timeline
- **Start Date:** September 15, 2024  
- **End Date:** December 15, 2024

## 💡 Notes
This project was developed as part of the **Embedded System Design** course at **Ho Chi Minh City University of Technology (HCMUT)**. It aims to demonstrate real-world applications of embedded technologies in smart home security and fire prevention systems.

## LICENSE
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

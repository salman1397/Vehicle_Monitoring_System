# 🚗 **Smart Vehicle Monitoring System**

A **real-time vehicle monitoring system** that tracks **speed, location, fuel level, temperature, humidity, and driver behavior**. The system detects **overspeeding**, **accidents**, and **drink-and-drive incidents**, notifying the owner via an **app or SMS**. Owners can also call the driver remotely for safety and assistance.

---

## 📌 **Features**

### 📍 Real-time Tracking  
Monitor vehicle **location and speed** using **GPS**.

### 📊 Data Visualization  
View **live graphs** of speed, temperature, fuel level, and accelerometer data on a **real-time dashboard**.

### ⚠️ Overspeed Detection  
The system alerts the owner **when the vehicle exceeds the speed limit**.

### 🛑 Accident Detection  
Detects accidents using **accelerometer data** and sends an emergency alert.

### 🍻 Drink & Drive Detection  
Detects alcohol in the driver's breath and sends a **warning alert**.

### 📡 Instant Alerts  
Sends notifications via **mobile app & SMS** for immediate action.

### 📞 Owner-Driver Communication  
The owner can **call the driver** in case of emergencies.

---

## 🛠 **Hardware Components**

| Component | Description | Image |
|-----------|------------|-------|
| **ESP32** | Main controller for data processing & communication | ![ESP32](https://raw.githubusercontent.com/salman1397/Vehicle_Monitoring_System/main/images/esp32.png) |
| **GPS Module** | Tracks vehicle location and speed | ![GPS Module](https://raw.githubusercontent.com/salman1397/Vehicle_Monitoring_System/main/images/gps_module.jpg) |
| **GSM Module** | Sends SMS alerts and allows calls | ![GSM Module](https://raw.githubusercontent.com/salman1397/Vehicle_Monitoring_System/main/images/gsm_module.jpg) |
| **Accelerometer** | Detects sudden impacts or accidents | ![Accelerometer](https://raw.githubusercontent.com/salman1397/Vehicle_Monitoring_System/main/images/accelerometer.jpg) |
| **Alcohol Sensor** | Detects alcohol presence in driver’s breath | ![MQ-3 Alcohol Sensor](https://raw.githubusercontent.com/salman1397/Vehicle_Monitoring_System/main/images/alcohol_sensor.jpg) |
| **DHT11 Sensor** | Measures indoor temperature & humidity | ![DHT11 Sensor](https://raw.githubusercontent.com/salman1397/Vehicle_Monitoring_System/main/images/dht11.jpg) |

---

---
| Name | Image |
|------|-------|
| **Datastreams** | ![ESP32](https://raw.githubusercontent.com/salman1397/Vehicle_Monitoring_System/main/images/dashboard_a.png) |
| **Web Dashboard** | ![ESP32](https://raw.githubusercontent.com/salman1397/Vehicle_Monitoring_System/main/images/dashboard_b.png) |

---






## 🔄 **How It Works**

1. **Sensors collect data** (GPS, accelerometer, alcohol, temperature, fuel level).
2. **ESP32 processes the data** and sends it to the server.
3. **Data is displayed on a real-time dashboard** for monitoring.
4. If any abnormal event occurs:
   - **Overspeeding?** Owner receives an alert.  
   - **Accident detected?** Emergency SMS is sent.  
   - **Alcohol detected?** Warning alert is triggered.  
5. **GSM module allows calling the driver** if needed.

---

## 📡 **Real-Time Monitoring Dashboard**

- **Live graphs** for speed, location, fuel, and temperature.
- **Web & Mobile App** support for easy access.
- **Alerts & Notifications** for quick response.

---

## 🚀 **Setup Instructions**

1. **Connect the components** as per the circuit diagram.
2. **Flash the ESP32 with firmware** using Arduino IDE.
3. **Set up the server** to store and visualize data.
4. **Use the app to receive alerts and monitor data.**

📌 *Detailed installation guide coming soon!*

---

## 🤝 **Contributions & Feedback**

Feel free to contribute or report issues. Let’s improve **vehicle safety** together! 🚗💨

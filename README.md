# Burglar_alarm_system

A fully functional **Arduino-based smart security system** that integrates a PIR motion sensor, keypad input, LDR light detection, LCD display, buzzer alarm, LED alert, and relay control. The system detects intrusions, triggers alarms, and allows disarming via password.



##  Project Overview

This project provides the essential logic for a compact home or office security system. The system:

* Detects **motion** using a PIR sensor
* Checks **ambient light** to avoid false alarms
* Displays system status on an **I2C LCD**
* Triggers a **buzzer alarm**, **LED alert**, and **relay activation** on intrusion
* Allows users to **disarm** the system through a keypad using a password
* Supports **re-arming** using a dedicated keypad command



##  Components Required

* Arduino Uno (or compatible)
* PIR motion sensor
* 4×4 Matrix Keypad
* I2C LCD Display (16×2)
* Active Buzzer
* LED for intrusion alert
* Relay module
* LDR + 10kΩ resistor (voltage divider)
* Jumper wires
* Breadboard



##  Wiring Guide

### **Sensors & Actuators**

| Component                    | Arduino Pin |
| ---------------------------- | ----------- |
| PIR Sensor OUT               | 2           |
| Buzzer                       | 3           |
| LED Alert                    | 4           |
| Relay Module                 | A1          |
| LDR (voltage divider output) | A3          |

### **Keypad (4×4)**

| Arduino Pins   | Keypad Pins |
| -------------- | ----------- |
| 7, 8, 9, 10    | Rows 1–4    |
| 11, 12, 13, A0 | Columns 1–4 |

### **LCD Display (I2C)**

| LCD Pin | Arduino Pin |
| ------- | ----------- |
| SDA     | A4          |
| SCL     | A5          |
| VCC     | 5V          |
| GND     | GND         |



##  System Features

###  **Motion Detection**

Uses PIR sensor to detect human movement.

###  **Light-Level Check**

Alarm triggers only when `lightLevel < lightThreshold` to reduce false alarms.

###  **Password-Protected Disarming**

Default password: **1234#**

Commands:

* `1234#` → Disarm system
* `A` → Re-arm system
* `*` → Clear input

###  **LCD Status Display**

Shows:

* Armed/Disarmed state
* Light levels (live)
* Intrusion warnings

###  **Audible & Visual Alerts**

Triggered on intrusion:

* Buzzer tone
* LED alert
* Relay activation (for siren, door lock, etc.)



##  How the Code Works

### **1. Initialization**

Configures keypad, LCD, PIR, buzzer, LED, relay, and system state.

### **2. Password Handling**

* User enters digits and submits using `#`.
* Correct password → system disarmed
* Wrong password → error message shown

### **3. Intrusion Logic**

Intrusion = **PIR HIGH** *and* **lightLevel < threshold** *and* **system armed**

Then `triggerAlarm()` is executed.

### **4. Alarm Response**

* LCD shows *INTRUDER ALERT*
* Buzzer activates
* LED turns on
* Relay engages



## Example LCD Outputs

```
System Armed
Light: 312
```

```
INTRUDER ALERT
Light: 120
```

```
System Disarmed
```




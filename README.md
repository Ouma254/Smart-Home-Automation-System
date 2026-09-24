# Smart-Home-Automation-System

A practical Arduino Mega 2560 smart-home automation project using a PIR motion sensor, relay-controlled lighting, I²C LCD display, and a passive buzzer with multiple randomized sound effects.

The project is being developed as a hands-on embedded systems and IoT learning project, with future expansion toward real audio playback, additional sensors, remote control, and connected home automation.

---

## Project Overview

The system automatically detects human movement using an AM312 PIR motion sensor.

When motion is detected:

1. The Arduino Mega 2560 detects the PIR signal.
2. The relay is activated.
3. The connected light turns ON.
4. The LCD displays the current motion and relay state.
5. One of several sound effects is randomly selected and played through a passive buzzer.

When motion stops:

1. The relay is deactivated.
2. The light turns OFF.
3. The buzzer stops.
4. The LCD returns to the idle state.

---

## Current Features

* Arduino Mega 2560 control
* AM312 PIR motion detection
* Automatic light switching
* Relay-controlled load
* 16x2 I²C LCD status display
* Passive buzzer sound effects
* Random sound selection
* Motion state tracking
* Serial Monitor diagnostics
* PlatformIO development environment
* Modular sound-effect functions

---

## Hardware

### Main Components

| Component              | Purpose                 |
| ---------------------- | ----------------------- |
| Arduino Mega 2560      | Main microcontroller    |
| AM312 PIR Sensor       | Motion detection        |
| 1-Channel Relay Module | Controls the light/load |
| 16x2 I²C LCD           | Displays system status  |
| Passive Buzzer         | Generates sound effects |
| Breadboard             | Prototyping             |
| Jumper Wires           | Connections             |
| Light/Bulb             | Demonstration load      |

---

## Pin Configuration

| Component | Arduino Mega Pin |
| --------- | ---------------- |
| PIR OUT   | D2               |
| Relay IN  | D3               |
| Buzzer +  | D4               |
| LCD SDA   | D20              |
| LCD SCL   | D21              |
| LCD VCC   | 5V               |
| LCD GND   | GND              |
| PIR VCC   | 5V               |
| PIR GND   | GND              |
| Relay VCC | 5V               |
| Relay GND | GND              |
| Buzzer -  | GND              |

The LCD uses I²C address:

```text
0x27
```

---

## System Architecture

```text
                   ┌─────────────────┐
                   │   AM312 PIR     │
                   │ Motion Sensor   │
                   └────────┬────────┘
                            │
                            │ D2
                            ▼
                   ┌─────────────────┐
                   │  Arduino Mega   │
                   │     2560        │
                   └───────┬─────────┘
                           │
              ┌────────────┼─────────────┐
              │            │             │
             D3           D4          I²C
              │            │             │
              ▼            ▼             ▼
         ┌─────────┐  ┌─────────┐  ┌───────────┐
         │ Relay   │  │ Buzzer  │  │ 16x2 LCD  │
         └────┬────┘  └─────────┘  └───────────┘
              │
              ▼
          Light/Bulb
```

---

## Relay Configuration

The relay is connected using:

```text
COM + NO
```

The current hardware was tested and the observed behavior is:

```text
D3 HIGH → Bulb ON
D3 LOW  → Bulb OFF
```

The software therefore uses:

```cpp
digitalWrite(RELAY_PIN, HIGH);
```

to switch the light ON.

And:

```cpp
digitalWrite(RELAY_PIN, LOW);
```

to switch the light OFF.

> **Safety:** If using mains electricity, disconnect mains power before modifying relay wiring. For development and classroom demonstrations, a low-voltage load is strongly recommended.

---

## Sound Effects

The current version contains nine randomly selected sound effects:

1. Funny WAH-WAH
2. Doorbell
3. Car horn
4. Dramatic entrance
5. Uh-oh
6. Police siren
7. Cartoon
8. Human-like laugh
9. Deep "God" / dramatic effect

The system uses:

```cpp
random(0, 9);
```

to select an effect whenever new motion is detected.

The sound is triggered only when the motion state changes from:

```text
NO MOTION
     ↓
MOTION
```

This prevents the buzzer from repeatedly playing while the PIR remains active.

---

## LCD Display

When the system is idle:

```text
SMART HOME

Motion: NO
Relay: OFF
```

When motion is detected:

```text
Motion: YES
Relay: ON
```

The LCD provides immediate feedback about the state of the system.

---

## Serial Monitor

The system also outputs diagnostic information at:

```text
9600 baud
```

Example:

```text
PIR: 1 | Motion: YES | D3: 1 | Relay: ON
```

and:

```text
PIR: 0 | Motion: NO | D3: 0 | Relay: OFF
```

The selected sound is also reported:

```text
Random sound selected: 8
Sound: LAUGH
```

---

## Software

### Development Environment

* PlatformIO
* Visual Studio Code
* Arduino Framework
* C++
* Arduino Mega 2560

### PlatformIO Configuration

```ini
[env:megaatmega2560]
platform = atmelavr
board = megaatmega2560
framework = arduino

monitor_speed = 9600

lib_deps =
    marcoschwartz/LiquidCrystal_I2C
```

---

## Required Library

The project uses:

```text
LiquidCrystal_I2C
```

PlatformIO automatically installs the library through the `lib_deps` configuration.

---

## Project Structure

```text
simple-home-auto/
│
├── include/
│
├── lib/
│
├── src/
│   └── main.cpp
│
├── test/
│
├── platformio.ini
│
└── README.md
```

---

## How It Works

The main control loop continuously reads the PIR sensor:

```cpp
int pirState = digitalRead(PIR_PIN);
```

Motion is interpreted as:

```cpp
bool motionDetected = (pirState == HIGH);
```

When motion is detected:

```cpp
digitalWrite(RELAY_PIN, HIGH);
```

The light turns ON.

The system then checks whether motion has just started:

```cpp
if (!previousMotion)
{
    playRandomSound();
}
```

After processing the current state:

```cpp
previousMotion = motionDetected;
```

This creates a simple motion-state transition system.

---

## Installation

Clone the repository:

```bash
git clone https://github.com/YOUR-USERNAME/simple-home-auto.git
```

Enter the project:

```bash
cd simple-home-auto
```

Open the project using VS Code and PlatformIO.

Connect the Arduino Mega 2560 through USB.

Build:

```bash
pio run
```

Upload:

```bash
pio run --target upload
```

Open the Serial Monitor:

```bash
pio device monitor
```

Or:

```bash
pio device monitor -b 9600
```

---

## Current Limitations

The passive buzzer is capable of generating tones but cannot reproduce actual human speech or high-quality recorded audio.

For example, the current "laugh" and "God" effects are synthesized electronic sound effects rather than real human recordings.

The current sound functions also use `delay()`, meaning the Arduino temporarily pauses normal program execution while a sound effect is playing.

---

## Planned Audio Upgrade

A future version will replace or supplement the passive buzzer with a real audio playback system.

### Planned Hardware

* DFPlayer Mini
* microSD card
* Speaker
* Optional PAM8403 amplifier

The system could then play actual recordings such as:

```text
0001.mp3 → Doorbell
0002.mp3 → Human laugh
0003.mp3 → Alarm
0004.mp3 → Welcome message
0005.mp3 → Recorded voice
```

The architecture would become:

```text
PIR
 │
 ▼
Arduino Mega
 │
 ├── Relay ──────► Light
 │
 ├── LCD ────────► Status
 │
 └── DFPlayer ───► Speaker
```

---

## Future Development

Possible future features include:

* Real MP3 audio playback
* DFPlayer Mini integration
* External amplifier
* Multiple rooms
* Multiple PIR sensors
* Door/window sensors
* Temperature monitoring
* Humidity monitoring
* Automatic fan control
* Automatic lighting
* Keypad access control
* RFID access control
* Servo-controlled door
* ESP32 connectivity
* Wi-Fi control
* Mobile/web dashboard
* MQTT integration
* Remote monitoring
* Home Assistant integration
* Event logging
* Manual/automatic operating modes
* Security alarm mode

---

## Learning Objectives

This project provides practical experience with:

* Microcontroller programming
* Digital GPIO
* Sensor interfacing
* Relay control
* I²C communication
* LCD interfacing
* PWM/tone generation
* State management
* Random number generation
* Serial communication
* Embedded C++
* Hardware troubleshooting
* PlatformIO
* Basic IoT system architecture

---

## Project Status

**Current status: Functional prototype**

The following components have been tested:

* [x] Arduino Mega 2560
* [x] PIR motion detection
* [x] Relay control
* [x] Light switching
* [x] I²C LCD
* [x] Passive buzzer
* [x] Random sound effects
* [x] Serial monitoring
* [ ] DFPlayer Mini
* [ ] Real audio playback
* [ ] External amplifier
* [ ] Wi-Fi connectivity
* [ ] Web/mobile control

---

## Author

**Denis Ouma**

Software Developer | Embedded Systems & IoT Learner

This project is part of a practical exploration of embedded systems, electronics, automation, and IoT development.

---

## License

This project is available for educational and personal development purposes.

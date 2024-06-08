# Environmental monitoring
## Introduction 

This project provides users with real-time weather and environmental data while enabling remote control of devices.

FreeRTOS project
- Task 1: Read Sensor
- Task 2: Control device
- Task 3: Connect to Wifi
- Task 4: Web Server for config wifi
- Task 5: Cloud


## Getting Started
- [PlatformIO in VSCode](https://docs.platformio.org/en/latest/integration/ide/vscode.html)
- [ThingsBoard](https://thingsboard.io/docs/getting-started-guides/helloworld/)
- ESP Wroom 32
- DHT11, Water Sensor, Button, Relay, other.
- Pin Connection ```config.h```: 
```c
#ifndef CONFIG_H
#define CONFIG_H

/*Sensor*/
#define DHTPIN 15
#define DHTTYPE DHT11
#define WATER_PIN 34

#define RELAY_PIN 32
#define STATUS_PIN 33
#define BUTTON_PIN 35

#define TURN_ON 1
#define TURN_OFF 0


/*Config for ThingsBoard with MQTT server*/
#define MQTT_SERVER "mqtt.thingsboard.cloud"
#define MQTT_PORT 1883
#define TOKEN "**************" // motify it with your token

#endif
```

## ESP32 Pinout
<img src="asset\image.png" alt="Description of the image">

## Schematic
[![Schematic](asset\image_schematic.png)](https://www.flux.ai/hihi12/main-white-universal-remote?editor=schematic&embed=1)

## Demo
[![Demo](https://img.youtube.com/vi/JxpdZ9Qpn0o/0.jpg)](https://youtu.be/JxpdZ9Qpn0o)

## References 
https://www.youtube.com/watch?v=UgbqH6cSpxk


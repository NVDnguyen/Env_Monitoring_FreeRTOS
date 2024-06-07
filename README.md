# Smart Irrigation System
## Introduction 
- FreeRTOS project

## Getting Started
- [PlatformIO in VSCode](https://docs.platformio.org/en/latest/integration/ide/vscode.html)
- [ThingsBoard](https://thingsboard.io/docs/getting-started-guides/helloworld/)
- ESP Wroom 32
- DHT11, Soil Moisture Sensor, Button, Relay, Pump, other.
- Pin Connection : 
```c
#ifndef CONFIG_H
#define CONFIG_H

/*Sensor*/
#define DHTPIN 15
#define DHTTYPE DHT11
#define SOIL_PIN 34

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

## References 
https://www.youtube.com/watch?v=UgbqH6cSpxk


# Smart Irrigation System
## Introduction 
- Dự án tưới tiêu thông minh
- Mức độ:  mini project
- Mục tiêu:  ESP301m
- Mức độ  hoàn thành : 50%

## Getting Started
- [PlatformIO in VSCode](https://docs.platformio.org/en/latest/integration/ide/vscode.html)
- [ThingsBoard](https://thingsboard.io/docs/getting-started-guides/helloworld/)
- ESP32
- DHT11, Soil Moisture Sensor, Button, Relay, Pump, other.
- Pin Connection : 
```c
#ifndef CONFIG_H
#define CONFIG_H

/*Sensor*/
#define DHTPIN 15
#define DHTTYPE DHT11
#define SOIL_PIN 34

#define RELAY_PIN 13
#define BUTTON_PIN 12
#define STATUS_REALY_PIN 20


/*Config for ThingsBoard with MQTT server*/
#define MQTT_SERVER "mqtt.thingsboard.cloud"
#define MQTT_PORT 1883
#define TOKEN "F0YhnhbPSiahMsxCspUv" // motify it with yout token

#endif
```

## References -cre
[![IMAGE ALT TEXT HERE](https://img.youtube.com/vi/UgbqH6cSpxk/0.jpg)](https://www.youtube.com/watch?v=UgbqH6cSpxk)

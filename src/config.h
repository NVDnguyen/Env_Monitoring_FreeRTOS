#ifndef CONFIG_H
#define CONFIG_H

/*Sensor*/
#define DHTPIN 15
#define DHTTYPE DHT11
#define SOIL_PIN 33

#define RELAY_PIN 32
#define BUTTON_PIN 35
#define STATUS_PIN 34

#define TURN_ON 1
#define TURN_OFF 0


/*Config for ThingsBoard with MQTT server*/
#define MQTT_SERVER "mqtt.thingsboard.cloud"
#define MQTT_PORT 1883
#define TOKEN "F0YhnhbPSiahMsxCspUv"

#endif
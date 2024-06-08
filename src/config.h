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

#define TOKEN "F0YhnhbPSiahMsxCspUv"

#endif
#ifndef TASKS_H
#define TASKS_H

#include <DHT.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <Preferences.h>
#include <ArduinoJson.h>


struct SensorData {
    int humidity;
    int temperature;
    int water;

};


void readSensor(void *params);
void controlCenter(void *params);
void printData(void *params);

void handleClient(void *params);
void connectToWifi(void *params);
void reconnect();

void upCloud(void *params);

void analyzeData (void *params);

void listenRPC(char *topic, byte *payload, unsigned int length);

#endif

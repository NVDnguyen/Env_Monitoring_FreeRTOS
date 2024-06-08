#include <Arduino.h>
#include "tasks.h"
#include "config.h"
#include "data_config.h"
#include "wifi_manager.h"

// Connection
WiFiManager wifiManager;
WiFiClient espClient;
PubSubClient client(espClient);

// Manange Data Access
QueueHandle_t xDataQ;
QueueHandle_t xAnalysisDataQ;
SemaphoreHandle_t xMutex;
DataConfig &dataCF = DataConfig::getInstance();

// Manage Task
TaskHandle_t xSensorTask;
TaskHandle_t xWifiTask;
TaskHandle_t xCloudTask;
TaskHandle_t xGetWifiConfig;
TaskHandle_t xHandleClient;
TaskHandle_t xAnalysisData;
TaskHandle_t xControlCenter;

void setup()
{
    Serial.begin(115200);
    // Set pin mode
    pinMode(WATER_PIN, INPUT);
    pinMode(BUTTON_PIN, INPUT); // Signal to manually control the PUMP
    pinMode(STATUS_PIN, INPUT); // status PUMP
    pinMode(RELAY_PIN, OUTPUT);       // CONTROL PUMP
    digitalWrite(RELAY_PIN,TURN_OFF);
    // establish connection
    //wifiManager.begin();
    client.setServer(MQTT_SERVER, MQTT_PORT);
    client.setCallback(listenRPC);    
    // setup Data
    xDataQ = xQueueCreate(5, sizeof(SensorData));
    xAnalysisDataQ = xQueueCreate(5, sizeof(SensorData));
    xMutex = xSemaphoreCreateMutex();
    // Task schedule
    //Core 1
    xTaskCreatePinnedToCore(readSensor, "Read Sensor", 4096, NULL, 3, &xSensorTask, 1);
    xTaskCreatePinnedToCore(controlCenter, "Control Manual", 2048, NULL, 4, &xControlCenter, 1);
    // Core 0
    xTaskCreatePinnedToCore(connectToWifi, "Wifi", 4096, NULL, 2, &xWifiTask, 0);
    xTaskCreatePinnedToCore(handleClient, "Web", 4096, NULL, 4, &xHandleClient, 0);
    xTaskCreatePinnedToCore(upCloud, "Cloud", 6000, NULL, 1, &xCloudTask, 0);
    //xTaskCreatePinnedToCore(analyzeData, "Sleep Manager", 4000, NULL, 2, NULL, ARDUINO_RUNNING_CORE);
}

void loop()
{
}

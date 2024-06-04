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
    pinMode(SOIL_PIN, INPUT);
    pinMode(BUTTON_PIN, INPUT_PULLUP); // Signal to manually control the PUMP
    pinMode(STATUS_REALY_PIN, INPUT); // status PUMP
    pinMode(RELAY_PIN, OUTPUT);       // CONTROL PUMP
    // establish connection
    //wifiManager.begin();
    client.setServer(MQTT_SERVER, MQTT_PORT);
    client.setCallback(listenRPC);    
    // setup Data
    xDataQ = xQueueCreate(10, sizeof(SensorData));
    xAnalysisDataQ = xQueueCreate(10, sizeof(SensorData));
    xMutex = xSemaphoreCreateMutex();
    // Task schedule
    xTaskCreatePinnedToCore(readSensor, "Read Sensor", 4000, NULL, 3, &xSensorTask, ARDUINO_RUNNING_CORE);
    xTaskCreatePinnedToCore(controlCenter, "Control Manual", 1000, NULL, 4, &xControlCenter, ARDUINO_RUNNING_CORE);
    xTaskCreatePinnedToCore(connectToWifi, "Wifi", 4000, NULL, 2, &xWifiTask, ARDUINO_RUNNING_CORE);
    xTaskCreatePinnedToCore(handleClient, "Web", 4000, NULL, 3, &xHandleClient, ARDUINO_RUNNING_CORE);
    xTaskCreatePinnedToCore(upCloud, "Cloud", 4000, NULL, 1, &xCloudTask, ARDUINO_RUNNING_CORE);
    // xTaskCreatePinnedToCore(analyzeData, "Sleep Manager", 4000, NULL, 2, NULL, ARDUINO_RUNNING_CORE);
}

void loop()
{
}

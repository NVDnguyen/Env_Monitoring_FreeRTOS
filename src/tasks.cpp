#include <Arduino.h>
#include "tasks.h"
#include "config.h"
#include "wifi_manager.h"
#include "data_config.h"
extern QueueHandle_t xDataQ;         // main.cpp
extern QueueHandle_t xAnalysisDataQ; // main.cpp
extern PubSubClient client;
extern Preferences preferences;
extern WiFiManager wifiManager;

extern TaskHandle_t xHandleClient;
extern TaskHandle_t xWifiTask;
extern SemaphoreHandle_t xMutex;

void readSensor(void *params)
{
    DHT dht(DHTPIN, DHTTYPE);
    dht.begin();

    while (1)
    {
        Serial.println("readSensor: Running");
        SensorData data;
        data.soilMoisture = map(analogRead(SOIL_PIN), 0, 4095, 0, 100);
        data.humidity = dht.readHumidity();
        data.temperature = dht.readTemperature();
        data.statusPump = digitalRead(STATUS_REALY_PIN);

        if (!isnan(data.humidity) && !isnan(data.temperature))
        {
            if (xQueueSend(xDataQ, &data, portMAX_DELAY) != pdPASS)
            {
                Serial.println("Failed to send data to queue.");
            }
        }
        else
        {
            Serial.println("Failed to read from DHT sensor!");
        }

        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

void connectToWifi(void *params)
{
    Serial.println("Connecting to Wifi....");

    while (1)
    {

        if (WiFi.status() != WL_CONNECTED)
        {
            // get data from memory
            String ssid;
            String password;

            DataConfig &dataCF = DataConfig::getInstance();
            dataCF.loadWifiConfig();
            ssid = dataCF.getSSID();
            password = dataCF.getPASSWORD();
            Serial.println("Memory: " + ssid + ", " + password);
            // begin
            WiFi.begin(ssid.c_str(), password.c_str());

            vTaskDelay(pdMS_TO_TICKS(5000));

            if (WiFi.status() == WL_CONNECTED)
            {
                Serial.print("Connected to ");
                Serial.println(WiFi.localIP());
                // reload data
                // vTaskResume(xLoadData);
                // Suspend this task since WiFi is connected
                vTaskSuspend(NULL);
            }
            else
            {
                wifiManager.begin();
                vTaskResume(xHandleClient);
            }
        }
        Serial.println("connectToWifi: Running");

        // Delay to avoid busy-waiting
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

void printData(void *params)
{
    while (1)
    {
        SensorData data;
        if (xQueueReceive(xDataQ, &data, portMAX_DELAY) == pdPASS)
        {
            Serial.print("Hum: ");
            Serial.print(data.humidity);
            Serial.print("| Temp: ");
            Serial.print(data.temperature);
            Serial.print("| Soil: ");
            Serial.print(data.soilMoisture);
            Serial.print("| Pump: ");
            Serial.print(data.statusPump);
        }
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void reconnect()
{
    while (!client.connected() && WiFi.isConnected())
    {
        Serial.print("Attempting MQTT connection...");
        if (client.connect("ESP32Client", TOKEN, NULL))
        {
            Serial.println("connected");
            client.subscribe("v1/devices/me/rpc/request/+");
        }
        else
        {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            vTaskDelay(pdMS_TO_TICKS(5000));
        }
    }
}

void upCloud(void *params)
{
    while (1)
    {
        if (WiFi.status() == WL_CONNECTED)
        {
            if (!client.connected())
            {
                reconnect();
            }
            client.loop();

            SensorData data;
            if (xQueueReceive(xDataQ, &data, pdMS_TO_TICKS(10000)) == pdPASS) // wait 5 sensorData available in queue
            {
                String payload = "{";
                payload += "\"temperature\":";
                payload += data.temperature;
                payload += ",";
                payload += "\"humidity\":";
                payload += data.humidity;
                payload += ",";
                payload += "\"soilMoisture\":";
                payload += data.soilMoisture;
                payload += ",";
                payload += "\"statusPump\":";
                payload += data.statusPump;
                payload += "}";

                char attributes[100];
                payload.toCharArray(attributes, 100);
                if (client.publish("v1/devices/me/telemetry", attributes))
                {
                    // Serial.print("Published data: ");
                    // Serial.println(payload);
                    Serial.println("upCloud:    Good");
                }
                else
                {
                    Serial.println("Failed to publish data");
                }
            }
        }
        else
        {
            vTaskResume(xWifiTask);
        }
        vTaskDelay(pdMS_TO_TICKS(6000));
    }
}

void handleClient(void *params)
{
    wifiManager.begin();
    while (1)
    {
        wifiManager.handleClient();
        // if (wifiManager.isGood())
        // {
        //     vTaskDelay(pdMS_TO_TICKS(5000));
        //     ESP.restart();
        // }
        if (WiFi.isConnected())
        {
            Serial.println("handleClient: Stop");
            wifiManager.stop();
            vTaskSuspend(NULL);
        }
        else
        {
            Serial.println("handleClient: Running");
        }
    }
}

void analyzeData(void *params)
{
    //
}
void controlCenter(void *params) // recieve cloud and manual control by button
{
    // if (WiFi.isConnected() && client.connected())
    // {
    //     Serial.println("control center running...");
    //     client.setCallback(listenRPC);
    // }

    while (1)
    {
        static bool lastState = HIGH;
        static unsigned long lastDebounceTime = 0;
        unsigned long debounceDelay = 50;
        bool currentState = digitalRead(BUTTON_PIN);
        if (currentState != lastState)
        {
            lastDebounceTime = millis();
        }
        if ((millis() - lastDebounceTime) > debounceDelay)
        {
            if (currentState != lastState)
            {
                lastState = currentState;
                if (currentState == LOW)
                {
                    digitalWrite(RELAY_PIN, HIGH);
                }
            }
        }
        digitalWrite(RELAY_PIN, LOW);
        vTaskDelay(pdMS_TO_TICKS(6000));
    }
}
void listenRPC(char *topic, byte *payload, unsigned int length)
{
    // convert payload to string
    String payloadIC = "";
    for (unsigned int i = 0; i < length; i++)
    {
        payloadIC += (char)payload[i];
    }
    Serial.println(payloadIC);
    // process json
    DynamicJsonDocument jsonDoc(200);
    DeserializationError e = deserializeJson(jsonDoc, payloadIC);
    if (e)
    {
        Serial.println(e.f_str());
        return;
    }
    // process RPC
    const char *method = jsonDoc["method"];
    if (strcmp(method, "setState") == 0)
    {
        int status = jsonDoc["params"];
        digitalWrite(RELAY_PIN, status);
    }
}

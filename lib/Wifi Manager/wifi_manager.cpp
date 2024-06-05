
#include "wifi_manager.h"
#include "data_config.h"
#include "web.h"
#include "captive_req.h"
WiFiManager::WiFiManager() : server(80) {}

bool WiFiManager::begin()
{
    // Initialize WiFi module and start access point
    setupAP();
    return true;
}

void WiFiManager::setupAP()
{
    const char *ssid = "ESP32_Config";
    const char *password = "11111111";
    WiFi.softAP(ssid, password);
    WiFi.softAPConfig(IPAddress(192, 168, 1, 32), IPAddress(192, 168, 1, 1), IPAddress(255, 255, 255, 0));

    // Cấu hình DNSServer để chuyển hướng tất cả các yêu cầu đến IP của ESP32
    dnsServer.start(53, "*", IPAddress(192, 168, 1, 32));

    server.addHandler(new CaptiveRequestHandler()).setFilter(ON_AP_FILTER); // only when requested from AP

    server.on("/", HTTP_GET, std::bind(&WiFiManager::handleRoot, this, std::placeholders::_1));
    server.on("/save", HTTP_POST, std::bind(&WiFiManager::handleSave, this, std::placeholders::_1));
    server.begin();
}

void WiFiManager::handleRoot(AsyncWebServerRequest *request)
{
    request->send(200, "text/html", html);
}

void WiFiManager::handleSave(AsyncWebServerRequest *request)
{
    if (request->hasParam("ssid", true) && request->hasParam("password", true))
    {
        String ssid = request->getParam("ssid", true)->value();
        String password = request->getParam("password", true)->value();

        extern SemaphoreHandle_t xMutex;
        if (xSemaphoreTake(xMutex, portMAX_DELAY) == pdTRUE)
        {
            // Save in memory
            DataConfig &dataCF = DataConfig::getInstance();
            dataCF.updateWifiConfig(ssid, password);
            xSemaphoreGive(xMutex);
        }

        request->send(200, "text/html", "WiFi credentials saved. Restarting..." + ssid + ".." + password);
        // Optionally, restart the ESP here
    }
    else
    {
        request->send(400, "text/html", "Invalid request");
    }
}

void WiFiManager::handleClient()
{
    dnsServer.processNextRequest(); // Xử lý các yêu cầu DNS
}

// Định nghĩa phương thức stop()
void WiFiManager::stop()
{
    // Dừng DNSServer
    dnsServer.stop();

    // Dừng WebServer
    server.end();

    // Tắt Access Point
    WiFi.softAPdisconnect(true);
}


#ifndef WIFIMANAGER_H
#define WIFIMANAGER_H

#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <DNSServer.h>

class CaptiveRequestHandler; 
class WiFiManager {
public:
    WiFiManager();
    bool begin();
    void stop();  // Thêm phương thức dừng
    void handleClient();

private:
    void setupAP();
    void handleRoot(AsyncWebServerRequest *request);
    void handleSave(AsyncWebServerRequest *request);
    AsyncWebServer server;
    DNSServer dnsServer;  // Thêm đối tượng DNSServer
};

#endif // WIFIMANAGER_H

#include "captive_req.h"

CaptiveRequestHandler::CaptiveRequestHandler() {}

CaptiveRequestHandler::~CaptiveRequestHandler() {}

bool CaptiveRequestHandler::canHandle(AsyncWebServerRequest *request) {
    // Add your logic here if needed
    return true;
}

void CaptiveRequestHandler::handleRequest(AsyncWebServerRequest *request) {
    // Send the HTML response
    request->send_P(200, "text/html", page);
}

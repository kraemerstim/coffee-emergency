#include "Restcall.h"
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include "ConnectionDetails.h"

bool Restcall::sendButtonPressed(const char* device_id, int button_id) {
    if (WiFi.status() != WL_CONNECTED) {
        return false;
    }

    HTTPClient http;
    char buf[256];
    snprintf(buf, sizeof buf, "http://192.168.0.136:5000/emergency/rest/device/%s/button/%d/pressed", device_id, button_id);
    //String zusammenbauen: http://emotion.cas.de/emergenc/rest/device/<device_id>/button/<button_id>/pressed

    http.begin(buf);

    Serial.println(buf);
    
    int httpCode =http.PUT("");

    Serial.print("Code: ");
    Serial.println(httpCode);

    if(httpCode == HTTP_CODE_OK) {
        Serial.print("HTTP response code ");
        Serial.println(httpCode);
        String response = http.getString();
        Serial.print("Response: ");
        Serial.println(response);
    }

    http.end();

    return true;
}


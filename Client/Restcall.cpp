#include "Restcall.h"
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include "ConnectionDetails.h"
#include <ArduinoJson.h>

int Restcall::sendButtonPressed(int button_id) {
    int returnvalue = -1;
    if (WiFi.status() != WL_CONNECTED) {
        return returnvalue;
    }

    HTTPClient http;
    String rest_call = String(HOST_ADDRESS) + "/emergency/rest/device/" + String(DEVICE_ID) + "/button/" + String(button_id) + "/pressed";

    http.begin(rest_call);

    Serial.println(rest_call);
    
    int httpCode =http.PUT("");

    Serial.print("Code: ");
    Serial.println(httpCode);

    if(httpCode == HTTP_CODE_OK) {
        Serial.print("HTTP response code ");
        Serial.println(httpCode);
        String response = http.getString();
        Serial.print("Response: ");
        Serial.println(response);

        StaticJsonBuffer<200> jsonBuffer;
        JsonObject& json_response = jsonBuffer.parseObject(response);
        int status = json_response["status"];

        Serial.print("status: ");
        Serial.println(status);
        returnvalue = status;
    }

    http.end();

    return returnvalue;
}

bool Restcall::initializeButton(Button* button) {
    if (WiFi.status() != WL_CONNECTED) {
        return false;
    }

    String type_string = "normal";
    if (button->getIsResetButton()) {
        type_string = "reset";
    }
    HTTPClient http;

    String rest_call = String(HOST_ADDRESS) + "/emergency/rest/device/" + String(DEVICE_ID) + "/button/" + String(button->getButtonId()) + "/type?type=" + type_string;

    Serial.println(rest_call);
    http.begin(rest_call);
    
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

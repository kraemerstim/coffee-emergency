//#include <ArduinoJson.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "ConnectionDetails.h"
WiFiClient client;

int inputPin = D2;
int ledPin = D4;
int buttonState = 0;
int counter = 0;

int interval = 1000;
unsigned long previousMillis = 0;

boolean button_is_pressed() {
  unsigned long currentMillis = millis();
  if ((unsigned long)(currentMillis - previousMillis) >= interval) {
    previousMillis = currentMillis;
    return true;
  }
  return false;
}


void wifiConnect() {
  Serial.print("Connecting to AP");
  /*
  WiFi.begin(AP_SSID, AP_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  */
  Serial.println("Connected");
}

void setup() {
  Serial.begin(9600);
  delay(300);

  //Interrupts fuer die Buttons aktivieren
  attachInterrupt(digitalPinToInterrupt(inputPin), ButtonPressedCallback, RISING);

  pinMode(ledPin, OUTPUT);
  Serial.println("starting interrupt test");
  //WiFi.disconnect();
}

void ButtonPressedCallback() {
  int test = millis();
  Serial.print("Stamp(ms): ");
  Serial.println(test);
  if (button_is_pressed())
    counter ++;
}

void loop() {
  delay(5000);
  Serial.print("Counter: ");
  Serial.println(counter);
}

void send_rest_notification_to_server(int button_id) {
  /*
  HTTPClient http;
  char buf[256];
  snprintf(buf, sizeof buf, "http://emotion.cas.de/rest/device/%s/button/%s/pressed?auth_token=%s", DEVICE_ID, BUTTON_ID, AUTH_TOKEN);
  http.begin(buf);
  int httpCode =http.POST();
  
  
  Serial.println(httpCode);
  if(httpCode == HTTP_CODE_OK) {
    Serial.print("HTTP response code ");
    Serial.println(httpCode);
    String response = http.getString();
    Serial.println(response);
  }
  http.end();
  */
}


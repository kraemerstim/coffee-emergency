#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "ConnectionDetails.h"
#include "Restcall.h"
#include "Button.h"

WiFiClient client;

void wifiConnect() {
  Serial.print("Connecting to AP");
  WiFi.begin(AP_SSID, AP_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Connected");
}

void setup() {
  Serial.begin(9600);
  delay(300);

  wifiConnect();
  
  Button buttons[4] = {
    Button(0, D5, false),
    Button(1, D6, false),
    Button(2, D7, false),
    Button(3, D8, false)
  };

  Serial.println("starting interrupt test");
}

void loop() {
  int pressedId = Button::pullPressedId();
  if (pressedId > -1) {
    Restcall::sendButtonPressed(BUTTON_ID, pressedId);
  }
  delay(100);
}


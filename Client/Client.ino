#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFiMulti.h>
#include "ConnectionDetails.h"
#include "Restcall.h"
#include "Button.h"

ESP8266WiFiMulti wifiMulti;     // Create an instance of the ESP8266WiFiMulti class, called 'wifiMulti'
int leds[3] = {D1, D2, D3};

void wifiConnect() {
  Serial.print("Connecting to the strongest AP"); 

  while (wifiMulti.run() != WL_CONNECTED) { // Wait for the Wi-Fi to connect: scan for Wi-Fi networks, and connect to the strongest of the networks above
    blink(0, 200, 3, true);
    Serial.print('.');
  }

  Serial.println('\n');
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID());              // Tell us what network we're connected to
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());           // Send the IP address of the ESP8266 to the computer
}

void setup() {
  Serial.begin(9600);
  delay(30);
  Serial.println('\n');

  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);

  digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);
  digitalWrite(D3, LOW);
  
  WiFi.persistent(false);
  WiFi.mode(WIFI_STA);
  WiFi.hostname("NodeMCU tim");

  wifiMulti.addAP(AP1_SSID, AP1_PASSWORD);
  wifiMulti.addAP(AP2_SSID, AP2_PASSWORD);
  //wifiMulti.addAP(AP3_SSID, AP3_PASSWORD);
  
  wifiConnect();
  
  Button buttons[4] = {
    Button(0, D5, false),
    Button(1, D6, false),
    Button(2, D7, false),
    Button(3, D8, true)
  };

  for (int i = 0; i < 4; i++) {
    buttons[i].registerInterrupt();
    //Restcall::initializeButton(&buttons[i]);
  }
}

void blink(int led_id, int interval, int times, boolean disable_rest) {
  if (disable_rest) {
    for (int i = 0; i < 3; i++) {
      digitalWrite(leds[i], LOW);
    }
  }
  if (interval == 0) {
    digitalWrite(leds[led_id], HIGH);
  }
  else
  {
    for (int i = 0; i< times; i++) {
      digitalWrite(leds[led_id], HIGH);
      delay(interval);
      digitalWrite(leds[led_id], LOW);
      delay(interval);
    }
  }
}

void loop() {
  int pressedId = Button::getPressedId();
  if (pressedId > -1) {
    while (!Restcall::sendButtonPressed(pressedId)) {
      wifiConnect();
    }
      digitalWrite(D1, HIGH);
      delay(1000);
      digitalWrite(D1, LOW);
      digitalWrite(D2, HIGH);
      delay(1000);
      digitalWrite(D2, LOW);
      digitalWrite(D3, HIGH);
      delay(1000);
      digitalWrite(D3, LOW);
      Button::pullPressedId();
  }
  delay(100);
}


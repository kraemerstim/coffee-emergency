#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFiMulti.h>
#include "ConnectionDetails.h"
#include "Restcall.h"
#include "Button.h"

int leds[3] = {D1, D2, D3};

Button buttons[4] = {
    Button(0, D5, false),
    Button(1, D6, false),
    Button(2, D7, false),
    Button(3, D8, true)
  };

ESP8266WiFiMulti wifiMulti;     // Create an instance of the ESP8266WiFiMulti class, called 'wifiMulti'

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

  pinMode(leds[0], OUTPUT);
  pinMode(leds[1], OUTPUT);
  pinMode(leds[2], OUTPUT);

  digitalWrite(leds[0], LOW);
  digitalWrite(leds[1], LOW);
  digitalWrite(leds[2], LOW);
  
  // Einrichtung des WLAN-Moduls
  WiFi.persistent(false);
  WiFi.mode(WIFI_STA);
  WiFi.hostname("NodeMCU tim");

  wifiMulti.addAP(AP1_SSID, AP1_PASSWORD);
  wifiMulti.addAP(AP2_SSID, AP2_PASSWORD);
  wifiMulti.addAP(AP3_SSID, AP3_PASSWORD);
  wifiMulti.addAP(AP4_SSID, AP4_PASSWORD);
  
  wifiConnect();

  for (int i = 0; i < 4; i++) {
    pinMode(buttons[i].getPin(), INPUT_PULLUP);
    Restcall::initializeButton(&buttons[i]);
    buttons[i].registerInterrupt();
  }

  blink(0, 0,0, true);
  delay(200);  
  blink(1, 0,0, false);  
  delay(200);  
  blink(2, 0,0, false);    
  delay(200);  
  disable_all_leds();
}

void disable_all_leds() {
  for (int i = 0; i < 3; i++) {
      digitalWrite(leds[i], LOW);
    }
}

void blink(int led_id, int interval, int times, boolean disable_rest) {
  if (disable_rest) {
    disable_all_leds();
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
      digitalWrite(leds[0], HIGH);
      delay(1000);
      digitalWrite(leds[0], LOW);
      digitalWrite(leds[1], HIGH);
      delay(1000);
      digitalWrite(leds[1], LOW);
      digitalWrite(leds[2], HIGH);
      delay(1000);
      digitalWrite(leds[2], LOW);
      Button::pullPressedId();
  }
  delay(100);
}


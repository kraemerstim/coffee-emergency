#include "Button.h"

unsigned long Button::previousMillis = 0;
int Button::pressedId = -1;
int interval = 200;

Button::Button(int button_id, int pin, bool reset_button) {
  this->button_id = button_id;
  this->pin = pin;
  this->is_reset_button = reset_button;
}

int Button::getButtonId() {
  return this->button_id;
}

int Button::getPin() {
    return this->pin;
}

boolean Button::getIsResetButton() {
    return this->is_reset_button;
}

void Button::registerInterrupt() {
    switch(button_id) {
        case 0:
            attachInterrupt(digitalPinToInterrupt(pin), Callback0, FALLING);
            Serial.println("Callback attatched: 0");
            break;
        case 1:
            attachInterrupt(digitalPinToInterrupt(pin), Callback1, FALLING);
            Serial.println("Callback attatched: 1");
            break;
        case 2:
            attachInterrupt(digitalPinToInterrupt(pin), Callback2, FALLING);
            Serial.println("Callback attatched: 2");
            break;
        case 3:
            attachInterrupt(digitalPinToInterrupt(pin), Callback3, FALLING);
            Serial.println("Callback attatched: 3");
            break;
        case 4:
            attachInterrupt(digitalPinToInterrupt(pin), Callback4, FALLING);
            Serial.println("Callback attatched: 4");
            break;
    }
}

int Button::pullPressedId() {
    int pressedId = Button::pressedId;
    if (pressedId > -1) {
        Button::pressedId = -1;
    }
    return pressedId;
}

int Button::getPressedId() {
    return pressedId;
}

bool Button::buttonIsPressed() {
    unsigned long currentMillis = millis();
    if ((unsigned long)(currentMillis - Button::previousMillis) >= interval) {
        Button::previousMillis = currentMillis;
        return true;
    }
    return false;
}

void Button::Callback0(){ Callback(0); }
void Button::Callback1(){ Callback(1); }
void Button::Callback2(){ Callback(2); }
void Button::Callback3(){ Callback(3); }
void Button::Callback4(){ Callback(4); }

void Button::Callback(int id) {
    if (Button::pressedId < 0 && buttonIsPressed()){
        Button::pressedId = id;
    }
}

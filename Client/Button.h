#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

class Button {
  private:
    int button_id;
    bool is_reset_button;
    int pin;
    static unsigned long previousMillis;
    static int pressedId;
 
    static bool buttonIsPressed();

  public:
    Button(int button_id, int pin, bool reset_button);
    void registerInterrupt();

    int getButtonId();
    int getPin();

    boolean getIsResetButton();

    static int pullPressedId();
    static int getPressedId();

    static void Callback0();
    static void Callback1();
    static void Callback2();
    static void Callback3();
    static void Callback4();

    static void Callback(int id);
};

#endif 

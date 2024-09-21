#include <Arduino.h>
#include "Arduino_FreeRTOS.h"

#include "IR.h"
#include "BaseFunc.h"
#include "mods.h"

#define LED_PIN 6

//--------------------------------------------------------------------------------------------------------------//

void setup()
{
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  attachInterrupt(0, IRreg, FALLING);
  Serial.begin(9600);
  _off_on();
}

void loop(){}
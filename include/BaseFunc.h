#pragma once
#include "FastLED.h"
#include "Arduino_FreeRTOS.h"

#define NUM_LEDS 116

extern CRGB leds[NUM_LEDS];

extern bool status;
extern CRGB activ_color;
extern float brightness;
extern TaskHandle_t pv_mode;

struct colors
{
  CRGB black;
  CRGB white;
  CRGB red;
  CRGB green;
  CRGB blue;
  CRGB cyan;
  CRGB pink;
  CRGB yellow;
  CRGB orange;
  CRGB violet;
};
extern colors base_colors;


void _off_on();
void _filling(CRGB _color);
void _change_brightness(bool _change);
// void SetMode(uint8_t mode);
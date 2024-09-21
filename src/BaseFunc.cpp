#include "BaseFunc.h"

#include "mods.h"

CRGB leds[NUM_LEDS];
bool status = false;
CRGB activ_color;
float brightness = 1;

colors base_colors =
{
  black:    CRGB(0,0,0),
  white:    CRGB(255,255,255),
  red:      CRGB(255,0,0),
  green:    CRGB(0,255,0),
  blue:     CRGB(0,0,255),
  cyan:     CRGB(0,255,255),
  pink:     CRGB(246,153,205),
  yellow:   CRGB(255,255,0),
  orange:   CRGB(255,128,0),
  violet:   CRGB(238,130,238)
};

TaskHandle_t pv_mode;

void _off_on()
{ 
  if (status) for (uint8_t i = 0; i < NUM_LEDS; i++) leds[i] = base_colors.black;
  else for (uint8_t i = 0; i < NUM_LEDS; i++) leds[i] = activ_color * brightness;
  FastLED.show();
}

void _filling(CRGB _color)
{
  // activ_color = _color;
  for (uint8_t i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = _color;
  }
}

void _change_brightness(bool _change)
{
  if (_change) brightness += 0.1;
  else brightness -= 0.1;
  if (brightness > 1) brightness = 1;
  else if (brightness < 0) brightness = 0;
  _filling(activ_color);
}

// void SetMode(uint8_t mode)
// {
//   // switch (mode)
//   // {
//   //   case 0:
//   //   {
//   //     //xTaskCreate (Blink, "effect_selector", 128, NULL, 0, &pv_mode);
//   //   } break;

//   //   case 1:
//   //   {
//   //     //xTaskCreate (Fire, "effect_selector", 128, NULL, 0, &pv_mode);
//   //   } break;

//   //   case 2:
//   //   {
//   //     xTaskCreate (Filling_Line, "effect_selector", 128, NULL, 0, &pv_mode);
//   //   } break;

//   //   case 3:
//   //   {
//   //     //xTaskCreate (Snake, "effect_selector", 128, NULL, 0, &pv_mode);
//   //   } break;

//   //   case 4:
//   //   {
//   //     //xTaskCreate (Pulse, "effect_selector", 128, NULL, 0, &pv_mode);
//   //   } break;

//   //   case 255:
//   //   {
//   //     vTaskDelete(pv_mode);
//   //     SetColor(Num_Color);
//   //   } break;
//   // }
// }
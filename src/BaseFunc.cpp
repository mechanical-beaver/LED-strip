#include "BaseFunc.h"

#include "mods.h"

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

CRGB leds[NUM_LEDS];
bool status = false;
CRGB activ_color;
float brightness = 1;

// TaskHandle_t pv_mode;

void _filling(CRGB _color)
{
  activ_color = _color;

  for (uint8_t i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CRGB(round(activ_color[0] * brightness), round(activ_color[1] * brightness), round(activ_color[2] * brightness));
  }

  FastLED.show();
}

void _off_on()
{ 
  if (status)
    for (uint8_t i = 0; i < NUM_LEDS; i++)
    {
      status = false;
      leds[i] = base_colors.black;
    }

  else
  {
    _filling(activ_color);
    status = true;
  }
  
  FastLED.show();
}

void _change_brightness(bool _change)
{
  if (_change)
    brightness += 0.1;
  else
    brightness -= 0.1;

  if (brightness > 1)
    brightness = 1;
  else if (brightness < 0.1)
    brightness = 0.1;

  _filling(activ_color);
}